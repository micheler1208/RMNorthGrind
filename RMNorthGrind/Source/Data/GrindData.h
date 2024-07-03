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
    bool isPrepared{ false };
    float grind;
    float fetThreshold;
    float fetSaturation;
    float fetGain;
    float headroom;

    using Gain = juce::dsp::Gain<float>;
    using HighPassFilter = juce::dsp::ProcessorDuplicator<juce::dsp::IIR::Filter<float>, juce::dsp::IIR::Coefficients<float>>;
    using PeakEQFilter = juce::dsp::ProcessorDuplicator<juce::dsp::IIR::Filter<float>, juce::dsp::IIR::Coefficients<float>>;

    juce::dsp::ProcessorChain<Gain, HighPassFilter, PeakEQFilter, PeakEQFilter, PeakEQFilter, PeakEQFilter, PeakEQFilter, PeakEQFilter, PeakEQFilter, PeakEQFilter, PeakEQFilter, PeakEQFilter> processorChain;
    void updateFilters(double sampleRate);

    float processFET(float inputSample);
    float applyFETThreshold(float sample);

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(GrindData)
};
