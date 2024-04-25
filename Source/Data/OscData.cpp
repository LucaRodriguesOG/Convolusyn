/*
  ==============================================================================

    OscData.cpp
    Created: 22 Apr 2024 11:49:33am
    Author:  Luca

  ==============================================================================
*/

#include "OscData.h"

void OscData::prepareToPlay(juce::dsp::ProcessSpec& spec)
{
    fmOsc.prepare(spec);
    prepare(spec);
}

void OscData::setWaveType(const int wave) 
{
    switch (wave)
    {
        case 0: // sine
            initialise([](float x) { return std::sin(x); });
            break;

        case 1: // saw
            initialise([](float x) { return x / juce::MathConstants<float>::pi; });
            break;

        case 2: // square
            initialise([](float x) { return x < 0.0f ? -1.0f : 1.0f; });
            break;

        default:
            jassertfalse;
            break;
    }
}

void OscData::setWaveFrequency(const int midiNoteNumber) 
{
    setFrequency(juce::MidiMessage::getMidiNoteInHertz(midiNoteNumber) + fmMod);
    midiNote = midiNoteNumber;
}

void OscData::getNextAudioBlock(juce::dsp::AudioBlock<float>& block) 
{
    for (int i = 0; i < block.getNumChannels(); i++) 
    {
        for (int j = 0; j < block.getNumSamples(); j++) 
        {
            fmMod = fmOsc.processSample(block.getSample(i, j)) * fmAmt;
        }
    }

    process(juce::dsp::ProcessContextReplacing<float>(block));
}

void OscData::setFMParams(const float amt, const float freq) 
{
    fmOsc.setFrequency(freq);
    fmAmt = amt;
    setFrequency(juce::MidiMessage::getMidiNoteInHertz(midiNote) + fmMod);
}

