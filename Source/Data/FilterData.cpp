/*
  ==============================================================================

    FilterData.cpp
    Created: 26 Apr 2024 10:25:42am
    Author:  Luca

  ==============================================================================
*/

#include "FilterData.h"

void FilterData::prepareToPlay(juce::dsp::ProcessSpec& spec)
{
    filter.reset();
    filter.prepare(spec);
    isPrepared = true;
}

void FilterData::process(juce::AudioBuffer<float>& buffer)
{
    jassert(isPrepared);

    juce::dsp::AudioBlock<float> block{ buffer };
    filter.process(juce::dsp::ProcessContextReplacing<float> { block });
}

void FilterData::updateParams(const int type, const float freq, const float res, const float lfo)
{
    switch (type)
    {
        case 0:
            filter.setType(juce::dsp::StateVariableTPTFilterType::lowpass);
            break;
        case 1:
            filter.setType(juce::dsp::StateVariableTPTFilterType::highpass);
            break;
        case 2:
            filter.setType(juce::dsp::StateVariableTPTFilterType::bandpass);
            break;
    }

    float lfoFreq = freq + lfo;
    lfoFreq = std::fmax(lfoFreq, 20.0f);
    lfoFreq = std::fmin(lfoFreq, 20000.0f);

    filter.setCutoffFrequency(lfoFreq);
    filter.setResonance(res);
}

void FilterData::reset()
{
    filter.reset();
}