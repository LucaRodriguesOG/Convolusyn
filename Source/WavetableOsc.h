/*
  ==============================================================================

    WavetableOsc.h
    Created: 12 Jul 2023 11:38:01am
    Author:  Amuse

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class WavetableOsc {
public:
	WavetableOsc();
	WavetableOsc(const juce::AudioSampleBuffer& inUse) : wavetable(inUse)
	{
		jassert(wavetable.getNumChannels() == 1);
	}

private:
	const juce::AudioSampleBuffer& wavetable;
};
