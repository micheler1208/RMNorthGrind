/*
  ==============================================================================

    PluginProcessor.cpp
    Author:  micheler1208

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"


// CONSTRUCTOR
RMNorthGrindAudioProcessor::RMNorthGrindAudioProcessor()
    : AudioProcessor(BusesProperties()
        .withInput("Input", juce::AudioChannelSet::mono(), true)
        .withOutput("Output", juce::AudioChannelSet::stereo(), true)),
    apvts(*this, nullptr, "PARAMETERS", createParams())
{
}

// DESTRUCTOR
RMNorthGrindAudioProcessor::~RMNorthGrindAudioProcessor()
{
}


// INITIALIZATION CONFIG
void RMNorthGrindAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    juce::dsp::ProcessSpec spec;
    spec.sampleRate = sampleRate;
    spec.maximumBlockSize = static_cast<juce::uint32>(samplesPerBlock);
    spec.numChannels = getTotalNumOutputChannels();

    noiseGate.prepareToPlay();
    grind.prepareToPlay(spec);
}

// PROCESS BLOCK
void RMNorthGrindAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
 juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    // Clear any output channels that don't have input data
    for (int i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
    {
        buffer.clear(i, 0, buffer.getNumSamples());
    }

    // GAIN STAGES
    if (totalNumInputChannels > 0 && totalNumOutputChannels > 0)
    {
        // Update parameters
        float noiseGateValue = apvts.getRawParameterValue("NOISEGATE")->load();
        noiseGate.updateValue(noiseGateValue);
        
        float grindValue = apvts.getRawParameterValue("GRIND")->load();
        grind.updateValue(grindValue);

        juce::dsp::AudioBlock<float> block(buffer);
        juce::dsp::ProcessContextReplacing<float> context(block);

        noiseGate.process(buffer);
        grind.process(buffer);
        
        if (totalNumInputChannels == 1 && totalNumOutputChannels == 2)
        {
            auto* leftChannel = buffer.getReadPointer(0);
            auto* rightChannel = buffer.getWritePointer(1);

            for (int sample = 0; sample < buffer.getNumSamples(); ++sample)
            {
                rightChannel[sample] = leftChannel[sample];
            }
        }
    }
}

// PAUSE STOP
void RMNorthGrindAudioProcessor::releaseResources()
{
}

// OUTPUT CHANNELS CONFIG
bool RMNorthGrindAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
    if (layouts.getMainInputChannelSet() != juce::AudioChannelSet::mono()
        && layouts.getMainInputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    return true;
}

// SUPPORT METHODS
const juce::String RMNorthGrindAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool RMNorthGrindAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool RMNorthGrindAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool RMNorthGrindAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double RMNorthGrindAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int RMNorthGrindAudioProcessor::getNumPrograms()
{
    return 1;
}

int RMNorthGrindAudioProcessor::getCurrentProgram()
{
    return 0;
}

void RMNorthGrindAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String RMNorthGrindAudioProcessor::getProgramName (int index)
{
    return {};
}

void RMNorthGrindAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}


bool RMNorthGrindAudioProcessor::hasEditor() const
{
    return true;
}

juce::AudioProcessorEditor* RMNorthGrindAudioProcessor::createEditor()
{
    return new RMNorthGrindAudioProcessorEditor (*this);
}

void RMNorthGrindAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
}

void RMNorthGrindAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
}

juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new RMNorthGrindAudioProcessor();
}

// CREATE PARAMETERS
juce::AudioProcessorValueTreeState::ParameterLayout RMNorthGrindAudioProcessor::createParams()
{
    std::vector<std::unique_ptr<juce::RangedAudioParameter>> params;

    // Noise Gate
    params.push_back(std::make_unique<juce::AudioParameterFloat>("NOISEGATE", "Noise Gate", -96.0f, 0.0f, -80.0f));

    // Grind
    params.push_back(std::make_unique<juce::AudioParameterFloat>("GRIND", "Grind", juce::NormalisableRange<float> { 0.0f, 1.0f, }, 0.0f));

    return { params.begin(), params.end() };
}
