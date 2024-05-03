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
    juce::StringArray choices{ "Sine", "Saw", "Square" };
    lfoTypeBox.addItemList(choices, 1);
    addAndMakeVisible(lfoTypeBox);
    lfoTypeAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ComboBoxAttachment>(apvts, "LFOWAVETYPE", lfoTypeBox);

    setSliderAndLabel(apvts, juce::String{ "LFOAMT" }, lfoAmtSlider, lfoAmtLabel, lfoAmtAttachment);
    setSliderAndLabel(apvts, juce::String{ "LFOFREQ" }, lfoFreqSlider, lfoFreqLabel, lfoFreqAttachment);

    lfoButton.setToggleable(true);
    addAndMakeVisible(lfoButton);
    lfoButtonAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ButtonAttachment>(apvts, "LFOBUTTON", lfoButton);

    this->name = name;
}

LFOComp::~LFOComp()
{
}

void LFOComp::paint(juce::Graphics& g)
{
    g.setColour(PURPLE);
    g.fillRoundedRectangle(getLocalBounds().toFloat(), 50.0f);

    g.setColour(juce::Colours::white);
    g.drawRoundedRectangle(getLocalBounds().toFloat(), 50.0f, 1.0f);   // draw an outline around the component
    g.drawText(name, getLocalBounds().reduced(5), juce::Justification::centredTop);
}

void LFOComp::resized()
{
    // TODO: set all widths and heights as variables for readability
    const auto pad = 10;

    lfoTypeBox.setBounds(getWidth() * 1 / 4, 25, getWidth() / 2, getHeight() / 4 - pad);

    lfoFreqSlider.setBounds(getWidth() * 1 / 4, getHeight() / 2, getWidth() / 4, getHeight() / 2 - pad);
    lfoFreqLabel.setBounds(lfoFreqSlider.getX(), lfoFreqSlider.getY() - 11, lfoFreqSlider.getWidth(), 15);

    lfoAmtSlider.setBounds(getWidth() * 2 / 4, getHeight() / 2, getWidth() / 4, getHeight() / 2 - pad);
    lfoAmtLabel.setBounds(lfoAmtSlider.getX(), lfoAmtSlider.getY() - 11, lfoAmtSlider.getWidth(), 15);

    lfoButton.setBounds(15, 15, 25, 25);
}

void LFOComp::setSliderAndLabel(juce::AudioProcessorValueTreeState& apvts, juce::String id, juce::Slider& slider,
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
