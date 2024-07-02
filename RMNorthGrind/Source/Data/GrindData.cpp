/*
  ==============================================================================

    GrindData.cpp
    Author:  micheler1208

  ==============================================================================
*/


#include "GrindData.h"

// COSTRUCTOR
GrindData::GrindData()
    : grind(1.0f)
{
}

// PREPARE TO PLAY
void GrindData::prepareToPlay(juce::dsp::ProcessSpec spec)
{
    reset();
    processorChain.prepare(spec);
    isPrepared = true;

    double sampleRate = spec.sampleRate;
    updateFilters(sampleRate);
}

// PROCESS BLOCK
void GrindData::process(juce::AudioBuffer<float>& buffer)
{
    juce::dsp::AudioBlock<float> block(buffer);
    juce::dsp::ProcessContextReplacing<float> context(block);

    processorChain.process(context);
}

// UPDATE VALUES
void GrindData::updateValue(float newGrind)
{
    grind = newGrind;
    processorChain.get<0>().setGainLinear(grind);
}

// RESET
void GrindData::reset()
{
    processorChain.reset();
}

// UPDATE FILTERS
void GrindData::updateFilters(double sampleRate)
{
    auto& highPassFilter = processorChain.get<1>();
    auto& fixedEQFilter = processorChain.get<2>();

    auto highPassCoefficients = juce::dsp::IIR::Coefficients<float>::makeHighPass(sampleRate, 120.0); // Filtro passa-alto a 120 Hz
    *highPassFilter.state = *highPassCoefficients;

    // Esempio di EQ fissa: un filtro peak/notch per esaltare le medie frequenze a 3 kHz
    auto eqCoefficients = juce::dsp::IIR::Coefficients<float>::makePeakFilter(sampleRate, 2700.0, 1.0f, juce::Decibels::decibelsToGain(3.0f)); // Peak a 3 kHz, Q=1.0, Gain=3dB
    *fixedEQFilter.state = *eqCoefficients;
}
