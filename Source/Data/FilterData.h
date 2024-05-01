/*
  ==============================================================================

    FilterData.h
    Created: 26 Apr 2024 10:25:42am
    Author:  Luca

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "LFOData.h"

class FilterData
{
public:
    void prepareToPlay(double sampleRate, int samplesPerBlock, int numChannels);
    void process(juce::AudioBuffer<float>& buffer);
    void updateParams(const int type, const float freq, const float res, const float lfo = 1.0f);
    void reset();
private:
    juce::dsp::StateVariableTPTFilter<float> filter;
    bool isPrepared{ false };

    LFOData lfo;
};