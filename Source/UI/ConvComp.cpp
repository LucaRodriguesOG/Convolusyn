/*
  ==============================================================================

    ConvComp.cpp
    Created: 30 Apr 2024 4:47:00pm
    Author:  Luca

  ==============================================================================
*/

#include <JuceHeader.h>
#include "ConvComp.h"

//==============================================================================
ConvComp::ConvComp(juce::AudioProcessorValueTreeState& apvts, juce::String name)
{
    convButton.setToggleable(true);
    addAndMakeVisible(convButton);
    convButtonAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ButtonAttachment>(apvts, "CONVBUTTON", convButton);

    addAndMakeVisible(fileName);

    /*wildcard = juce::WildcardFileFilter(juce::String("*.wav;*.mp3"), juce::String(), "Audio Files");
    browser = juce::FileBrowserComponent(juce::FileBrowserComponent::canSelectFiles, juce::File(), wildcard, nullptr);
    fileChooser = juce::FileChooserDialogBox("Open File", "Please Choose a File", browser, true, WHITE);*/
    //addAndMakeVisible(fileChooser);

    this->name = name;
}

ConvComp::~ConvComp()
{
}

void ConvComp::paint (juce::Graphics& g)
{
    g.setColour(ORANGE);
    g.fillRoundedRectangle(getLocalBounds().toFloat(), 50.0f);

    g.setColour(juce::Colours::white);
    g.drawRoundedRectangle(getLocalBounds().toFloat(), 50.0f, 1.0f);   // draw an outline around the component
    g.drawText(name, getLocalBounds().reduced(5), juce::Justification::centredTop);

    //g.drawText(fileName.getText(), getLocalBounds(), juce::Justification::centred);
}

void ConvComp::resized()
{
    convButton.setBounds(15, 15, 25, 25);
    fileName.setBounds(getLocalBounds().reduced(50));
    fileName.setJustificationType(juce::Justification::centred);
}

void ConvComp::setFileName(const juce::String file)
{
    auto name = file.substring(file.lastIndexOf("\\")+1, file.length());
    fileName.setText(name, juce::dontSendNotification);
    juce::Logger::writeToLog(juce::String(fileName.getText()));
}
