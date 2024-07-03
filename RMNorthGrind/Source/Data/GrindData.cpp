/*
  ==============================================================================

    GrindData.cpp
    Author:  micheler1208

  ==============================================================================
*/
#include "GrindData.h"

// CONSTRUCTOR
GrindData::GrindData()
    : grind(1.0f), fetThreshold(0.7f), fetSaturation(5.0f), fetGain(1.1f), headroom(18.0f)
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
    juce::ScopedNoDenormals noDenormals;
    auto numSamples = buffer.getNumSamples();

    for (int channel = 0; channel < buffer.getNumChannels(); ++channel)
    {
        auto* channelData = buffer.getWritePointer(channel);

        for (int sample = 0; sample < numSamples; ++sample)
        {
            // Process through multiple FET stages
            float fetProcessedSample = processFET(channelData[sample]);

            // Apply EQ and Gain
            channelData[sample] = fetProcessedSample;
        }
    }

    juce::dsp::AudioBlock<float> block(buffer);
    juce::dsp::ProcessContextReplacing<float> context(block);
    processorChain.process(context);
}

// PROCESS FET MODEL
float GrindData::processFET(float inputSample)
{
    // First FET stage
    float stage1Output = inputSample * fetGain;
    stage1Output = applyFETThreshold(stage1Output);

    // Second FET stage
    float stage2Output = stage1Output * fetGain;
    stage2Output = applyFETThreshold(stage2Output);

    // Adjust output for headroom
    float finalOutput = stage2Output * (headroom / 9.0f);

    return finalOutput;
}

float GrindData::applyFETThreshold(float sample)
{
    if (sample > fetThreshold)
    {
        sample = fetThreshold + (sample - fetThreshold) / fetSaturation;
    }
    else if (sample < -fetThreshold)
    {
        sample = -fetThreshold + (sample + fetThreshold) / fetSaturation;
    }
    return sample;
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
    auto& peak1 = processorChain.get<2>();
    auto& peak2 = processorChain.get<3>();
    auto& peak3 = processorChain.get<4>();
    auto& peak4 = processorChain.get<5>();
    auto& peak5 = processorChain.get<6>();
    auto& peak6 = processorChain.get<7>();
    auto& peak7 = processorChain.get<8>();
    auto& peak8 = processorChain.get<9>();
    auto& peak9 = processorChain.get<10>();
    auto& peak10 = processorChain.get<11>();

    // High Pass Filter
    auto highPassCoefficients = juce::dsp::IIR::Coefficients<float>::makeHighPass(sampleRate, 10.0f, 0.4f);
    *highPassFilter.state = *highPassCoefficients;

    // Fixed Peaks
    auto peak1Coefficients = juce::dsp::IIR::Coefficients<float>::makePeakFilter(sampleRate, 23.7, 0.55f, juce::Decibels::decibelsToGain(-5.1f));
    *peak1.state = *peak1Coefficients;

    auto peak2Coefficients = juce::dsp::IIR::Coefficients<float>::makePeakFilter(sampleRate, 52.3, 2.33f, juce::Decibels::decibelsToGain(-4.0f));
    *peak2.state = *peak2Coefficients;

    auto peak3Coefficients = juce::dsp::IIR::Coefficients<float>::makePeakFilter(sampleRate, 90.1, 1.03f, juce::Decibels::decibelsToGain(-3.9f));
    *peak3.state = *peak3Coefficients;

    auto peak4Coefficients = juce::dsp::IIR::Coefficients<float>::makePeakFilter(sampleRate, 167.1, 3.0f, juce::Decibels::decibelsToGain(-4.7f));
    *peak4.state = *peak4Coefficients;

    auto peak5Coefficients = juce::dsp::IIR::Coefficients<float>::makePeakFilter(sampleRate, 252.9, 1.0f, juce::Decibels::decibelsToGain(-0.67f));
    *peak5.state = *peak5Coefficients;

    auto peak6Coefficients = juce::dsp::IIR::Coefficients<float>::makePeakFilter(sampleRate, 967.1, 1.0f, juce::Decibels::decibelsToGain(5.33f));
    *peak6.state = *peak6Coefficients;

    auto peak7Coefficients = juce::dsp::IIR::Coefficients<float>::makePeakFilter(sampleRate, 1471.7, 1.0f, juce::Decibels::decibelsToGain(1.95f));
    *peak7.state = *peak7Coefficients;

    auto peak8Coefficients = juce::dsp::IIR::Coefficients<float>::makePeakFilter(sampleRate, 3965.0, 0.9f, juce::Decibels::decibelsToGain(0.46f));
    *peak8.state = *peak8Coefficients;

    auto peak9Coefficients = juce::dsp::IIR::Coefficients<float>::makePeakFilter(sampleRate, 6664.0, 0.37f, juce::Decibels::decibelsToGain(6.05f));
    *peak9.state = *peak9Coefficients;

    auto peak10Coefficients = juce::dsp::IIR::Coefficients<float>::makePeakFilter(sampleRate, 20000.0, 1.01f, juce::Decibels::decibelsToGain(2.23f));
    *peak10.state = *peak10Coefficients;
}
