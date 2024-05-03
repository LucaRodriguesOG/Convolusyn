/*
  ==============================================================================

    LFOData.h
    Created: 30 Apr 2024 5:27:07pm
    Author:  Luca

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class LFOData {
public:
    void prepare(double sampleRate);
    void updateParams(const int wave, const float a, const float f);
    float val();
private:
    float amt{ 0.0f };
    float freq{ 0.0f };
    float sampleRate{ 0.0f };
    float increment{ 0.0f };
    float phase{ 0.0f };
    int waveSize{ 1024 };

    std::vector<float> sine = std::vector<float>(waveSize);
    std::vector<float> saw = std::vector<float>(waveSize);
    std::vector<float> square = std::vector<float>(waveSize);
    std::vector<float> wave = std::vector<float>(waveSize);
};