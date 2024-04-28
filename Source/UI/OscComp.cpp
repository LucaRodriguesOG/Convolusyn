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
OscComp::OscComp(juce::AudioProcessorValueTreeState& apvts, juce::String name, juce::String waveID)
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.

    juce::StringArray choices{ "Sine", "Saw", "Square" };
    oscWaveBox.addItemList(choices, 1);
    addAndMakeVisible(oscWaveBox);
    oscWaveAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ComboBoxAttachment>(apvts, waveID, oscWaveBox);

    setSliderAndLabel(apvts, juce::String { "FMAMT" }, fmAmtSlider, fmAmtLabel, fmAmtAttachment);
    setSliderAndLabel(apvts, juce::String{ "FMFREQ" }, fmFreqSlider, fmFreqLabel, fmFreqAttachment);

    this->name = name;
}

OscComp::~OscComp()
{
}

void OscComp::paint (juce::Graphics& g)
{
    juce::Colour c1 = juce::Colour::Colour::fromFloatRGBA(0.0f, 0.5f, 0.3f, .7f);
    juce::Colour c2 = juce::Colour::Colour::fromFloatRGBA(0.5f, 0.0f, 0.5f, .7f);
    g.setGradientFill(juce::ColourGradient(c1, 0, 0, c2, getWidth(), getHeight(), false));
    g.fillRoundedRectangle(getLocalBounds().toFloat(), 50.0f);

    g.setColour(juce::Colours::white);
    g.drawRoundedRectangle(getLocalBounds().toFloat(), 50.0f, 1.0f);   // draw an outline around the component
    g.drawText(name, getLocalBounds().reduced(5), juce::Justification::centredTop);
}

void OscComp::resized()
{
    // TODO: set all widths and heights as variables for readability
    const auto pad = 10;

    oscWaveBox.setBounds(getWidth() * 1/4, 25, getWidth() / 2, getHeight() / 4 - pad);

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
