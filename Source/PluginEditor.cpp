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
    
    myKnobLook.setLookAndFeelSliderRotary(juce::ImageCache::getFromMemory(BinaryData::knobRelease_png, BinaryData::knobRelease_pngSize));

    addAndMakeVisible(InputVolume_knob);
    InputVolume_knob.setLookAndFeel(&myKnobLook);
    InputVolume_knob.setSliderStyle(juce::Slider::Rotary);
    InputVolume_knob.setRotaryParameters(3.92, 8.63, true);
    InputVolume_knob.setRange(0.00, 1.0, 0.01);
    InputVolume_knob.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
    InputVolume_knob.setPopupDisplayEnabled(true, false, this);
    InputVolume_knob.setTextValueSuffix(" Input volume");
    InputVolume_knob.setValue(audioProcessor.ampSim.getInputVolume());
    InputVolume_knob.addListener(this);

    addAndMakeVisible(Bass_knob);
    Bass_knob.setLookAndFeel(&myKnobLook);
    Bass_knob.setSliderStyle(juce::Slider::Rotary);
    Bass_knob.setRotaryParameters(3.92, 8.63, true);
    Bass_knob.setRange(0.00, 20.0, 0.01);
    Bass_knob.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
    Bass_knob.setPopupDisplayEnabled(true, false, this);
    Bass_knob.setTextValueSuffix(" Bass");
    Bass_knob.setValue(audioProcessor.ampSim.getBassVolume());
    Bass_knob.addListener(this);

    addAndMakeVisible(Mid_knob);
    Mid_knob.setLookAndFeel(&myKnobLook);
    Mid_knob.setSliderStyle(juce::Slider::Rotary);
    Mid_knob.setRotaryParameters(3.92, 8.63, true);
    Mid_knob.setRange(0.00, 20.0, 0.01);
    Mid_knob.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
    Mid_knob.setPopupDisplayEnabled(true, false, this);
    Mid_knob.setTextValueSuffix(" Mid");
    Mid_knob.setValue(audioProcessor.ampSim.getMidVolume());
    Mid_knob.addListener(this);

    addAndMakeVisible(Treble_knob);
    Treble_knob.setLookAndFeel(&myKnobLook);
    Treble_knob.setSliderStyle(juce::Slider::Rotary);
    Treble_knob.setRotaryParameters(3.92, 8.63, true);
    Treble_knob.setRange(0.00, 20.0, 0.01);
    Treble_knob.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
    Treble_knob.setPopupDisplayEnabled(true, false, this);
    Treble_knob.setTextValueSuffix(" Treble");
    Treble_knob.setValue(audioProcessor.ampSim.getTrebleVolume());
    Treble_knob.addListener(this);

    addAndMakeVisible(Bias_knob);
    Bias_knob.setRange(0.75, 1.75, 0.001);
    Bias_knob.setTextBoxStyle(juce::Slider::NoTextBox, false, 90, 0);
    Bias_knob.setPopupDisplayEnabled(true, false, this);
    Bias_knob.setTextValueSuffix(" Bias");
    Bias_knob.setValue(audioProcessor.ampSim.getBias());
    Bias_knob.addListener(this);

    addAndMakeVisible(Amp_knob);
    Amp_knob.setRange(0.001, 0.5, 0.001);
    Amp_knob.setTextBoxStyle(juce::Slider::NoTextBox, false, 90, 0);
    Amp_knob.setPopupDisplayEnabled(true, false, this);
    Amp_knob.setTextValueSuffix(" Amp");
    Amp_knob.setValue(audioProcessor.ampSim.getAmp());
    Amp_knob.addListener(this);

    addAndMakeVisible(MasterVolume_knob);
    MasterVolume_knob.setLookAndFeel(&myKnobLook);
    MasterVolume_knob.setSliderStyle(juce::Slider::Rotary);
    MasterVolume_knob.setRotaryParameters(3.92, 8.63, true);
    MasterVolume_knob.setRange(0.00, 10.0, 0.01);
    MasterVolume_knob.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
    MasterVolume_knob.setPopupDisplayEnabled(true, false, this);
    MasterVolume_knob.setTextValueSuffix(" Master volume");
    MasterVolume_knob.setValue(audioProcessor.ampSim.getMasterVolume());
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

    setSize(700, 250);
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

    if (audioProcessor.ampSim.getAmpState() == 0)
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

    if (audioProcessor.ampSim.getCabState() == 0)
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

    if (audioProcessor.ampSim.getFilterState() == 0)
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

    if (audioProcessor.ampSim.getTubeState() == 0)
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
    InputVolume_knob.setBounds(60, 129, 50, 50);

    Bass_knob.setBounds(171, 152, 50, 50);
    Mid_knob.setBounds(225, 152, 50, 50);
    Treble_knob.setBounds(278, 152, 50, 50);
    
    Bias_knob.setBounds(400, 185, 60, 12);
    Amp_knob.setBounds(400, 198, 60, 12);

    Power_button.setBounds(649, 9, 18, 42);
    Cab_button.setBounds(542, 20, 30, 25);

    Filter_button.setBounds(303, 98, 18, 18);
    Tube_button.setBounds(489, 98, 37, 37);
    
    MasterVolume_knob.setBounds(583, 129, 50, 50);
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
        audioProcessor.ampSim.setInputVolume(slider->getValue());
        audioProcessor.Input.setValue(slider->getValue());
    }
    else if (slider == &Bass_knob)
    {
        audioProcessor.ampSim.setBassVolume(slider->getValue());
        audioProcessor.Bass.setValue(slider->getValue());
    }
    else if (slider == &Mid_knob)
    {
        audioProcessor.ampSim.setMidVolume(slider->getValue());
        audioProcessor.Mid.setValue(slider->getValue());
    }
    else if (slider == &Treble_knob)
    {
        audioProcessor.ampSim.setTrebleVolume(slider->getValue());
        audioProcessor.Treble.setValue(slider->getValue());
    }
    else if (slider == &Bias_knob)
    {
        audioProcessor.ampSim.setBias(slider->getValue());
        audioProcessor.Bias.setValue(slider->getValue());
    }
    else if (slider == &Amp_knob)
    {
        audioProcessor.ampSim.setAmp(slider->getValue());
        audioProcessor.Ampli.setValue(slider->getValue());
    }
    else if (slider == &MasterVolume_knob)
    {
        audioProcessor.ampSim.setMasterVolume(slider->getValue());
        audioProcessor.Master.setValue(slider->getValue());
    }
}

void Guitar_ampAudioProcessorEditor::Cab_buttonClicked()
{
    if (audioProcessor.ampSim.getCabState() == 0)
    {
        audioProcessor.ampSim.setCabState(1);
        audioProcessor.CabState.setValue(1);
    }
    else
    {
        audioProcessor.ampSim.setCabState(0);
        audioProcessor.CabState.setValue(0);
    }
    repaint();
}

void Guitar_ampAudioProcessorEditor::Power_buttonClicked()
{
    if (audioProcessor.ampSim.getAmpState() == 0)
    {
        audioProcessor.ampSim.setAmpState(1);
        audioProcessor.AmpState.setValue(1);
    }
    else
    {
        audioProcessor.ampSim.setAmpState(0);
        audioProcessor.AmpState.setValue(0);
    }
    repaint();
}

void Guitar_ampAudioProcessorEditor::Filter_buttonCLicked()
{
    if (audioProcessor.ampSim.getFilterState() == 0)
    {
        audioProcessor.ampSim.setFilterState(1);
        audioProcessor.FilterState.setValue(1);
    }
    else
    {
        audioProcessor.ampSim.setFilterState(0);
        audioProcessor.FilterState.setValue(0);
    }
    repaint();
}

void Guitar_ampAudioProcessorEditor::Tube_buttonCLicked()
{
    if (audioProcessor.ampSim.getTubeState() == 0)
    {
        audioProcessor.ampSim.setTubeState(1);
        audioProcessor.TubeState.setValue(1);
    }
    else
    {
        audioProcessor.ampSim.setTubeState(0);
        audioProcessor.TubeState.setValue(0);
    }
    repaint();
}
