/*
  ==============================================================================

    Synth.cpp
    Created: 18 Jul 2023 12:10:52pm
    Author:  Luca Rodrigues

  ==============================================================================
*/

#include "Synth.h"
#include <JuceHeader.h>

bool Voice::canPlaySound(juce::SynthesiserSound* sound) {
    return dynamic_cast<juce::SynthesiserSound*>(sound) != nullptr;
}

void Voice::startNote(int midiNoteNumber, float velocity, juce::SynthesiserSound* sound, int currentPitchWheelPosition) {

}

void Voice::stopNote(float velocity, bool allowTailOff) {

}

void Voice::pitchWheelMoved(int newPitchWheelValue) {

}

void Voice::controllerMoved(int controllerNumber, int newControllerValue) {

}

void Voice::renderNextBlock(juce::AudioBuffer<float>& outputBuffer, int startSample, int numSamples) {

}