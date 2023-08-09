/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
ConvolusynAudioProcessorEditor::ConvolusynAudioProcessorEditor (ConvolusynAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (800, 600);

    // GAIN
    setSlider(gSlider);

    // OSC
    oscAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ComboBoxAttachment>(audioProcessor.apvts, "OSC", oscSelect);

    // ADSR
    using SliderAttachment = juce::AudioProcessorValueTreeState::SliderAttachment;
    // ATTACK
    aAttachment = std::make_unique<SliderAttachment>(audioProcessor.apvts, "ATTACK", aSlider);
    setSlider(aSlider);
    // DECAY
    dAttachment = std::make_unique<SliderAttachment>(audioProcessor.apvts, "DECAY", dSlider);
    setSlider(dSlider);
    // SUSTAIN
    sAttachment = std::make_unique<SliderAttachment>(audioProcessor.apvts, "SUSTAIN", sSlider);
    setSlider(sSlider);
    // RELEASE
    rAttachment = std::make_unique<SliderAttachment>(audioProcessor.apvts, "RELEASE", rSlider);
    setSlider(rSlider);

}

void ConvolusynAudioProcessorEditor::setSlider(juce::Slider& s) {
    s.setSliderStyle(juce::Slider::LinearBarVertical);
    //s.setRange(0.0, 1.0, .01);
    s.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 90, 90);
    s.setPopupDisplayEnabled(true, false, this);
    //s.setTextValueSuffix(" Attack");
    s.setValue(100);

    addAndMakeVisible(&s);
}

ConvolusynAudioProcessorEditor::~ConvolusynAudioProcessorEditor()
{
}

//==============================================================================
void ConvolusynAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.setColour (juce::Colours::white);
    g.setFont (15.0f);
    //g.drawFittedText ("Volume", (getWidth() / 2) - 40, 0, getWidth(), 30, juce::Justification::centred, 1); // FIXME: location of volume text
}

void ConvolusynAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
    
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
