/*
  ==============================================================================

    ConvData.cpp
    Created: 30 Apr 2024 4:47:19pm
    Author:  Luca

  ==============================================================================
*/

#include "ConvData.h"

void ConvData::prepare(juce::dsp::ProcessSpec& spec)
{
    conv.reset();
    conv.prepare(spec);
    isPrepared = true;
}

void ConvData::loadFile(juce::File& file)
{
    conv.loadImpulseResponse(file, juce::dsp::Convolution::Stereo::yes, juce::dsp::Convolution::Trim::yes, 0, juce::dsp::Convolution::Normalise::yes);
}

void ConvData::process(juce::AudioBuffer<float>& buffer)
{
    jassert(isPrepared);

    juce::dsp::AudioBlock<float> block{ buffer };
    conv.process(juce::dsp::ProcessContextReplacing<float> { block });
}