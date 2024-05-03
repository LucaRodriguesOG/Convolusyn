/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
ConvolusynAudioProcessor::ConvolusynAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       ), 
                        apvts(*this, nullptr, "Parameters", createParameters())
#endif
{
    synth.addSound(new Sound());
    synth.addVoice(new Voice());
}

ConvolusynAudioProcessor::~ConvolusynAudioProcessor()
{
}

//==============================================================================
const juce::String ConvolusynAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool ConvolusynAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool ConvolusynAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool ConvolusynAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double ConvolusynAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int ConvolusynAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int ConvolusynAudioProcessor::getCurrentProgram()
{
    return 0;
}

void ConvolusynAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String ConvolusynAudioProcessor::getProgramName (int index)
{
    return {};
}

void ConvolusynAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void ConvolusynAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need...

    // -------------------------------------------------------------------------------------------- Synth
    synth.setCurrentPlaybackSampleRate(sampleRate);
    

    // for each voice in the synth, we must cast it to one of our voices (not juce::SynthesiserVoices), and use our
    // prepareToPlay function on our voices. This will process each voice so they are ready to play.
    for (int i = 0; i < synth.getNumVoices(); i++) {
        if (auto voice = dynamic_cast<Voice*>(synth.getVoice(i))) {
            voice->prepareToPlay(sampleRate, samplesPerBlock, getNumOutputChannels());
        }
    }

    filter.prepareToPlay(sampleRate, samplesPerBlock, getNumOutputChannels());
    lfo.prepare(sampleRate);
    juce::dsp::ProcessSpec spec;
    spec.sampleRate = sampleRate;
    spec.maximumBlockSize = samplesPerBlock;
    spec.numChannels = getNumOutputChannels();
    gain.prepare(spec);
}

void ConvolusynAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool ConvolusynAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void ConvolusynAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    // In case we have more outputs than inputs, this code clears any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    // This is here to avoid people getting screaming feedback
    // when they first compile a plugin, but obviously you don't need to keep
    // this code if your algorithm always overwrites all the output channels.
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    /*juce::AudioPlayHead* playHead = getPlayHead();
    if (playHead) 
    {
        juce::AudioPlayHead::CurrentPositionInfo* info = new juce::AudioPlayHead::CurrentPositionInfo();
        
        if (!playHead->getCurrentPosition(*info)) {
            DBG("AudioPlayHead Unavailabe");
        }

        auto bpm = info->bpm;
    }*/
    
    auto bpm = getPlayHead()->getPosition()->getBpm();

    //============================================================================== Synth
    for (int i = 0; i < synth.getNumVoices(); i++) {
        if (auto voice = dynamic_cast<Voice*>(synth.getVoice(i))) {
            // Osc Type and FM Mods
            auto& oscWave = *apvts.getRawParameterValue("OSC1WAVETYPE");
            auto& fmAmt = *apvts.getRawParameterValue("FMAMT");
            auto& fmFreq = *apvts.getRawParameterValue("FMFREQ");

            // ADSR
            auto& a = *apvts.getRawParameterValue("ATTACK");            // going to change to make less cpu intensive
            auto& d = *apvts.getRawParameterValue("DECAY");
            auto& s = *apvts.getRawParameterValue("SUSTAIN");
            auto& r = *apvts.getRawParameterValue("RELEASE");

            // All Updates
            voice->getOscillator().setWaveType(oscWave);
            voice->getOscillator().setFMParams(fmAmt, fmFreq);
            voice->updateADSR(a.load(), d.load(), s.load(), r.load());
        }
    }

    //============================================================================== Midi
    /*for (const juce::MidiMessageMetadata metadata : midiMessages) {
        if (metadata.numBytes == 3) {
            juce::Logger::writeToLog("Sample Time: " + juce::String(metadata.getMessage().getTimeStamp()));
        }
    }*/

    synth.renderNextBlock(buffer, midiMessages, 0, buffer.getNumSamples());

    //============================================================================== LFO
    auto& lfoWaveType = *apvts.getRawParameterValue("LFOWAVETYPE");
    auto& lfoAmt = *apvts.getRawParameterValue("LFOAMT");
    auto& lfoFreq = *apvts.getRawParameterValue("LFOFREQ");
    auto& lfoButton = *apvts.getRawParameterValue("LFOBUTTON");

    lfo.updateParams(lfoWaveType, lfoAmt, lfoFreq);

    //============================================================================== Filter
    auto& filterType = *apvts.getRawParameterValue("FILTERTYPE");
    auto& filterCutoff = *apvts.getRawParameterValue("FILTERCUTOFF");
    auto& filterResonance = *apvts.getRawParameterValue("FILTERRESONANCE");
    auto& filterButton = *apvts.getRawParameterValue("FILTERBUTTON");

    if (lfoButton) 
    {
        filter.updateParams(filterType, filterCutoff, filterResonance, lfo.val());
    }
    else
    {
        filter.updateParams(filterType, filterCutoff, filterResonance);
    }
    if (filterButton) 
    {
        filter.process(buffer);
    }

    //============================================================================== Gain
    auto& gainVal = *apvts.getRawParameterValue("GAIN");
    gain.setGainLinear(gainVal);
    juce::dsp::AudioBlock<float> audioBlock{ buffer };
    gain.process(juce::dsp::ProcessContextReplacing<float>(audioBlock));

    // This is the place where you'd normally do the guts of your plugin's
    // audio processing...
    // Make sure to reset the state if your inner loop is processing
    // the samples and the outer loop is handling the channels.
    // Alternatively, you can process the samples with the channels
    // interleaved by keeping the same state.
    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
        auto* channelData = buffer.getWritePointer (channel);

        // ..do something to the data... 
    }
}

//==============================================================================
bool ConvolusynAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* ConvolusynAudioProcessor::createEditor()
{
    return new ConvolusynAudioProcessorEditor (*this);
}

//==============================================================================
void ConvolusynAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void ConvolusynAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new ConvolusynAudioProcessor();
}

void ConvolusynAudioProcessor::loadFile(const juce::String& file)
{

}

// Value Tree
//juce::AudioProcessorValueTreeState ConvolusynAudioProcessor::getAPVTS() {
//    return apvts;
//}

juce::AudioProcessorValueTreeState::ParameterLayout ConvolusynAudioProcessor::createParameters() {
    // vector of parameters in our value tree
    std::vector<std::unique_ptr<juce::RangedAudioParameter>> params;

    // ADSR
    params.push_back(std::make_unique<juce::AudioParameterFloat>("ATTACK", "Attack", juce::NormalisableRange{ 0.001f, 1.0f, 0.001f }, 0.1f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("DECAY", "Decay", juce::NormalisableRange{ 0.001f, 1.0f, 0.001f }, 0.1f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("SUSTAIN", "Sustain", juce::NormalisableRange{ 0.001f, 1.0f, 0.001f }, 1.0f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("RELEASE", "Release", juce::NormalisableRange{ 0.001f, 4.0f, 0.001f }, 0.4f));

    // Oscillator Waveforms and FM Mods
    params.push_back(std::make_unique<juce::AudioParameterChoice>("OSC1WAVETYPE", "Osc 1 Wave Type", juce::StringArray{ "Sine", "Saw", "Square" }, 0));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("FMAMT", "FM Amount", juce::NormalisableRange{ 0.0f, 1000.0f, 0.001f, 0.3f }, 0.0f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("FMFREQ", "FM Frequency", juce::NormalisableRange{ 0.0f, 1000.0f, 0.001f, 0.3f }, 0.0f));

    // Filter
    params.push_back(std::make_unique<juce::AudioParameterChoice>("FILTERTYPE", "Filter Type", juce::StringArray{ "Lowpass", "Highpass", "Bandpass" }, 0));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("FILTERCUTOFF", "Filter Cutoff", juce::NormalisableRange{ 20.0f, 20000.0f, 1.0f, 0.3f }, 20000.0f)); // 0.1f and 0.6f for last 2 of norm range
    params.push_back(std::make_unique<juce::AudioParameterFloat>("FILTERRESONANCE", "Filter Resonance", juce::NormalisableRange{ 0.05f, 10.0f, 0.001f }, 0.05f));
    params.push_back(std::make_unique<juce::AudioParameterBool>("FILTERBUTTON", "Filter Button", false));

    // LFO
    params.push_back(std::make_unique<juce::AudioParameterChoice>("LFOWAVETYPE", "LFO Wave Type", juce::StringArray{ "Sine", "Saw", "Square" }, 0));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("LFOAMT", "LFO Amt", juce::NormalisableRange{ 0.0f, 20000.0f, 1.0f, 0.3f }, 1.0f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("LFOFREQ", "LFO Frequency", juce::NormalisableRange{ 0.001f, 5000.0f, 0.001f, 0.3f }, 200.0f));
    params.push_back(std::make_unique<juce::AudioParameterBool>("LFOBUTTON", "LFO Button", false));

    // Convolution
    params.push_back(std::make_unique<juce::AudioParameterBool>("CONVBUTTON", "Convolution Button", false));

    // Gain
    params.push_back(std::make_unique<juce::AudioParameterFloat>("GAIN", "Gain", juce::NormalisableRange{ 0.0f, 1.0f, 0.001f }, 0.5f));

    return {params.begin(), params.end()};
}