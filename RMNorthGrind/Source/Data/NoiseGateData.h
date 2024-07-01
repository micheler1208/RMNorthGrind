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
    bool isPrepared{ false };
    float threshold;
    double sampleRate;

    float attackTime = 0.01f;  // 10 ms
    float releaseTime = 0.1f;  // 100 ms

    float currentGain = 1.0f;
    float envelope = 0.0f;

    void calculateEnvelope(float sample);
    void calculateGain();

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(NoiseGateData)
};