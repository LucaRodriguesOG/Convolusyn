/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class ConvolusynAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    ConvolusynAudioProcessorEditor (ConvolusynAudioProcessor&);
    ~ConvolusynAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    ConvolusynAudioProcessor& audioProcessor;

    //============================================================================== Gain
    juce::Slider gSlider;

    //============================================================================== OSC Select
    juce::ComboBox oscSelect;
    std::unique_ptr<juce::AudioProcessorValueTreeState::ComboBoxAttachment> oscAttachment;

    //============================================================================== ADSR
    using SliderAttachment = juce::AudioProcessorValueTreeState::SliderAttachment;

    juce::Slider aSlider;
    juce::Slider dSlider;
    juce::Slider sSlider;
    juce::Slider rSlider;
    std::unique_ptr<SliderAttachment> aAttachment;
    std::unique_ptr<SliderAttachment> dAttachment;
    std::unique_ptr<SliderAttachment> sAttachment;
    std::unique_ptr<SliderAttachment> rAttachment;
    

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ConvolusynAudioProcessorEditor)
};
