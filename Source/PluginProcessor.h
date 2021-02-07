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

    // my variables and functions
    float inputVolume = 1.0;
    float masterVolume = 1.0;

    int amp_state;
    int cab_state;
    int filter_state;
    int tube_state;

    //float Bass_knob_state = 0.0;
    //float Mid_knob_state = 0.0;
    //float Treble_knob_state = 0.0;
    //float InputVolume_knob_state = 0.0;
    //float MasterVolume_knob_state = 0.0;
    //float Bias_knob_state = 0.0;
    //float Amp_knob_state = 0.0;

    IIR_filter bass_filter;
    IIR_filter mid_filter;
    IIR_filter treble_filter;

    FIR cabinet;

    Nonlinear tube;

private:

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Guitar_ampAudioProcessor)
};
