/*
  ==============================================================================

    GrindComponent.h
    Author:  micheler1208

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "CustomLookAndFeelGrind.h"
#include "CustomSlider.h"

class GrindComponent  : public juce::Component
{
public:
    GrindComponent(juce::AudioProcessorValueTreeState& apvts);
    ~GrindComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    // CUSTOM LOOK AND FEEL
    CustomLookAndFeelGrind customLookAndFeelGrind;
    
    // DRIVE
    CustomSlider grindSlider;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> grindAttachment;

    // LABELS
    juce::Label grindLabel;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (GrindComponent)
};
