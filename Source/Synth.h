/*
  ==============================================================================

    Synth.h
    Created: 18 Jul 2023 12:10:52pm
    Author:  Luca Rodrigues

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

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
    void updateADSR(const float a, const float d, const float s, const float r);

private:
    bool isPrepared = false;

    //============================================================================== Oscillator+
    juce::dsp::Oscillator<float> osc1{ [](float x) { return std::sin(x); }, 200 };  // init oscillator w/ std::sin(), 200 lut idx
    juce::dsp::Gain<float> gain;                                                    // declare gain

    // saw eq: return x / juce::MathConstants<float>::pi;
    // square eq: return x < 0.0f ? -1.0f : 1.0f;

    //============================================================================== ADSR+
    juce::ADSR adsr;
    juce::ADSR::Parameters adsrParams;

    //============================================================================== Audio Buffer
    juce::AudioBuffer<float> sBuffer;
};
