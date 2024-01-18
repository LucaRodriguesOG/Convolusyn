/*
  ==============================================================================

    ADSRData.h
    Created: 18 Jan 2024 1:40:03pm
    Author:  Luca

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class ADSRData : public juce::ADSR
{
public: 
    void updateADSR(const float a, const float d, const float s, const float r);

private: 
    juce::ADSR::Parameters adsrParams;
};