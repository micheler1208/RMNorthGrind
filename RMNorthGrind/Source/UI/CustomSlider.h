/*
  ==============================================================================

    CustomSlider.h
    Author:  micheler1208

  ==============================================================================
*/
#pragma once

#include <JuceHeader.h>

class CustomSlider : public juce::Slider
{
public:
    CustomSlider()
    {
        setNumDecimalPlacesToDisplay(1);
    }

    void setDecimalPlaces(int places)
    {
        numDecimalPlaces = places;
        setNumDecimalPlacesToDisplay(places);
    }

protected:
    juce::String getTextFromValue(double value) override
    {
        juce::String suffix;
        juce::String textValue;

        if (getName() == "NoiseGate")
        {
            suffix = " db";
            textValue = juce::String(value, numDecimalPlaces);
        }
        else if ( getName() == "Grind")
        {
            suffix = " %";
            textValue = juce::String(value, 0);
        }

        return textValue + suffix;
    }

    double getValueFromText(const juce::String& text) override
    {
        auto valueStr = text.upToFirstOccurrenceOf(" ", false, false);
        auto value = valueStr.getDoubleValue();

        if (getName() == "Grind")
        {
        }

        return value;
    }

private:
    int numDecimalPlaces = 1;
};
