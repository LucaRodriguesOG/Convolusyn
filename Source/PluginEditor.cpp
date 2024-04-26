/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
ConvolusynAudioProcessorEditor::ConvolusynAudioProcessorEditor (ConvolusynAudioProcessor& p)
    : AudioProcessorEditor (&p), 
    audioProcessor (p),
    osc (audioProcessor.apvts), 
    adsr(audioProcessor.apvts, "ADSR", "ATTACK", "DECAY", "SUSTAIN", "RELEASE"),
    filter(audioProcessor.apvts),
    lfoADSR(audioProcessor.apvts, "LFO ADSR", "LFOATTACK", "LFODECAY", "LFOSUSTAIN", "LFORELEASE")
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize(800, 600);

    // GAIN
    // setSlider(gSlider);

    // OSC
    addAndMakeVisible(osc);

    // ADSR
    addAndMakeVisible(adsr);

    // FILTER
    addAndMakeVisible(filter);

    // LFO
    addAndMakeVisible(lfoADSR);

}

ConvolusynAudioProcessorEditor::~ConvolusynAudioProcessorEditor()
{
}

//==============================================================================
void ConvolusynAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.setColour (juce::Colours::white);
    g.setFont (15.0f);
    //g.drawFittedText ("Volume", (getWidth() / 2) - 40, 0, getWidth(), 30, juce::Justification::centred, 1); // FIXME: location of volume text
}

void ConvolusynAudioProcessorEditor::resized()
{   
    int pad = 10;

    // Oscillator
    osc.setBounds(pad, pad, getWidth() * 2 / 4 - pad, getHeight() / 4 - pad);

    // ADSR
    adsr.setBounds(pad, getHeight() * 3 / 4, getWidth() * 2 / 4 - pad, getHeight() / 4 - pad);

    // Filter
    filter.setBounds(getWidth() * 2 / 4, getHeight() * 3 / 4, getWidth() * 2 / 4 - pad, getHeight() / 4 - pad);

    // LFO
    lfoADSR.setBounds(getWidth() * 2 / 4, pad, getWidth() * 2 / 4 - pad, getHeight() / 4 - pad);
}
