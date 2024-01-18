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
class ADSRComp  : public juce::Component
{
public:
    ADSRComp(juce::AudioProcessorValueTreeState& apvts);
    ~ADSRComp() override;

    void paint (juce::Graphics&) override;
    void resized() override;


private:
    void setSlider(juce::Slider& s);
    juce::Slider aSlider;
    juce::Slider dSlider;
    juce::Slider sSlider;
    juce::Slider rSlider;

    using SliderAttachment = juce::AudioProcessorValueTreeState::SliderAttachment;

    std::unique_ptr<SliderAttachment> aAttachment;
    std::unique_ptr<SliderAttachment> dAttachment;
    std::unique_ptr<SliderAttachment> sAttachment;
    std::unique_ptr<SliderAttachment> rAttachment;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ADSRComp)
};
