/*
  ==============================================================================

    GrindComponent.cpp
    Author:  micheler1208

  ==============================================================================
*/

#include <JuceHeader.h>
#include "GrindComponent.h"

//==============================================================================

// CONSTRUCTORE
GrindComponent::GrindComponent(juce::AudioProcessorValueTreeState& apvts)
{
    using SliderAttachment = juce::AudioProcessorValueTreeState::SliderAttachment;

    // GRIND SLIDER
    grindSlider.setLookAndFeel(&customLookAndFeelGrind);
    grindSlider.setName("Grind");
    grindSlider.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    grindSlider.setRange(1.0, 20.0, 0.1);
    grindSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 60, 20);
    addAndMakeVisible(&grindSlider);
    grindAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(apvts, "GRIND", grindSlider);
    
    // LABELS
    juce::Font labelFont = juce::Font(juce::Typeface::createSystemTypefaceFor(BinaryData::timegoing_ttf, BinaryData::timegoing_ttfSize));
    labelFont.setHeight(48.0f);

    // DRIVE LABEL
    grindLabel.setText("Grind", juce::dontSendNotification);
    grindLabel.setFont(labelFont);
    grindLabel.setColour(juce::Label::textColourId, juce::Colour::fromRGB(234, 236, 233));
    grindLabel.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(&grindLabel);

}

// DESTRUCTOR
GrindComponent::~GrindComponent()
{
    grindSlider.setLookAndFeel(nullptr);
}

void GrindComponent::paint (juce::Graphics& g)
{
}

void GrindComponent::resized()
{
    grindLabel.setBounds(0, 0, 75, 40);
    grindSlider.setBounds(0, 40, 75, 75);
}
