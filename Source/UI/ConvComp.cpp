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

    this->name = name;
}

ConvComp::~ConvComp()
{
}

void ConvComp::paint (juce::Graphics& g)
{
    g.setColour(YELLOW);
    g.fillRoundedRectangle(getLocalBounds().toFloat(), 50.0f);

    g.setColour(juce::Colours::white);
    g.drawRoundedRectangle(getLocalBounds().toFloat(), 50.0f, 1.0f);   // draw an outline around the component
    g.drawText(name, getLocalBounds().reduced(5), juce::Justification::centredTop);
}

void ConvComp::resized()
{
    
    
    convButton.setBounds(15, 15, 25, 25);
}
