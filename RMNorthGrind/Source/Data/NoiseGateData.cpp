/*
  ==============================================================================

    NoiseGateData.cpp
    Author:  micheler1208

  ==============================================================================
*/

#include "NoiseGateData.h"

// COSTRUCTOR
NoiseGateData::NoiseGateData()
    : threshold(-80.0f)
{
}

// PREPARE TO PLAY
void NoiseGateData::prepareToPlay()
{
    reset();
    threshold = -80.0f;
    isPrepared = true;
}

// PROCESS NOISE GATE
void NoiseGateData::process(juce::AudioBuffer<float>& buffer)
{
    jassert(isPrepared);
    
    for (int channel = 0; channel < buffer.getNumChannels(); ++channel)
    {
        auto* channelData = buffer.getWritePointer(channel);

        for (int sample = 0; sample < buffer.getNumSamples(); ++sample)
        {
            if (juce::Decibels::gainToDecibels(channelData[sample]) < threshold)
            {
                channelData[sample] = 0.0f;
            }
        }
    }
}

void NoiseGateData::updateValue(float newThreshold)
{
    threshold = newThreshold;
}

// RESET
void NoiseGateData::reset()
{
    threshold = -80.0f;
}
