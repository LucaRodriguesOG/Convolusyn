/*
  ==============================================================================

    OscComp.h
    Created: 22 Apr 2024 12:30:42pm
    Author:  Luca

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "UI_Global.h"

//==============================================================================
class OscComp  : public juce::Component
{
public:
    OscComp(juce::AudioProcessorValueTreeState& apvts, juce::String name, juce::String waveID);
    ~OscComp() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    juce::ComboBox oscWaveBox;
    juce::Slider fmAmtSlider;
    juce::Slider fmFreqSlider;

    std::unique_ptr<juce::AudioProcessorValueTreeState::ComboBoxAttachment> oscWaveAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> fmAmtAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> fmFreqAttachment;
    
    juce::Label fmAmtLabel{ "FM Amt", "FM Amt" };
    juce::Label fmFreqLabel{ "FM Freq", "FM Freq" };

    juce::String name{ "" }; 

    void setSliderAndLabel(juce::AudioProcessorValueTreeState& apvts, juce::String id, juce::Slider& slider, 
        juce::Label& label, std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment>& attachment);

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (OscComp)
};
