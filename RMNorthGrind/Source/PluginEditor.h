/*
  ==============================================================================

    PluginEditor.h
    Author:  micheler1208

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "UI/GrindComponent.h"
#include "UI/NoiseGateComponent.h"

class RMNorthGrindAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    RMNorthGrindAudioProcessorEditor (RMNorthGrindAudioProcessor&);
    ~RMNorthGrindAudioProcessorEditor() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    // PROCESSOR
    RMNorthGrindAudioProcessor& audioProcessor;
    
    // IMAGES
    juce::Image backgroundImage;
    
    // NOISE GATE
    NoiseGateComponent noiseGate;
    
    //GRIND
    GrindComponent grind;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (RMNorthGrindAudioProcessorEditor)
};
