/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "UI/ADSRComp.h"
#include "UI/OscComp.h"
#include "UI/FilterComp.h"

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

    //============================================================================== OSC
    OscComp osc;

    //============================================================================== ADSR
    ADSRComp adsr;

    //============================================================================== Filter
    FilterComp filter;

    //============================================================================== LFO
    ADSRComp lfoADSR;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ConvolusynAudioProcessorEditor)
};
