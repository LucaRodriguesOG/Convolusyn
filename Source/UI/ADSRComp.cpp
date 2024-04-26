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
}

ADSRComp::~ADSRComp()
{
}

void ADSRComp::paint (juce::Graphics& g)
{
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */

    //g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));   // clear the background

    //g.setColour (juce::Colours::grey);
    g.drawRect (getLocalBounds(), 1);   // draw an outline around the component
    g.drawText(name, getLocalBounds(), juce::Justification::left);
    //g.setColour (juce::Colours::white);
    //g.setFont (14.0f);
    //g.drawText ("ADSRComp", getLocalBounds(),
    //            juce::Justification::centred, true);   // draw some placeholder text

    //g.fillAll(juce::Colours::black);
}

void ADSRComp::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..
    const auto bounds = getLocalBounds();
    const auto pad = 10;
    const auto sliderWidth = bounds.getWidth() / 4 - pad;
    const auto sliderHeight = bounds.getHeight() - pad;
    const auto sliderStartX = 0;
    const auto sliderStartY = 0;//bounds.getHeight() - pad * 8;//(sliderHeight / 2);

    //gSlider.setBounds(getWidth() - 50, 25, 20, 100);
    aSlider.setBounds(sliderStartX + pad, sliderStartY, sliderWidth, sliderHeight);
    aLabel.setBounds(aSlider.getX(), aSlider.getY(), aSlider.getWidth(), 15);

    dSlider.setBounds(aSlider.getRight(), sliderStartY, sliderWidth, sliderHeight);
    dLabel.setBounds(dSlider.getX(), dSlider.getY(), dSlider.getWidth(), 15);

    sSlider.setBounds(dSlider.getRight(), sliderStartY, sliderWidth, sliderHeight);
    sLabel.setBounds(sSlider.getX(), sSlider.getY(), sSlider.getWidth(), 15);

    rSlider.setBounds(sSlider.getRight(), sliderStartY, sliderWidth, sliderHeight);
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