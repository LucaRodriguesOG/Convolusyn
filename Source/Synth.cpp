/*
  ==============================================================================

    Synth.cpp
    Created: 18 Jul 2023 12:10:52pm
    Author:  Luca Rodrigues

  ==============================================================================
*/

#include "Synth.h"
#include <JuceHeader.h>


// pure virtuals
bool Voice::canPlaySound(juce::SynthesiserSound* sound) 
{
    return dynamic_cast<juce::SynthesiserSound*>(sound) != nullptr;
}

void Voice::startNote(int midiNoteNumber, float velocity, juce::SynthesiserSound* sound, int currentPitchWheelPosition) 
{
    adsr.noteOn();
    osc.setWaveFrequency(midiNoteNumber);
    //lfoADSR.noteOn();
}

void Voice::stopNote(float velocity, bool allowTailOff) 
{
    adsr.noteOff();
    //lfoADSR.noteOff();

    if (!allowTailOff || !adsr.isActive()) 
    {
        clearCurrentNote();
    }
}

void Voice::pitchWheelMoved(int newPitchWheelValue) 
{

}

void Voice::controllerMoved(int controllerNumber, int newControllerValue) 
{

}

void Voice::renderNextBlock(juce::AudioBuffer<float>& outputBuffer, int startSample, int numSamples) 
{
    
    // if applying to sBuffer, start from 0 to sBuffer.getNumSamples()
    // if applying to outputBuffer, start from startSample to numSamples.

    jassert(isPrepared);
    
    if (!isVoiceActive()) {
        return;
    }

    sBuffer.setSize(outputBuffer.getNumChannels(), numSamples, false, false, true); // set size to exactly what we need, no reallocation
    //lfoADSR.applyEnvelopeToBuffer(sBuffer, 0, numSamples); // startSample?
    sBuffer.clear();

    // this will create an audio block, oscillator will add data to it, gain will turn it down

    juce::dsp::AudioBlock<float> audioBlock { sBuffer };                    // init audio block
    osc.getNextAudioBlock(audioBlock);                                      // init osc replacing context w/ audio block
    adsr.applyEnvelopeToBuffer(sBuffer, 0, sBuffer.getNumSamples());        // init adsr (sBuffer is alias for audioBlock) bc osc and gain needed a contexted dsp Block

    //filter.process(sBuffer);                                                // init filter to process this block
    gain.process(juce::dsp::ProcessContextReplacing<float>(audioBlock));    // init gain replacing context w/ audio block
    
    for (int i = 0; i < outputBuffer.getNumChannels(); i++) {               // iterate through channels and add sample from
        outputBuffer.addFrom(i, startSample, sBuffer, i, 0, numSamples);    // sBuffer to outputBuffer

        if (!adsr.isActive()) {                                             // if adsr isnt on
            clearCurrentNote();                                             // clear the note
        }
    }
}

// voice class
void Voice::prepareToPlay(double sampleRate, int samplesPerBlock, int outputChannels) 
{
    juce::dsp::ProcessSpec spec;                    // declare/init process spec
    spec.maximumBlockSize = samplesPerBlock;
    spec.sampleRate = sampleRate;
    spec.numChannels = outputChannels;

    osc.prepareToPlay(spec);                                            
    adsr.setSampleRate(sampleRate);                                     
    //filter.prepareToPlay(sampleRate, samplesPerBlock, outputChannels);
    //lfoADSR.setSampleRate(sampleRate);


    gain.prepare(spec);                                                 
    gain.setGainLinear(0.10f);

    isPrepared = true;
}

void Voice::updateADSR(const float a, const float d, const float s, const float r) 
{
    adsr.updateADSR(a, d, s, r);
}

//void Voice::updateFilter(const int filterType, const float filterCutoff, const float filterResonance) 
//{
//    float lfo = lfoADSR.getNextSample();
//    filter.updateParams(filterType, filterCutoff, filterResonance, lfo);
//}
//
//void Voice::updateLFOADSR(const float a, const float d, const float s, const float r) 
//{
//    lfoADSR.updateADSR(a, d, s, r);
//}