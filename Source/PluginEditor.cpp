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
    gSlider.setSliderStyle(juce::Slider::LinearBarVertical);
    gSlider.setRange(0.0, 100.0, 1.0);
    gSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 90, 90);
    gSlider.setPopupDisplayEnabled(true, false, this);
    gSlider.setTextValueSuffix(" Volume");
    gSlider.setValue(100);

    addAndMakeVisible(&gSlider);

    // OSC
    oscAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ComboBoxAttachment>(audioProcessor.apvts, "OSC", oscSelect);

    // ADSR
    using SliderAttachment = juce::AudioProcessorValueTreeState::SliderAttachment;
    // ATTACK
    aAttachment = std::make_unique<SliderAttachment>(audioProcessor.apvts, "ATTACK", aSlider);
    // DECAY
    dAttachment = std::make_unique<SliderAttachment>(audioProcessor.apvts, "DECAY", dSlider);
    // SUSTAIN
    sAttachment = std::make_unique<SliderAttachment>(audioProcessor.apvts, "SUSTAIN", sSlider);
    // RELEASE
    rAttachment = std::make_unique<SliderAttachment>(audioProcessor.apvts, "RELEASE", rSlider);

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
    g.drawFittedText ("Volume", (getWidth() / 2) - 40, 0, getWidth(), 30, juce::Justification::centred, 1); // FIXME: location of volume text
}

void ConvolusynAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
    
    gSlider.setBounds(getWidth() - 50, 25, 20, 100);
}
