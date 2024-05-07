/*
  ==============================================================================

    LFOData.cpp
    Created: 30 Apr 2024 5:27:07pm
    Author:  Luca

  ==============================================================================
*/

#include "LFOData.h"

void LFOData::prepare(double sampleRate)
{
    this->sampleRate = sampleRate;

    for (int i = 0; i < waveSize; i++)
    {
        float temp = 2.0f * juce::MathConstants<float>::pi * i / float(waveSize);
        sine[i] = std::sin(temp);

        saw[i] = - i / float(waveSize);
        
        square[i] = (i < (waveSize / 2)) ? 0.0f : -1.0f;
    }

    wave = sine;
}

void LFOData::updateParams(const int wave, const float a, const float f)
{
    switch (wave)
    {
    case 0: // sine
        this->wave = sine;
        break;

    case 1: // saw
        this->wave = saw;
        break;

    case 2: // square
        this->wave = square;
        break;

    default:
        jassertfalse;
        break;
    }
    amt = a;
    freq = f;
    increment = freq * float(waveSize) / sampleRate; // added the 2.0 * pi lets see if good later
}

float LFOData::val() 
{
    float val = wave[int(phase)] * amt;
    phase = fmod(phase + increment, float(waveSize));
    return val;
}

void LFOData::resetPhase()
{
    phase = 0;
}