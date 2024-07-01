/*
  ==============================================================================

    GrindData.cpp
    Author:  micheler1208

  ==============================================================================
*/


#include "GrindData.h"

// PREPARE TO PLAY
void GrindData::prepareToPlay(juce::dsp::ProcessSpec spec)
{
    reset();
    grind = 1.0f;
    processorChain.prepare(spec);
    isPrepared = true;

    updateFilters();
}

// PROCESS BLOCK
void GrindData::process(juce::AudioBuffer<float>& buffer)
{
    juce::dsp::AudioBlock<float> block(buffer);
    processorChain.process(juce::dsp::ProcessContextReplacing<float>(block));
}

// UPDATE VALUES
void GrindData::updateValue(float newGrind)
{
    grind = newGrind;
    processorChain.get<0>().setGainLinear(grind);
}

// RESET
void NoiseGateData::reset()
{
    grind = 1.0f;
}


// UPDATE FILTERS
void GrindData::updateFilters()
{
    auto& highPassFilter = processorChain.get<1>();
    auto& fixedEQFilter = processorChain.get<2>();

    juce::dsp::IIR::Coefficients<float>::Ptr highPassCoefficients = juce::dsp::IIR::Coefficients<float>::makeHighPass(sampleRate, 120.0); // Filtro passa-alto a 80 Hz
    highPassFilter.coefficients = highPassCoefficients;

    // Esempio di EQ fissa: un filtro peak/notch per esaltare le medie frequenze a 3 kHz
    juce::dsp::IIR::Coefficients<float>::Ptr eqCoefficients = juce::dsp::IIR::Coefficients<float>::makePeakFilter(sampleRate, 3000.0, 1.0f, juce::Decibels::decibelsToGain(3.0f)); // Peak a 3 kHz, Q=1.0, Gain=3dB
    fixedEQFilter.coefficients = eqCoefficients;
}