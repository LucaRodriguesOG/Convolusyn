/*
  ==============================================================================

    GainComp.h
    Created: 3 May 2024 1:29:40pm
    Author:  Luca

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "UI_Global.h"

//==============================================================================
/*
*/
class GainComp  : public juce::Component
{
public:
    GainComp(juce::AudioProcessorValueTreeState& apvts, juce::String name);
    ~GainComp() override;

    void paint (juce::Graphics&) override;
    void resized() override;
    void setSliderAndLabel(juce::AudioProcessorValueTreeState& apvts, juce::String id, juce::Slider& slider,
        juce::Label& label, std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment>& attachment);
private:
    juce::Slider gainSlider;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> gainAttachment;
    juce::Label gainLabel{ "Gain", "Gain" };
    juce::String name;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (GainComp)
};
