/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "Engine.h"

//==============================================================================
/**
*/
class Guitar_ampAudioProcessor  : public juce::AudioProcessor
{
public:
    //==============================================================================
    Guitar_ampAudioProcessor();
    ~Guitar_ampAudioProcessor();

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    //==============================================================================
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;

    //==============================================================================
    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

    Amp ampSim;

    juce::AudioProcessorValueTreeState parameters;
    juce::Value Input;
    juce::Value Master;

    juce::Value Bass;
    juce::Value Mid;
    juce::Value Treble;

    juce::Value Bias;
    juce::Value Ampli;

    juce::Value AmpState;
    juce::Value CabState;
    juce::Value FilterState;
    juce::Value TubeState;

private:

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Guitar_ampAudioProcessor)
};
