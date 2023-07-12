#pragma once

#include <JuceHeader.h>

class WavetableOsc {
public:
	WavetableOsc(const juce::AudioSampleBuffer& inUse) : wavetable(inUse)
	{
		jassert(wavetable.getNumChannels() == 1);
	}

private:
	const juce::AudioSampleBuffer& wavetable;
};