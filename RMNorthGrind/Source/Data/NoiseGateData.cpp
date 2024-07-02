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
void NoiseGateData::prepareToPlay(double newSampleRate)
{
    reset();
    sampleRate = newSampleRate;
    isPrepared = true;
}

// PROCESS NOISE GATE
void NoiseGateData::process(juce::AudioBuffer<float>& buffer)
{
    jassert(isPrepared);

    float attackCoeff = std::exp(-1.0f / (sampleRate * attackTime));
    float releaseCoeff = std::exp(-1.0f / (sampleRate * releaseTime));

    for (int channel = 0; channel < buffer.getNumChannels(); ++channel)
    {
        auto* channelData = buffer.getWritePointer(channel);

        for (int sample = 0; sample < buffer.getNumSamples(); ++sample)
        {
            calculateEnvelope(channelData[sample]);

            if (juce::Decibels::gainToDecibels(envelope) < threshold)
                currentGain *= releaseCoeff;
            else
                currentGain = 1.0f - (1.0f - currentGain) * attackCoeff;

            channelData[sample] *= currentGain;
        }
    }
}

void NoiseGateData::calculateEnvelope(float sample)
{
    float absSample = std::abs(sample);
    if (absSample > envelope)
        envelope = absSample + attackTime * (envelope - absSample);
    else
        envelope = absSample + releaseTime * (envelope - absSample);
}

void NoiseGateData::updateValue(float newThreshold)
{
    threshold = newThreshold;
}

// RESET
void NoiseGateData::reset()
{
    threshold = -80.0f;
    envelope = 0.0f;
    currentGain = 1.0f;
}
