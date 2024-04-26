/*
  ==============================================================================

    ADSRComp.cpp
    Created: 18 Jan 2024 1:39:27pm
    Author:  Luca

  ==============================================================================
*/

#include <JuceHeader.h>
#include "ADSRComp.h"

//==============================================================================
ADSRComp::ADSRComp(juce::AudioProcessorValueTreeState& apvts, juce::String name, juce::String aID, juce::String dID, juce::String sID, juce::String rID)
{    
    setSliderAndLabel(apvts, aID, aSlider, aLabel, aAttachment);
    setSliderAndLabel(apvts, dID, dSlider, dLabel, dAttachment);
    setSliderAndLabel(apvts, sID, sSlider, sLabel, sAttachment);
    setSliderAndLabel(apvts, rID, rSlider, rLabel, rAttachment);
    this->name = name;
}

ADSRComp::~ADSRComp()
{
}

void ADSRComp::paint (juce::Graphics& g)
{
    g.setColour(juce::Colours::white);
    g.drawRect(getLocalBounds(), 1);   // draw an outline around the component
    g.drawText(name, getLocalBounds().reduced(5), juce::Justification::centredTop);
}

void ADSRComp::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..
    const auto bounds = getLocalBounds();
    const auto pad = 10;
    const auto sliderWidth = bounds.getWidth() / 4 - pad;
    const auto sliderHeight = bounds.getHeight() / 2;
    const auto sliderStartX = pad / 2;
    const auto sliderStartY = bounds.getHeight() * 1 / 4;//bounds.getHeight() - pad * 8;//(sliderHeight / 2);

    aSlider.setBounds(sliderStartX, sliderStartY, sliderWidth, sliderHeight);
    aLabel.setBounds(aSlider.getX(), aSlider.getY(), aSlider.getWidth(), 15);

    dSlider.setBounds(aSlider.getRight() + pad, sliderStartY, sliderWidth, sliderHeight);
    dLabel.setBounds(dSlider.getX(), dSlider.getY(), dSlider.getWidth(), 15);

    sSlider.setBounds(dSlider.getRight() + pad, sliderStartY, sliderWidth, sliderHeight);
    sLabel.setBounds(sSlider.getX(), sSlider.getY(), sSlider.getWidth(), 15);

    rSlider.setBounds(sSlider.getRight() + pad, sliderStartY, sliderWidth, sliderHeight);
    rLabel.setBounds(rSlider.getX(), rSlider.getY(), rSlider.getWidth(), 15);
}

void ADSRComp::setSliderAndLabel(juce::AudioProcessorValueTreeState& apvts, juce::String id, juce::Slider& slider,
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