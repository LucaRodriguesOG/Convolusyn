/*
  ==============================================================================

    ADSRData.cpp
    Created: 18 Jan 2024 1:40:03pm
    Author:  Luca

  ==============================================================================
*/

#include "ADSRData.h"

void ADSRData::updateADSR(const float a, const float d, const float s, const float r) {

    adsrParams.attack = a;                       // sets adsr parameters
    adsrParams.decay = d;
    adsrParams.sustain = s;
    adsrParams.release = r;

    setParameters(adsrParams);                   // apply parameters to adsr
};