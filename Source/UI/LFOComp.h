/*
  ==============================================================================

    LFOComp.h
    Created: 30 Apr 2024 5:27:30pm
    Author:  Luca

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "UI_Global.h"

//==============================================================================
/*
*/
class LFOComp  : public juce::Component
{
public:
    LFOComp(juce::AudioProcessorValueTreeState& apvts, juce::String name);
    ~LFOComp() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:

    juce::String name{ "" };

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (LFOComp)
};
