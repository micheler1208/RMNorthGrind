/*
  ==============================================================================

    NoiseGateData.h
    Author:  micheler1208

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class NoiseGateData
{
public:
    NoiseGateData();
    void prepareToPlay();
    void process(juce::AudioBuffer<float>& buffer);
    void updateValue(float newThreshold);
    void reset();

private:
    bool isPrepared { false };
    float sampleRate;
    float threshold;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(NoiseGateData)
};