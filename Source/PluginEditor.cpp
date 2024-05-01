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
    osc(audioProcessor.apvts, "OSC 1", "OSC1WAVETYPE"),
    adsr(audioProcessor.apvts, "OSC ADSR", "ATTACK", "DECAY", "SUSTAIN", "RELEASE"),
    filter(audioProcessor.apvts, "FILTER"),
    lfo(audioProcessor.apvts, "FILTER LFO"),
    conv(audioProcessor.apvts, "CONVOLUTION")
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize(800, 600);

    // LookAndFeel
    getLookAndFeel().setColour(juce::Slider::thumbColourId, WHITE);
    getLookAndFeel().setColour(juce::Slider::rotarySliderFillColourId, GREY);
    getLookAndFeel().setColour(juce::Slider::rotarySliderOutlineColourId, DARK_GREY);

    getLookAndFeel().setColour(juce::ComboBox::backgroundColourId, WHITE);
    getLookAndFeel().setColour(juce::ComboBox::textColourId, DARK_GREY);
    getLookAndFeel().setColour(juce::ComboBox::outlineColourId, WHITE);
    getLookAndFeel().setColour(juce::ComboBox::arrowColourId, GREY);

    getLookAndFeel().setColour(juce::Label::textColourId, WHITE);

    getLookAndFeel().setColour(juce::ToggleButton::tickColourId, DARK_GREY);
    getLookAndFeel().setColour(juce::ToggleButton::tickDisabledColourId, WHITE);

    getLookAndFeel().setColour(juce::PopupMenu::backgroundColourId, WHITE);
    getLookAndFeel().setColour(juce::PopupMenu::textColourId, DARK_GREY);
    getLookAndFeel().setColour(juce::PopupMenu::highlightedBackgroundColourId, GREY);

    // GAIN
    //addAndMakeVisible(gain);

    // OSC
    addAndMakeVisible(osc);

    // ADSR
    addAndMakeVisible(adsr);

    // FILTER
    addAndMakeVisible(filter);

    // LFO
    addAndMakeVisible(lfo);

    // CONV
    addAndMakeVisible(conv);
}

ConvolusynAudioProcessorEditor::~ConvolusynAudioProcessorEditor()
{
}

//==============================================================================
void ConvolusynAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    //g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));
    g.fillAll(DARK_GREY);
    /*juce::Colour c1 = juce::Colour::Colour::fromFloatRGBA(0.0f, 0.5f, 0.3f, .7f);
    juce::Colour c2 = juce::Colour::Colour::fromFloatRGBA(0.5f, 0.0f, 0.5f, .7f);
    g.setGradientFill(juce::ColourGradient(c1, 0, 0, c2, getWidth(), getHeight(), false));
    g.fillRoundedRectangle(getLocalBounds().toFloat(), 50.0f);*/
}

void ConvolusynAudioProcessorEditor::resized()
{   
    int padW = 10;
    int padH = 10;
    int moduleWidth = getWidth() / 3 - padW * 2;
    int moduleHeight = getHeight() / 3 - padH * 2;

    // Oscillator
    osc.setBounds(padW, padH, moduleWidth, moduleHeight);

    // ADSR
    adsr.setBounds(padW, getHeight() - moduleHeight - padH, moduleWidth, moduleHeight);

    // Filter
    filter.setBounds(getWidth() - moduleWidth - padW, padH, moduleWidth, moduleHeight);

    // LFO
    lfo.setBounds(getWidth() - moduleWidth - padW, getHeight() - moduleHeight - padH, moduleWidth, moduleHeight);

    // Convolution
    conv.setBounds(padW, moduleHeight + padH * 3, moduleWidth*3 + padW * 4, moduleHeight);
}
