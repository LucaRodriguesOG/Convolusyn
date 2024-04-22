/*
  ==============================================================================

    OscComp.h
    Created: 22 Apr 2024 12:30:42pm
    Author:  Luca

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class OscComp  : public juce::Component
{
public:
    OscComp(juce::AudioProcessorValueTreeState& apvts, juce::String waveID);
    ~OscComp() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    juce::ComboBox oscWave;
    std::unique_ptr<juce::AudioProcessorValueTreeState::ComboBoxAttachment> oscWaveAttachment;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (OscComp)
};
