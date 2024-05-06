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
    convolution(audioProcessor.apvts, "CONVOLUTION"),
    gain(audioProcessor.apvts, "GAIN")
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize(900, 600);

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

    // OSC
    addAndMakeVisible(osc);

    // ADSR
    addAndMakeVisible(adsr);

    // FILTER
    addAndMakeVisible(filter);

    // LFO
    addAndMakeVisible(lfo);

    // CONV
    addAndMakeVisible(convolution);
    
    // GAIN
    addAndMakeVisible(gain);
}

ConvolusynAudioProcessorEditor::~ConvolusynAudioProcessorEditor()
{
}

//==============================================================================
void ConvolusynAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    //g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));
    //g.fillAll(DARK_GREY);
    g.setGradientFill(juce::ColourGradient(BLACK, getWidth()/2, 0, DARK_GREY, getWidth()/2, getHeight()/16, false));
    g.fillRect(getLocalBounds());
    g.setColour(WHITE);
    g.setFont(getHeight() / 4);
    g.drawText("CONVOLUSYN", getLocalBounds(), juce::Justification::centred);
}

void ConvolusynAudioProcessorEditor::resized()
{   
    int padW = 10;
    int padH = 10;
    int moduleWidth = getWidth() / 3 - padW; // - padW * 2
    int moduleHeight = getHeight() / 3 - padH; // - padH * 2

    // Oscillator
    osc.setBounds(padW, padH, moduleWidth, moduleHeight);

    // ADSR
    adsr.setBounds(padW, padH*2 + moduleHeight*2, moduleWidth, moduleHeight);

    // Filter
    filter.setBounds(padW*2 + moduleWidth*2, padH, moduleWidth, moduleHeight);

    // LFO
    lfo.setBounds(padW*2 + moduleWidth*2, padH*2 + moduleHeight*2, moduleWidth, moduleHeight);

    // Convolution
    convolution.setBounds(padW*3/2 + moduleWidth, padH, moduleWidth, moduleHeight);

    // Gain
    gain.setBounds(padW*3/2 + moduleWidth, padH*2 + moduleHeight*2, moduleWidth, moduleHeight);
}

bool ConvolusynAudioProcessorEditor::isInterestedInFileDrag(const juce::StringArray& files)
{
    
    for (auto i : files)
    {
        if (i.contains(".wav") || i.contains(".mp3"))
        {
            //juce::Logger::writeToLog("IM INTERESTED!!!!!");
            return true;
        }
    }
    //juce::Logger::writeToLog("NOT INTERESTED...");
    return false;
}

void ConvolusynAudioProcessorEditor::filesDropped(const juce::StringArray& files, int x, int y)
{
    
    if (isInterestedInFileDrag(files))
    {
        for (auto i : files)
        {
            //juce::Logger::writeToLog("YOU DROPPED THIS");
            audioProcessor.loadFile(i);
            convolution.setFileName(i);
        }
    }
}