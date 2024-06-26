/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "Synth.h"
#include "Data/ConvData.h"
#include "Data/LFOData.h"
#include "Data/FilterData.h"

//==============================================================================
/**
*/
class ConvolusynAudioProcessor  : public juce::AudioProcessor
                            #if JucePlugin_Enable_ARA
                             , public juce::AudioProcessorARAExtension
                            #endif
{
public:
    //==============================================================================
    ConvolusynAudioProcessor();
    ~ConvolusynAudioProcessor() override;

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    //==============================================================================
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;

    //==============================================================================
    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

    //============================================================================== Files
    void loadFile(const juce::String& file);
    juce::String getFileName();

    //============================================================================== Value Tree State
    //juce::AudioProcessorValueTreeState getAPVTS();
    juce::AudioProcessorValueTreeState apvts;

private:
    //============================================================================== Synth
    juce::Synthesiser synth;

    //============================================================================== Convolution
    ConvData convolution;
    
    //============================================================================== LFO
    LFOData lfo;

    //============================================================================== Filter
    FilterData filter;

    //============================================================================== Gain
    juce::dsp::Gain<float> gain;

    //============================================================================== Files
    juce::String fileName{ "" };

    //============================================================================== Value Tree State
    juce::AudioProcessorValueTreeState::ParameterLayout createParameters();

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ConvolusynAudioProcessor)
};
