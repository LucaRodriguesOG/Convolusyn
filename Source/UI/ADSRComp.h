/*
  ==============================================================================

    ADSRComp.h
    Created: 18 Jan 2024 1:39:27pm
    Author:  Luca

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class ADSRComp : public juce::Component
{
public:
    ADSRComp(juce::AudioProcessorValueTreeState& apvts, juce::String name, juce::String aID, juce::String dID, juce::String sID, juce::String rID);
    ~ADSRComp() override;

    void paint (juce::Graphics&) override;
    void resized() override;


private:
    juce::Slider aSlider;
    juce::Slider dSlider;
    juce::Slider sSlider;
    juce::Slider rSlider;

    using SliderAttachment = juce::AudioProcessorValueTreeState::SliderAttachment;

    std::unique_ptr<SliderAttachment> aAttachment;
    std::unique_ptr<SliderAttachment> dAttachment;
    std::unique_ptr<SliderAttachment> sAttachment;
    std::unique_ptr<SliderAttachment> rAttachment;

    juce::Label aLabel{ "Attack", "A" };
    juce::Label dLabel{ "Decay", "D" };
    juce::Label sLabel{ "Sustain", "S" };
    juce::Label rLabel{ "Release", "R" };

    juce::String name{ "" };

    void setSliderAndLabel(juce::AudioProcessorValueTreeState& apvts, juce::String id, juce::Slider& slider,
        juce::Label& label, std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment>& attachment);

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ADSRComp)
};
