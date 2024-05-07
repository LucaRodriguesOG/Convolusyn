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

    juce::ComboBox lfoTypeBox;
    juce::Slider lfoAmtSlider;
    juce::Slider lfoFreqSlider;
    juce::ToggleButton lfoButton;
    juce::ToggleButton triggerButton;

    std::unique_ptr<juce::AudioProcessorValueTreeState::ComboBoxAttachment> lfoTypeAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> lfoAmtAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> lfoFreqAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::ButtonAttachment> lfoButtonAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::ButtonAttachment> triggerButtonAttachment;
    
    juce::Label lfoAmtLabel{ "LFO Amt", "Amt" };
    juce::Label lfoFreqLabel{ "LFO Freq", "Freq" };
    juce::Label triggerLabel{ "Trigger", "Trig" };
    
    juce::String name{ "" };

    void setSliderAndLabel(juce::AudioProcessorValueTreeState& apvts, juce::String id, juce::Slider& slider,
        juce::Label& label, std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment>& attachment);

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (LFOComp)
};
