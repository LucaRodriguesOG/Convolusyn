/*
  ==============================================================================

    Synth.h
    Created: 18 Jul 2023 12:10:52pm
    Author:  Luca Rodrigues

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class Sounds : public juce::SynthesiserSound {
    
public:
    bool appliesToNote(int midiNoteNumber) override { return true; }
    bool appliesToChannel(int midiChannel) override { return true; }

private:
};

class Voices : public juce::SynthesiserVoice {

public:
    bool canPlaySound(juce::SynthesiserSound* sound) override;
    void startNote(int midiNoteNumber, float velocity, juce::SynthesiserSound* sound, int currentPitchWheelPosition) override;
    void stopNote(float velocity, bool allowTailOff) override;
    void pitchWheelMoved(int newPitchWheelValue) override;
    void controllerMoved(int controllerNumber, int newControllerValue) override;
    void renderNextBlock(juce::AudioBuffer<float>& outputBuffer, int startSample, int numSamples) override;

private:
};
