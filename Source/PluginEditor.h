/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class Guitar_ampAudioProcessorEditor  : public juce::AudioProcessorEditor,
    private juce::Button::Listener, private juce::Slider::Listener
{
public:
    Guitar_ampAudioProcessorEditor (Guitar_ampAudioProcessor&);
    ~Guitar_ampAudioProcessorEditor();

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;


private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    Guitar_ampAudioProcessor& audioProcessor;

    juce::Image background;

    juce::Slider InputVolume_knob;

    juce::Slider Bass_knob;
    juce::Slider Mid_knob;
    juce::Slider Treble_knob;

    juce::Slider Bias_knob;
    juce::Slider Amp_knob;

    juce::Slider MasterVolume_knob;

    juce::ImageButton Cab_button;
    juce::ImageButton Power_button;
    juce::ImageButton Filter_button;
    juce::ImageButton Tube_button;

    virtual void buttonClicked(juce::Button* button) override;
    virtual void sliderValueChanged(juce::Slider* slider) override;

    void Cab_buttonClicked();
    void Power_buttonClicked();
    void Filter_buttonCLicked();
    void Tube_buttonCLicked();

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Guitar_ampAudioProcessorEditor)
};
