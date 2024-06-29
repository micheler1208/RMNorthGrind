/*
  ==============================================================================

    PluginEditor.h
    Author:  micheler1208

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class RMNorthGrindAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    RMNorthGrindAudioProcessorEditor (RMNorthGrindAudioProcessor&);
    ~RMNorthGrindAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    RMNorthGrindAudioProcessor& audioProcessor;
    
    // IMAGES
    juce::Image backgroundImage;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (RMNorthGrindAudioProcessorEditor)
};
