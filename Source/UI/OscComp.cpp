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
OscComp::OscComp(juce::AudioProcessorValueTreeState& apvts)
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.

    juce::StringArray choices{ "Sine", "Saw", "Square" };
    oscWaveBox.addItemList(choices, 1);
    addAndMakeVisible(oscWaveBox);
    oscWaveAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ComboBoxAttachment>(apvts, "OSC1WAVETYPE", oscWaveBox);
    oscWaveLabel.setColour(juce::Label::ColourIds::textColourId, juce::Colours::white);
    oscWaveLabel.setJustificationType(juce::Justification::centred);
    oscWaveLabel.setFont(15.0f);
    addAndMakeVisible(oscWaveLabel);

    setSliderAndLabel(apvts, juce::String { "FMAMT" }, fmAmtSlider, fmAmtLabel, fmAmtAttachment);
    setSliderAndLabel(apvts, juce::String{ "FMFREQ" }, fmFreqSlider, fmFreqLabel, fmFreqAttachment);
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
    g.drawRect (getLocalBounds(), 1);   // draw an outline around the component

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

    // TODO: set all widths and heights as variables for readability
    const auto pad = 10;

    oscWaveBox.setBounds(getWidth() * 1/4, 25, getWidth() / 2, getHeight() / 4 - pad);
    oscWaveLabel.setBounds(oscWaveBox.getX(), oscWaveBox.getY() - 25, oscWaveBox.getWidth(), 15);

    fmAmtSlider.setBounds(getWidth() * 1/4, getHeight() / 2, getWidth() / 4, getHeight() / 2 - pad);
    fmAmtLabel.setBounds(fmAmtSlider.getX(), fmAmtSlider.getY() - 11, fmAmtSlider.getWidth(), 15);

    fmFreqSlider.setBounds(getWidth() * 2/4, getHeight() / 2, getWidth() / 4, getHeight() / 2 - pad);
    fmFreqLabel.setBounds(fmFreqSlider.getX(), fmFreqSlider.getY() - 11, fmFreqSlider.getWidth(), 15);

}

void OscComp::setSliderAndLabel(juce::AudioProcessorValueTreeState& apvts, juce::String id, juce::Slider& slider, 
    juce::Label& label, std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment>& attachment)
{
    slider.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    slider.setRotaryParameters(0, juce::MathConstants<float>::pi * 2 / 3, true);
    slider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 100, 15);
    addAndMakeVisible(slider);
    attachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(apvts, id, slider);
    label.setColour(juce::Label::ColourIds::textColourId, juce::Colours::white);
    label.setJustificationType(juce::Justification::centred);
    label.setFont(15.0f);
    addAndMakeVisible(label);
}
