/*
  ==============================================================================

    ConvData.h
    Created: 30 Apr 2024 4:47:19pm
    Author:  Luca

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class ConvData {
public:
    void prepare(juce::dsp::ProcessSpec& spec);
    void loadFile(juce::File& file);
    void process(juce::AudioBuffer<float>& buffer);

private:
    bool isPrepared{ false };
    juce::dsp::Convolution conv;
};
