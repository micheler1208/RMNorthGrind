/*
  ==============================================================================

    PluginEditor.cpp
    Author:  micheler1208

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
RMNorthGrindAudioProcessorEditor::RMNorthGrindAudioProcessorEditor (RMNorthGrindAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (384, 698);
}

RMNorthGrindAudioProcessorEditor::~RMNorthGrindAudioProcessorEditor()
{
}

// GUI - PAINT
void RMNorthGrindAudioProcessorEditor::paint (juce::Graphics& g)
{
    // Background
    backgroundImage = juce::ImageCache::getFromMemory(BinaryData::background_jpg, BinaryData::background_jpgSize);
    if (!backgroundImage.isNull())
    {
        g.drawImageAt(backgroundImage, 0, 0);
    }
    else
    {
        // Fallback color
        g.fillAll(getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId));
    }

    // Title Text
    juce::Font titleFont = juce::Font(juce::Typeface::createSystemTypefaceFor(BinaryData::timegoing_ttf, BinaryData::timegoing_ttfSize));
    titleFont.setHeight(64.0f);
    g.setFont(titleFont);
    g.setColour(juce::Colour::fromRGB(118, 5, 11));
    g.drawFittedText("RM - NORTH GRIND", getLocalBounds().removeFromTop(70), juce::Justification::centred, 1);
}

void RMNorthGrindAudioProcessorEditor::resized()
{
}
