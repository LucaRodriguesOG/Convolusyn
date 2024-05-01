/*
  ==============================================================================

    LFOComp.cpp
    Created: 30 Apr 2024 5:27:30pm
    Author:  Luca

  ==============================================================================
*/

#include <JuceHeader.h>
#include "LFOComp.h"

//==============================================================================
LFOComp::LFOComp(juce::AudioProcessorValueTreeState& apvts, juce::String name)
{

    this->name = name;
}

LFOComp::~LFOComp()
{
}

void LFOComp::paint (juce::Graphics& g)
{
    g.setColour(PURPLE);
    g.fillRoundedRectangle(getLocalBounds().toFloat(), 50.0f);

    g.setColour(juce::Colours::white);
    g.drawRoundedRectangle(getLocalBounds().toFloat(), 50.0f, 1.0f);   // draw an outline around the component
    g.drawText(name, getLocalBounds().reduced(5), juce::Justification::centredTop);
}

void LFOComp::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..

}
