/*
  ==============================================================================

    OscComp.cpp
    Created: 22 Apr 2024 12:30:42pm
    Author:  Luca

  ==============================================================================
*/

#include <JuceHeader.h>
#include "OscComp.h"

//==============================================================================
OscComp::OscComp(juce::AudioProcessorValueTreeState& apvts, juce::String waveID)
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.

    juce::StringArray choices{ "Sine", "Saw", "Square" };
    oscWave.addItemList(choices, 1);
    addAndMakeVisible(oscWave);

    oscWaveAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ComboBoxAttachment>(apvts, waveID, oscWave);

}

OscComp::~OscComp()
{
}

void OscComp::paint (juce::Graphics& g)
{
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */

    //g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));   // clear the background

    //g.setColour (juce::Colours::grey);
    //g.drawRect (getLocalBounds(), 1);   // draw an outline around the component

    //g.setColour (juce::Colours::white);
    //g.setFont (14.0f);
    //g.drawText ("OscComp", getLocalBounds(),
    //            juce::Justification::centred, true);   // draw some placeholder text

    //g.fillAll(juce::Colours::white);
}

void OscComp::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..

    oscWave.setBounds(0, 0, getWidth(), getHeight());

}
