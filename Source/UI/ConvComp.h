/*
  ==============================================================================

    ConvComp.h
    Created: 30 Apr 2024 4:47:00pm
    Author:  Luca

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "UI_Global.h"

//==============================================================================
/*
*/
class ConvComp  : public juce::Component
{
public:
    ConvComp(juce::AudioProcessorValueTreeState& apvts, juce::String name);
    ~ConvComp() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:

    juce::ToggleButton convButton;

    std::unique_ptr<juce::AudioProcessorValueTreeState::ButtonAttachment> convButtonAttachment;

    juce::String name{ "" };

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ConvComp)
};
