/*
  ==============================================================================

    GrindData.h
    Author:  micheler1208

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class GrindData
{
public:
    void prepareToPlay(juce::dsp::ProcessSpec spec);
    void process(juce::AudioBuffer<float>& buffer);
    void updateValue(float newGain);
    void reset();

private:
    bool isPrepared { false };
    float grind;

    juce::dsp::ProcessorChain<juce::dsp::Gain<float>, juce::dsp::IIR::Filter<float>, juce::dsp::IIR::Filter<float>> EQ;
    void updateFilters();

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(GrindData)
};