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
bool Voice::canPlaySound(juce::SynthesiserSound* sound) {
    return dynamic_cast<juce::SynthesiserSound*>(sound) != nullptr;
}

void Voice::startNote(int midiNoteNumber, float velocity, juce::SynthesiserSound* sound, int currentPitchWheelPosition) {
    adsr.noteOn();
    osc1.setFrequency(juce::MidiMessage::getMidiNoteInHertz(midiNoteNumber));
}

void Voice::stopNote(float velocity, bool allowTailOff) {
    adsr.noteOff();
}

void Voice::pitchWheelMoved(int newPitchWheelValue) {

}

void Voice::controllerMoved(int controllerNumber, int newControllerValue) {

}

void Voice::renderNextBlock(juce::AudioBuffer<float>& outputBuffer, int startSample, int numSamples) {
    
    jassert(isPrepared);
    
    // this will create an audio block, oscillator will add data to it, gain will turn it down

    juce::dsp::AudioBlock<float> audioBlock { outputBuffer };               // init audio block
    osc1.process(juce::dsp::ProcessContextReplacing<float>(audioBlock));    // init osc replacing context w/ audio block

    gain.process(juce::dsp::ProcessContextReplacing<float>(audioBlock));    // init gain replacing context w/ audio block

    adsr.applyEnvelopeToBuffer(outputBuffer, startSample, numSamples);      // init adsr (outputBuffer is alias for audioBlock
                                                                            // bc osc1 and gain needed a contexted dsp Block
}

// voice class
void Voice::prepareToPlay(double sampleRate, int samplesPerBlock, int outputChannels) {

    adsr.setSampleRate(sampleRate);

    juce::dsp::ProcessSpec spec;                    // declare/init process spec
    spec.maximumBlockSize = samplesPerBlock;
    spec.sampleRate = sampleRate;
    spec.numChannels = outputChannels;

    osc1.prepare(spec);                             // prepares osc w/ spec
    gain.prepare(spec);                             // prepares gain w/ spec

    gain.setGainLinear(0.10f);

    isPrepared = true;
}