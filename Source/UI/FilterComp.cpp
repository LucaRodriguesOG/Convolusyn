/*
  ==============================================================================

    FilterComp.cpp
    Created: 26 Apr 2024 11:14:05am
    Author:  Luca

  ==============================================================================
*/

#include <JuceHeader.h>
#include "FilterComp.h"

//==============================================================================
FilterComp::FilterComp(juce::AudioProcessorValueTreeState& apvts, juce::String name)
{
    juce::StringArray choices{ "Lowpass", "Highpass", "Bandpass" };
    filterTypeBox.addItemList(choices, 1);
    addAndMakeVisible(filterTypeBox);
    filterTypeAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ComboBoxAttachment>(apvts, "FILTERTYPE", filterTypeBox);

    setSliderAndLabel(apvts, juce::String{ "FILTERCUTOFF" }, filterCutoffSlider, filterCutoffLabel, filterCutoffAttachment);
    setSliderAndLabel(apvts, juce::String{ "FILTERRESONANCE" }, filterResonanceSlider, filterResonanceLabel, filterResonanceAttachment);

    filterButton.setToggleable(true);
    filterButton.setColour(juce::ToggleButton::ColourIds::tickColourId, juce::Colour::Colour::fromFloatRGBA(0.0f, 1.0f, 1.0f, 1.0f));
    addAndMakeVisible(filterButton);
    filterButtonAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ButtonAttachment>(apvts, "FILTERBUTTON", filterButton);
    /*filterButton.onClick = [this]
        {
            on = !on;
        };*/

    this->name = name;
}

FilterComp::~FilterComp()
{
}

void FilterComp::paint (juce::Graphics& g)
{   
    /*if (on)
    {
        juce::Colour c1 = juce::Colour::Colour::fromFloatRGBA(0.0f, 0.5f, 0.3f, .7f);
        juce::Colour c2 = juce::Colour::Colour::fromFloatRGBA(0.5f, 0.0f, 0.5f, .7f);
        g.setGradientFill(juce::ColourGradient(c1, 0, 0, c2, getWidth(), getHeight(), false));
        g.fillAll();
    }
    else
    {
        g.fillAll(juce::Colour::Colour::fromFloatRGBA(0.1f, 0.1f, 0.1f, 1.0f));
    }*/
    
    juce::Colour c1 = juce::Colour::Colour::fromFloatRGBA(0.0f, 0.5f, 0.3f, .7f);
    juce::Colour c2 = juce::Colour::Colour::fromFloatRGBA(0.5f, 0.0f, 0.5f, .7f);
    g.setGradientFill(juce::ColourGradient(c1, 0, 0, c2, getWidth(), getHeight(), false));
    g.fillRoundedRectangle(getLocalBounds().toFloat(), 50.0f);

    g.setColour(juce::Colours::white);
    g.drawRoundedRectangle(getLocalBounds().toFloat(), 50.0f, 1.0f);   // draw an outline around the component
    g.drawText(name, getLocalBounds().reduced(5), juce::Justification::centredTop);
}

void FilterComp::resized()
{
    // TODO: set all widths and heights as variables for readability
    const auto pad = 10;

    filterTypeBox.setBounds(getWidth() * 1 / 4, 25, getWidth() / 2, getHeight() / 4 - pad);

    filterCutoffSlider.setBounds(getWidth() * 1 / 4, getHeight() / 2, getWidth() / 4, getHeight() / 2 - pad);
    filterCutoffLabel.setBounds(filterCutoffSlider.getX(), filterCutoffSlider.getY() - 11, filterCutoffSlider.getWidth(), 15);

    filterResonanceSlider.setBounds(getWidth() * 2 / 4, getHeight() / 2, getWidth() / 4, getHeight() / 2 - pad);
    filterResonanceLabel.setBounds(filterResonanceSlider.getX(), filterResonanceSlider.getY() - 11, filterResonanceSlider.getWidth(), 15);

    filterButton.setBounds(15, 15, 25, 25);
}

void FilterComp::setSliderAndLabel(juce::AudioProcessorValueTreeState& apvts, juce::String id, juce::Slider& slider,
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