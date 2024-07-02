/*
  ==============================================================================

    NoiseGateComponent.cpp
    Author:  micheler1208

  ==============================================================================
*/

#include <JuceHeader.h>
#include "NoiseGateComponent.h"

//==============================================================================

// CONTRUCTOR
NoiseGateComponent::NoiseGateComponent(juce::AudioProcessorValueTreeState& apvts)
{
    using SliderAttachment = juce::AudioProcessorValueTreeState::SliderAttachment;

    // NOISE GATE SLIDER
    noiseGateSlider.setLookAndFeel(&customLookAndFeelGrind);
    noiseGateSlider.setName("NoiseGate");
    noiseGateSlider.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    noiseGateSlider.setRange(-96.0, 0.0, 0.01);
    noiseGateSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 60, 20);
    addAndMakeVisible(&noiseGateSlider);
    noiseGateAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(apvts, "NOISEGATE", noiseGateSlider);

    // LABELS
    juce::Font labelFont = juce::Font(juce::Typeface::createSystemTypefaceFor(BinaryData::timegoing_ttf, BinaryData::timegoing_ttfSize));
    labelFont.setHeight(48.0f);

    // NOISE GATE LABEL
    noiseGateLabel.setText("Noise Gate", juce::dontSendNotification);
    noiseGateLabel.setFont(labelFont);
    noiseGateLabel.setColour(juce::Label::textColourId, juce::Colour::fromRGB(234, 236, 233));
    noiseGateLabel.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(&noiseGateLabel);
}

// DESTRUCTOR
NoiseGateComponent::~NoiseGateComponent()
{
    noiseGateSlider.setLookAndFeel(nullptr);
}

void NoiseGateComponent::paint (juce::Graphics& g)
{
}

void NoiseGateComponent::resized()
{
    noiseGateLabel.setBounds(0, 0, 150, 40);
    noiseGateSlider.setBounds(40, 40, 75, 75);
}
