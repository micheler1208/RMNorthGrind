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
        juce::String prefix;
        juce::String suffix;
        juce::String textValue;

        if (getName() == "NoiseGate")
        {
            prefix = "";
            suffix = " db";
            textValue = juce::String(value, numDecimalPlaces);
        }
        else if ( getName() == "Grind")
        {
            prefix = "+";
            suffix = " db";
            textValue = juce::String(value, numDecimalPlaces);
        }

        return textValue + suffix;
    }

    double getValueFromText(const juce::String& text) override
    {
        auto valueStr = text.upToFirstOccurrenceOf(" ", false, false);
        auto value = valueStr.getDoubleValue();
        return value;
    }

private:
    int numDecimalPlaces = 1;
};
