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
    GrindData();
    void prepareToPlay(juce::dsp::ProcessSpec spec);
    void process(juce::AudioBuffer<float>& buffer);
    void updateValue(float newGain);
    void reset();

private:
    bool isPrepared { false };
    float grind;

    using Gain = juce::dsp::Gain<float>;
    using HighPassFilter = juce::dsp::ProcessorDuplicator<juce::dsp::IIR::Filter<float>, juce::dsp::IIR::Coefficients<float>>;
    using FixedEQFilter = juce::dsp::ProcessorDuplicator<juce::dsp::IIR::Filter<float>, juce::dsp::IIR::Coefficients<float>>;

    juce::dsp::ProcessorChain<Gain, HighPassFilter, FixedEQFilter> processorChain;
    void updateFilters(double sampleRate);

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(GrindData)
};