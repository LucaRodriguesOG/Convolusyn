/*
  ==============================================================================

    FilterComp.h
    Created: 26 Apr 2024 11:14:05am
    Author:  Luca

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class FilterComp  : public juce::Component
{
public:
    FilterComp(juce::AudioProcessorValueTreeState& apvts);
    ~FilterComp() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:

    juce::ComboBox filterTypeBox;
    juce::Slider filterCutoffSlider;
    juce::Slider filterResonanceSlider;

    std::unique_ptr<juce::AudioProcessorValueTreeState::ComboBoxAttachment> filterTypeAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> filterCutoffAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> filterResonanceAttachment;

    juce::Label filterTypeLabel{ "Filter Type", "Filter" };
    juce::Label filterCutoffLabel{ "Filter Cutoff", "Cutoff" };
    juce::Label filterResonanceLabel{ "Filter Resonance", "Resonance" };

    void setSliderAndLabel(juce::AudioProcessorValueTreeState& apvts, juce::String id, juce::Slider& slider,
        juce::Label& label, std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment>& attachment);

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FilterComp)
};
