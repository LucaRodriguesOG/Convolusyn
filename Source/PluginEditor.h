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

    //============================================================================== Oscillators+

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    ConvolusynAudioProcessor& audioProcessor;

    //============================================================================== Sliders
    juce::Slider midivol;

    //============================================================================== OSC

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ConvolusynAudioProcessorEditor)
};
