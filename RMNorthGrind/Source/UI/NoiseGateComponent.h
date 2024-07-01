/*
  ==============================================================================

    NoiseGateComponent.h
    Author:  micheler1208

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "CustomLookAndFeelGrind.h"
#include "CustomSlider.h"

class NoiseGateComponent  : public juce::Component
{
public:
    NoiseGateComponent(juce::AudioProcessorValueTreeState& apvts);
    ~NoiseGateComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    // CUSTOM LOOK AND FEEL
    CustomLookAndFeelGrind customLookAndFeelGrind;
    
    // NOISE GATE
    CustomSlider noiseGateSlider;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> noiseGateAttachment;

    // LABELS
    juce::Label noiseGateLabel;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (NoiseGateComponent)
};
