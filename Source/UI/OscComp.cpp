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
OscComp::OscComp(juce::AudioProcessorValueTreeState& apvts, juce::String waveID, juce::String fmAmtID, juce::String fmFreqID)
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.

    juce::StringArray choices{ "Sine", "Saw", "Square" };
    oscWaveBox.addItemList(choices, 1);
    addAndMakeVisible(oscWaveBox);
    oscWaveAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ComboBoxAttachment>(apvts, waveID, oscWaveBox);
    oscWaveLabel.setColour(juce::Label::ColourIds::textColourId, juce::Colours::white);
    oscWaveLabel.setJustificationType(juce::Justification::centred);
    oscWaveLabel.setFont(15.0f);
    addAndMakeVisible(oscWaveLabel);

    fmAmtSlider.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    fmAmtSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 100, 15);
    addAndMakeVisible(fmAmtSlider);
    fmAmtAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(apvts, fmAmtID, fmAmtSlider);
    fmAmtLabel.setColour(juce::Label::ColourIds::textColourId, juce::Colours::white);
    fmAmtLabel.setJustificationType(juce::Justification::centred);
    fmAmtLabel.setFont(15.0f);
    addAndMakeVisible(fmAmtLabel);



    fmFreqSlider.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    fmFreqSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 100, 15);
    addAndMakeVisible(fmFreqSlider);
    fmFreqAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(apvts, fmFreqID, fmFreqSlider);
    fmFreqLabel.setColour(juce::Label::ColourIds::textColourId, juce::Colours::white);
    fmFreqLabel.setJustificationType(juce::Justification::centred);
    fmFreqLabel.setFont(15.0f);
    addAndMakeVisible(fmFreqLabel);
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
    // components that your component contains...

    oscWaveBox.setBounds(getWidth() * 1/4, 25, getWidth() / 2, getHeight() / 4);
    oscWaveLabel.setBounds(oscWaveBox.getX(), oscWaveBox.getY() - 25, oscWaveBox.getWidth(), 15);

    fmAmtSlider.setBounds(getWidth() * 1/4, getHeight() / 2, getWidth() / 4, getHeight() / 2);
    fmAmtLabel.setBounds(fmAmtSlider.getX(), fmAmtSlider.getY() - 11, fmAmtSlider.getWidth(), 15);

    fmFreqSlider.setBounds(getWidth() * 2/4, getHeight() / 2, getWidth() / 4, getHeight() / 2);
    fmFreqLabel.setBounds(fmFreqSlider.getX(), fmFreqSlider.getY() - 11, fmFreqSlider.getWidth(), 15);

}
