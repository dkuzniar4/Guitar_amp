/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
Guitar_ampAudioProcessorEditor::Guitar_ampAudioProcessorEditor (Guitar_ampAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.

    addAndMakeVisible(InputVolume_knob);
    InputVolume_knob.setSliderStyle(juce::Slider::Rotary);
    InputVolume_knob.setRotaryParameters(3.92, 8.63, true);
    InputVolume_knob.setRange(0.00, 1.0, 0.01);
    InputVolume_knob.setTextBoxStyle(juce::Slider::NoTextBox, false, 90, 0);
    InputVolume_knob.setPopupDisplayEnabled(true, false, this);
    InputVolume_knob.setTextValueSuffix(" Input volume");
    InputVolume_knob.setValue(audioProcessor.inputVolume);
    InputVolume_knob.addListener(this);

    addAndMakeVisible(Bass_knob);
    Bass_knob.setSliderStyle(juce::Slider::Rotary);
    Bass_knob.setRotaryParameters(3.92, 8.63, true);
    Bass_knob.setRange(0.00, 20.0, 0.01);
    Bass_knob.setTextBoxStyle(juce::Slider::NoTextBox, false, 90, 0);
    Bass_knob.setPopupDisplayEnabled(true, false, this);
    Bass_knob.setTextValueSuffix(" Bass");
    Bass_knob.setValue(audioProcessor.bass_filter.volume);
    Bass_knob.addListener(this);

    addAndMakeVisible(Mid_knob);
    Mid_knob.setSliderStyle(juce::Slider::Rotary);
    Mid_knob.setRotaryParameters(3.92, 8.63, true);
    Mid_knob.setRange(0.00, 20.0, 0.01);
    Mid_knob.setTextBoxStyle(juce::Slider::NoTextBox, false, 90, 0);
    Mid_knob.setPopupDisplayEnabled(true, false, this);
    Mid_knob.setTextValueSuffix(" Mid");
    Mid_knob.setValue(audioProcessor.mid_filter.volume);
    Mid_knob.addListener(this);

    addAndMakeVisible(Treble_knob);
    Treble_knob.setSliderStyle(juce::Slider::Rotary);
    Treble_knob.setRotaryParameters(3.92, 8.63, true);
    Treble_knob.setRange(0.00, 20.0, 0.01);
    Treble_knob.setTextBoxStyle(juce::Slider::NoTextBox, false, 90, 0);
    Treble_knob.setPopupDisplayEnabled(true, false, this);
    Treble_knob.setTextValueSuffix(" Treble");
    Treble_knob.setValue(audioProcessor.treble_filter.volume);
    Treble_knob.addListener(this);

    addAndMakeVisible(Bias_knob);
    //Bias_knob.setSliderStyle(juce::Slider::Rotary);
    //Bias_knob.setRotaryParameters(3.92, 8.63, true);
    Bias_knob.setRange(0.50, 2.0, 0.001);
    Bias_knob.setTextBoxStyle(juce::Slider::NoTextBox, false, 90, 0);
    Bias_knob.setPopupDisplayEnabled(true, false, this);
    Bias_knob.setTextValueSuffix(" Bias");
    Bias_knob.setValue(audioProcessor.tube.bias);
    Bias_knob.addListener(this);

    addAndMakeVisible(Amp_knob);
    //Amp_knob.setSliderStyle(juce::Slider::Rotary);
    //Amp_knob.setRotaryParameters(3.92, 8.63, true);
    Amp_knob.setRange(0.001, 0.25, 0.001);
    Amp_knob.setTextBoxStyle(juce::Slider::NoTextBox, false, 90, 0);
    Amp_knob.setPopupDisplayEnabled(true, false, this);
    Amp_knob.setTextValueSuffix(" Amp");
    Amp_knob.setValue(audioProcessor.tube.amp);
    Amp_knob.addListener(this);

    addAndMakeVisible(MasterVolume_knob);
    MasterVolume_knob.setSliderStyle(juce::Slider::Rotary);
    MasterVolume_knob.setRotaryParameters(3.92, 8.63, true);
    MasterVolume_knob.setRange(0.00, 2.0, 0.01);
    MasterVolume_knob.setTextBoxStyle(juce::Slider::NoTextBox, false, 90, 0);
    MasterVolume_knob.setPopupDisplayEnabled(true, false, this);
    MasterVolume_knob.setTextValueSuffix(" Master volume");
    MasterVolume_knob.setValue(audioProcessor.masterVolume);
    MasterVolume_knob.addListener(this);

    Power_button.setImages(true, true, true, juce::ImageCache::getFromMemory(BinaryData::power_ON_png, BinaryData::power_ON_pngSize), 1.0,
        juce::Colours::transparentWhite, juce::Image(), 1.0, juce::Colours::transparentWhite,
        juce::ImageCache::getFromMemory(BinaryData::power_ON_png, BinaryData::power_ON_pngSize), 1.0, juce::Colours::transparentWhite, 0.0);
    addAndMakeVisible(Power_button);
    Power_button.addListener(this);

    Cab_button.setImages(true, true, true, juce::ImageCache::getFromMemory(BinaryData::cab_ON_png, BinaryData::cab_ON_pngSize), 1.0,
        juce::Colours::transparentWhite, juce::Image(), 1.0, juce::Colours::transparentWhite,
        juce::ImageCache::getFromMemory(BinaryData::cab_ON_png, BinaryData::cab_ON_pngSize), 1.0, juce::Colours::transparentWhite, 0.0);
    addAndMakeVisible(Cab_button);
    Cab_button.addListener(this);

    Filter_button.setImages(true, true, true, juce::ImageCache::getFromMemory(BinaryData::switch_ON_png, BinaryData::switch_ON_pngSize), 1.0,
        juce::Colours::transparentWhite, juce::Image(), 1.0, juce::Colours::transparentWhite,
        juce::ImageCache::getFromMemory(BinaryData::switch_ON_png, BinaryData::switch_ON_pngSize), 1.0, juce::Colours::transparentWhite, 0.0);
    addAndMakeVisible(Filter_button);
    Filter_button.addListener(this);

    Tube_button.setImages(true, true, true, juce::ImageCache::getFromMemory(BinaryData::switch_ON_png, BinaryData::switch_ON_pngSize), 1.0,
        juce::Colours::transparentWhite, juce::Image(), 1.0, juce::Colours::transparentWhite,
        juce::ImageCache::getFromMemory(BinaryData::switch_ON_png, BinaryData::switch_ON_pngSize), 1.0, juce::Colours::transparentWhite, 0.0);
    addAndMakeVisible(Tube_button);
    Tube_button.addListener(this);

    setSize(1400, 500);
}

Guitar_ampAudioProcessorEditor::~Guitar_ampAudioProcessorEditor()
{
}

//==============================================================================
void Guitar_ampAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.setColour (juce::Colours::white);
    g.setFont (15.0f);
    
    background = juce::ImageCache::getFromMemory(BinaryData::background_png, BinaryData::background_pngSize);
    g.drawImageAt(background, 0, 0);

    if (audioProcessor.amp_state == 0)
    {
        Power_button.setImages(true, true, true, juce::ImageCache::getFromMemory(BinaryData::power_OFF_png, BinaryData::power_OFF_pngSize), 1.0,
            juce::Colours::transparentWhite, juce::Image(), 1.0, juce::Colours::transparentWhite,
            juce::ImageCache::getFromMemory(BinaryData::power_OFF_png, BinaryData::power_OFF_pngSize), 1.0, juce::Colours::transparentWhite, 0.0);
    }
    else
    {
        Power_button.setImages(true, true, true, juce::ImageCache::getFromMemory(BinaryData::power_ON_png, BinaryData::power_ON_pngSize), 1.0,
            juce::Colours::transparentWhite, juce::Image(), 1.0, juce::Colours::transparentWhite,
            juce::ImageCache::getFromMemory(BinaryData::power_ON_png, BinaryData::power_ON_pngSize), 1.0, juce::Colours::transparentWhite, 0.0);
    }

    if (audioProcessor.cab_state == 0)
    {
        Cab_button.setImages(true, true, true, juce::ImageCache::getFromMemory(BinaryData::cab_OFF_png, BinaryData::cab_OFF_pngSize), 1.0,
            juce::Colours::transparentWhite, juce::Image(), 1.0, juce::Colours::transparentWhite,
            juce::ImageCache::getFromMemory(BinaryData::cab_OFF_png, BinaryData::cab_OFF_pngSize), 1.0, juce::Colours::transparentWhite, 0.0);
    }
    else
    {
        Cab_button.setImages(true, true, true, juce::ImageCache::getFromMemory(BinaryData::cab_ON_png, BinaryData::cab_ON_pngSize), 1.0,
            juce::Colours::transparentWhite, juce::Image(), 1.0, juce::Colours::transparentWhite,
            juce::ImageCache::getFromMemory(BinaryData::cab_ON_png, BinaryData::cab_ON_pngSize), 1.0, juce::Colours::transparentWhite, 0.0);
    }

    if (audioProcessor.filter_state == 0)
    {
        Filter_button.setImages(true, true, true, juce::ImageCache::getFromMemory(BinaryData::switch_OFF_png, BinaryData::switch_OFF_pngSize), 1.0,
            juce::Colours::transparentWhite, juce::Image(), 1.0, juce::Colours::transparentWhite,
            juce::ImageCache::getFromMemory(BinaryData::switch_OFF_png, BinaryData::switch_OFF_pngSize), 1.0, juce::Colours::transparentWhite, 0.0);
        addAndMakeVisible(Filter_button);
        Filter_button.addListener(this);
    }
    else
    {
        Filter_button.setImages(true, true, true, juce::ImageCache::getFromMemory(BinaryData::switch_ON_png, BinaryData::switch_ON_pngSize), 1.0,
            juce::Colours::transparentWhite, juce::Image(), 1.0, juce::Colours::transparentWhite,
            juce::ImageCache::getFromMemory(BinaryData::switch_ON_png, BinaryData::switch_ON_pngSize), 1.0, juce::Colours::transparentWhite, 0.0);
        addAndMakeVisible(Filter_button);
        Filter_button.addListener(this);
    }

    if (audioProcessor.tube_state == 0)
    {
        Tube_button.setImages(true, true, true, juce::ImageCache::getFromMemory(BinaryData::switch_OFF_png, BinaryData::switch_OFF_pngSize), 1.0,
            juce::Colours::transparentWhite, juce::Image(), 1.0, juce::Colours::transparentWhite,
            juce::ImageCache::getFromMemory(BinaryData::switch_OFF_png, BinaryData::switch_OFF_pngSize), 1.0, juce::Colours::transparentWhite, 0.0);
        addAndMakeVisible(Tube_button);
        Tube_button.addListener(this);
    }
    else
    {
        Tube_button.setImages(true, true, true, juce::ImageCache::getFromMemory(BinaryData::switch_ON_png, BinaryData::switch_ON_pngSize), 1.0,
            juce::Colours::transparentWhite, juce::Image(), 1.0, juce::Colours::transparentWhite,
            juce::ImageCache::getFromMemory(BinaryData::switch_ON_png, BinaryData::switch_ON_pngSize), 1.0, juce::Colours::transparentWhite, 0.0);
        addAndMakeVisible(Tube_button);
        Tube_button.addListener(this);
    }
}

void Guitar_ampAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
    InputVolume_knob.setBounds(107, 247, 127, 127);

    Bass_knob.setBounds(355, 311, 81, 81);
    Mid_knob.setBounds(460, 311, 81, 81);
    Treble_knob.setBounds(567, 311, 81, 81);
    
    Bias_knob.setBounds(794, 367, 130, 30);
    Amp_knob.setBounds(794, 394, 130, 30);

    Power_button.setBounds(1298, 19, 48, 94);
    Cab_button.setBounds(1084, 39, 57, 47);

    Filter_button.setBounds(607, 197, 37, 37);
    Tube_button.setBounds(981, 197, 37, 37);
    
    MasterVolume_knob.setBounds(1155, 247, 127, 127);
}

void Guitar_ampAudioProcessorEditor::buttonClicked(juce::Button* button)
{
    if (button == &Cab_button) {
        Cab_buttonClicked();
    }
    else if (button == &Power_button)
    {
        Power_buttonClicked();
    }
    else if (button == &Filter_button)
    {
        Filter_buttonCLicked();
    }
    else if (button == &Tube_button)
    {
        Tube_buttonCLicked();
    }
}

void Guitar_ampAudioProcessorEditor::sliderValueChanged(juce::Slider* slider)
{
    if (slider == &InputVolume_knob)
    {
        audioProcessor.inputVolume = slider->getValue();
    }
    else if (slider == &Bass_knob)
    {
        audioProcessor.bass_filter.volume = slider->getValue();
    }
    else if (slider == &Mid_knob)
    {
        audioProcessor.mid_filter.volume = slider->getValue();
    }
    else if (slider == &Treble_knob)
    {
        audioProcessor.treble_filter.volume = slider->getValue();
    }
    else if (slider == &Bias_knob)
    {
        audioProcessor.tube.bias = slider->getValue();
    }
    else if (slider == &Amp_knob)
    {
        audioProcessor.tube.amp = slider->getValue();
    }
    else if (slider == &MasterVolume_knob)
    {
        audioProcessor.masterVolume = slider->getValue();
    }
}

void Guitar_ampAudioProcessorEditor::Cab_buttonClicked()
{
    if (audioProcessor.cab_state == 0)
    {
        audioProcessor.cab_state = 1;
    }
    else
    {
        audioProcessor.cab_state = 0;
    }
    repaint();
}

void Guitar_ampAudioProcessorEditor::Power_buttonClicked()
{
    if (audioProcessor.amp_state == 0)
    {
        audioProcessor.amp_state = 1;
    }
    else
    {
        audioProcessor.amp_state = 0;
    }
    repaint();
}

void Guitar_ampAudioProcessorEditor::Filter_buttonCLicked()
{
    if (audioProcessor.filter_state == 0)
    {
        audioProcessor.filter_state = 1;
    }
    else
    {
        audioProcessor.filter_state = 0;
    }
    repaint();
}

void Guitar_ampAudioProcessorEditor::Tube_buttonCLicked()
{
    if (audioProcessor.tube_state == 0)
    {
        audioProcessor.tube_state = 1;
    }
    else
    {
        audioProcessor.tube_state = 0;
    }
    repaint();
}
