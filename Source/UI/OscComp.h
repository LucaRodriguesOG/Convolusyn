/*
  ==============================================================================

    OscComp.h
    Created: 22 Apr 2024 12:30:42pm
    Author:  Luca

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class OscComp  : public juce::Component
{
public:
    OscComp(juce::AudioProcessorValueTreeState& apvts, juce::String waveID, juce::String fmAmtID, juce::String fmFreqID);
    ~OscComp() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    juce::ComboBox oscWaveBox;
    std::unique_ptr<juce::AudioProcessorValueTreeState::ComboBoxAttachment> oscWaveAttachment;
    juce::Label oscWaveLabel{ "Osc Wave Box", "Oscillator 1" };

    juce::Slider fmAmtSlider;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> fmAmtAttachment;
    juce::Label fmAmtLabel{ "FM Amt", "FM Amt" };

    juce::Slider fmFreqSlider;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> fmFreqAttachment;
    juce::Label fmFreqLabel{ "FM Freq", "FM Freq" };

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (OscComp)
};
