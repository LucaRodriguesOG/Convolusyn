/*
  ==============================================================================

    Synth.cpp
    Created: 18 Jul 2023 12:10:52pm
    Author:  Luca Rodrigues

  ==============================================================================
*/

#include "Synth.h"
#include <JuceHeader.h>

bool Voices::canPlaySound(juce::SynthesiserSound* sound) {

}

void Voices::startNote(int midiNoteNumber, float velocity, juce::SynthesiserSound* sound, int currentPitchWheelPosition) {

}

void Voices::stopNote(float velocity, bool allowTailOff) {

}

void Voices::pitchWheelMoved(int newPitchWheelValue) {

}

void Voices::controllerMoved(int controllerNumber, int newControllerValue) {

}

void Voices::renderNextBlock(juce::AudioBuffer<float>& outputBuffer, int startSample, int numSamples) {

}