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
ADSRComp::ADSRComp(juce::AudioProcessorValueTreeState& apvts)
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.
    // 
    // ADSR
    using SliderAttachment = juce::AudioProcessorValueTreeState::SliderAttachment;
    // ATTACK
    aAttachment = std::make_unique<SliderAttachment>(apvts, "ATTACK", aSlider);
    setSlider(aSlider);
    // DECAY
    dAttachment = std::make_unique<SliderAttachment>(apvts, "DECAY", dSlider);
    setSlider(dSlider);
    // SUSTAIN
    sAttachment = std::make_unique<SliderAttachment>(apvts, "SUSTAIN", sSlider);
    setSlider(sSlider);
    // RELEASE
    rAttachment = std::make_unique<SliderAttachment>(apvts, "RELEASE", rSlider);
    setSlider(rSlider);
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
    //g.drawRect (getLocalBounds(), 1);   // draw an outline around the component

    //g.setColour (juce::Colours::white);
    //g.setFont (14.0f);
    //g.drawText ("ADSRComp", getLocalBounds(),
    //            juce::Justification::centred, true);   // draw some placeholder text

    g.fillAll(juce::Colours::black);
}

void ADSRComp::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..
    const auto bounds = getLocalBounds().reduced(10);
    const auto pad = 10;
    const auto sliderWidth = bounds.getWidth() / 16 - pad;
    const auto sliderHeight = bounds.getHeight() / 8 - pad;
    const auto sliderStartX = 0;
    const auto sliderStartY = bounds.getHeight() - pad * 8;//(sliderHeight / 2);

    //gSlider.setBounds(getWidth() - 50, 25, 20, 100);
    aSlider.setBounds(sliderStartX + pad, sliderStartY, sliderWidth, sliderHeight);
    dSlider.setBounds(aSlider.getRight() + pad, sliderStartY, sliderWidth, sliderHeight);
    sSlider.setBounds(dSlider.getRight() + pad, sliderStartY, sliderWidth, sliderHeight);
    rSlider.setBounds(sSlider.getRight() + pad, sliderStartY, sliderWidth, sliderHeight);
}

void ADSRComp::setSlider(juce::Slider& s) {
    s.setSliderStyle(juce::Slider::LinearBarVertical);
    //s.setRange(0.0, 1.0, .01);
    s.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 90, 90);
    s.setPopupDisplayEnabled(true, false, this);
    //s.setTextValueSuffix(" Attack");
    s.setValue(100);

    addAndMakeVisible(&s);
}