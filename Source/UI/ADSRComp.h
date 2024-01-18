/*
  ==============================================================================

    ADSRComp.h
    Created: 18 Jan 2024 1:39:27pm
    Author:  Luca

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class ADSRComp  : public juce::Component
{
public:
    ADSRComp();
    ~ADSRComp() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ADSRComp)
};
