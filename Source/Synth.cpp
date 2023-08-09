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

    if (!allowTailOff || !adsr.isActive()) {
        clearCurrentNote();
    }
}

void Voice::pitchWheelMoved(int newPitchWheelValue) {

}

void Voice::controllerMoved(int controllerNumber, int newControllerValue) {

}

void Voice::renderNextBlock(juce::AudioBuffer<float>& outputBuffer, int startSample, int numSamples) {
    
    // if applying to sBuffer, start from 0 to sBuffer.getNumSamples()
    // if applying to outputBuffer, start from startSample to numSamples.

    jassert(isPrepared);
    
    if (!isVoiceActive()) {
        return;
    }

    sBuffer.setSize(outputBuffer.getNumChannels(), numSamples, false, false, true); // set size to exactly what we need, no reallocation
    sBuffer.clear();

    // this will create an audio block, oscillator will add data to it, gain will turn it down

    juce::dsp::AudioBlock<float> audioBlock { sBuffer };                    // init audio block
    osc1.process(juce::dsp::ProcessContextReplacing<float>(audioBlock));    // init osc replacing context w/ audio block

    gain.process(juce::dsp::ProcessContextReplacing<float>(audioBlock));    // init gain replacing context w/ audio block

    adsr.applyEnvelopeToBuffer(sBuffer, 0, sBuffer.getNumSamples());        // init adsr (sBuffer is alias for audioBlock)
                                                                            // bc osc1 and gain needed a contexted dsp Block
    
    for (int i = 0; i < outputBuffer.getNumChannels(); i++) {               // iterate through channels and add sample from
        outputBuffer.addFrom(i, startSample, sBuffer, i, 0, numSamples);    // sBuffer to outputBuffer

        if (!adsr.isActive()) {                                             // if adsr isnt on
            clearCurrentNote();                                             // clear the note
        }
    }
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

    adsrParams.attack = 0.2f;                       // sets adsr parameters
    adsrParams.decay = 0.2f;
    adsrParams.sustain = 1.0f;
    adsrParams.release = 1.0f;

    adsr.setParameters(adsrParams);                 // apply parameters to adsr

    isPrepared = true;
}