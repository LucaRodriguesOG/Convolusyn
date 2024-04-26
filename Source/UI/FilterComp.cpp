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
FilterComp::FilterComp(juce::AudioProcessorValueTreeState& apvts)
{
    juce::StringArray choices{ "Lowpass", "Highpass", "Bandpass" };
    filterTypeBox.addItemList(choices, 1);
    addAndMakeVisible(filterTypeBox);
    filterTypeAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ComboBoxAttachment>(apvts, "FILTERTYPE", filterTypeBox);
    filterTypeLabel.setColour(juce::Label::ColourIds::textColourId, juce::Colours::white);
    filterTypeLabel.setJustificationType(juce::Justification::centred);
    filterTypeLabel.setFont(15.0f);
    addAndMakeVisible(filterTypeLabel);

    setSliderAndLabel(apvts, juce::String{ "FILTERCUTOFF" }, filterCutoffSlider, filterCutoffLabel, filterCutoffAttachment);
    setSliderAndLabel(apvts, juce::String{ "FILTERRESONANCE" }, filterResonanceSlider, filterResonanceLabel, filterResonanceAttachment);
}

FilterComp::~FilterComp()
{
}

void FilterComp::paint (juce::Graphics& g)
{
    //g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));   // clear the background

    //g.setColour (juce::Colours::grey);
    g.drawRect (getLocalBounds(), 1);   // draw an outline around the component

    //g.setColour (juce::Colours::white);
    //g.setFont (14.0f);
    //g.drawText ("FilterComp", getLocalBounds(),
    //            juce::Justification::centred, true);   // draw some placeholder text
}

void FilterComp::resized()
{
    // TODO: set all widths and heights as variables for readability
    const auto pad = 10;

    filterTypeBox.setBounds(getWidth() * 1 / 4, 25, getWidth() / 2, getHeight() / 4 - pad);
    filterTypeLabel.setBounds(filterTypeBox.getX(), filterTypeBox.getY() - 25, filterTypeBox.getWidth(), 15);

    filterCutoffSlider.setBounds(getWidth() * 1 / 4, getHeight() / 2, getWidth() / 4, getHeight() / 2 - pad);
    filterCutoffLabel.setBounds(filterCutoffSlider.getX(), filterCutoffSlider.getY() - 11, filterCutoffSlider.getWidth(), 15);

    filterResonanceSlider.setBounds(getWidth() * 2 / 4, getHeight() / 2, getWidth() / 4, getHeight() / 2 - pad);
    filterResonanceLabel.setBounds(filterResonanceSlider.getX(), filterResonanceSlider.getY() - 11, filterResonanceSlider.getWidth(), 15);
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