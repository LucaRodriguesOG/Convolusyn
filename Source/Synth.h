/*
  ==============================================================================

    Synth.h
    Created: 18 Jul 2023 12:10:52pm
    Author:  Luca Rodrigues

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "Data/ADSRData.h"
#include "Data/OscData.h"

class Sound : public juce::SynthesiserSound {
    
public:
    bool appliesToNote(int midiNoteNumber) override { return true; }
    bool appliesToChannel(int midiChannel) override { return true; }

private:
};

class Voice : public juce::SynthesiserVoice {

public:
    // pure virtuals
    bool canPlaySound(juce::SynthesiserSound* sound) override;
    void startNote(int midiNoteNumber, float velocity, juce::SynthesiserSound* sound, int currentPitchWheelPosition) override;
    void stopNote(float velocity, bool allowTailOff) override;
    void pitchWheelMoved(int newPitchWheelValue) override;
    void controllerMoved(int controllerNumber, int newControllerValue) override;
    void renderNextBlock(juce::AudioBuffer<float>& outputBuffer, int startSample, int numSamples) override;

    // voice class
    void prepareToPlay(double sampleRate, int samplesPerBlock, int outputChannels);

    // Osc
    OscData& getOscillator() { return osc; }

    // ADSR
    void updateADSR(const float a, const float d, const float s, const float r);

    // LFO
    //void updateLFOADSR(const float a, const float d, const float s, const float r);

private:
    bool isPrepared = false;

    //============================================================================== Oscillator
    OscData osc;

    //============================================================================== ADSR
    ADSRData adsr;

    //============================================================================== Audio Buffer
    juce::AudioBuffer<float> sBuffer;
};
