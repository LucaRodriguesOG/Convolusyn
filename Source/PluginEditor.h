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
#include "UI/ConvComp.h"
#include "UI/LFOComp.h"
#include "UI/GainComp.h"

//==============================================================================
/**
*/
class ConvolusynAudioProcessorEditor  : public juce::AudioProcessorEditor,
                                        public juce::FileDragAndDropTarget
{
public:
    ConvolusynAudioProcessorEditor (ConvolusynAudioProcessor&);
    ~ConvolusynAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

    //==============================================================================
    bool isInterestedInFileDrag(const juce::StringArray& files) override;
    void filesDropped(const juce::StringArray& files, int x, int y) override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    ConvolusynAudioProcessor& audioProcessor;

    //============================================================================== OSC
    OscComp osc;

    //============================================================================== ADSR
    ADSRComp adsr;

    //============================================================================== Filter
    FilterComp filter;

    //============================================================================== LFO
    LFOComp lfo;

    //============================================================================== Convolution
    ConvComp conv;
    
    //============================================================================== Gain
    GainComp gain;

    //============================================================================== Files
    // TODO: see what dsp::convolution takes in, and if we can get the file data into that format, do all of this in audioProcessor.loadFile(juce::String&);

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ConvolusynAudioProcessorEditor)
};
