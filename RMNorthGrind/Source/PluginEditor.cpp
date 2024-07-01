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
    : AudioProcessorEditor (&p),
    audioProcessor (p),
    noiseGate(audioProcessor.apvts), 
    grind(audioProcessor.apvts)
{
    
    // WINDOW SIZE
    setSize (384, 698);
    
    // NOISE GATE ENABLE
    addAndMakeVisible(noiseGate);

    // GRIND ENABLE
    addAndMakeVisible(grind);
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
    auto area = getLocalBounds().reduced(20);

    int sliderWidth = 80;
    int sliderHeight = 80;
    int spacing = 20;
    int extraLeftMargin = 25;
    int labelHeight = 20;

    int totalWidth = 5 * sliderWidth + 4 * spacing;
    int startX = (area.getWidth() - totalWidth) / 2 + extraLeftMargin;
    int startY = area.getHeight() - sliderHeight - labelHeight - 40;
    
    
    grind.setBounds(53, 50, getWidth() / 2, 150);

    noiseGate.setBounds(getWidth()/2 + 53, 50, getWidth() / 2, 150);
    

}