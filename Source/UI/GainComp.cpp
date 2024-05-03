/*
  ==============================================================================

    GainComp.cpp
    Created: 3 May 2024 1:29:40pm
    Author:  Luca

  ==============================================================================
*/

#include <JuceHeader.h>
#include "GainComp.h"

//==============================================================================
GainComp::GainComp(juce::AudioProcessorValueTreeState& apvts, juce::String name)
{
    setSliderAndLabel(apvts, juce::String{ "GAIN" }, gainSlider, gainLabel, gainAttachment);
    this->name = name;
}

GainComp::~GainComp()
{
}

void GainComp::paint (juce::Graphics& g)
{
    g.setColour(SKY_BLUE);
    g.fillRoundedRectangle(getLocalBounds().toFloat(), 50.0f);

    g.setColour(juce::Colours::white);
    g.drawRoundedRectangle(getLocalBounds().toFloat(), 50.0f, 1.0f);   // draw an outline around the component
    g.drawText(name, getLocalBounds().reduced(5), juce::Justification::centredTop);
}

void GainComp::resized()
{
    const auto pad = 10;

    gainSlider.setBounds(getWidth() * 1 / 4, getHeight() * 1 / 4, getWidth() / 2, getHeight() / 2);
    //gainLabel.setBounds(gainSlider.getX(), gainSlider.getY() - 11, gainSlider.getWidth(), 15);
}

void GainComp::setSliderAndLabel(juce::AudioProcessorValueTreeState& apvts, juce::String id, juce::Slider& slider,
    juce::Label& label, std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment>& attachment)
{
    slider.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    slider.setRotaryParameters(0, juce::MathConstants<float>::pi * 2 / 3, true);
    slider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 100, 15);
    addAndMakeVisible(slider);
    attachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(apvts, id, slider);
    label.setJustificationType(juce::Justification::centred);
    label.setFont(15.0f);
    addAndMakeVisible(label);
}
