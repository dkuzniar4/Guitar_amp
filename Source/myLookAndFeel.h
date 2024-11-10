/*
  ==============================================================================

    myLookAndFeel.h
    Created: 8 Nov 2024 7:47:09pm
    Author:  Dominik

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
class myLookAndFeel : public juce::LookAndFeel_V4
{

public:
    myLookAndFeel();
    void setLookAndFeelSliderVertical(juce::Image inputImage);
    void setLookAndFeelSliderRotary(juce::Image inputImage);
    void drawLinearSlider(juce::Graphics& g, int x, int y, int width, int height,
        float sliderPos,
        float minSliderPos,
        float maxSliderPos,
        const juce::Slider::SliderStyle style, juce::Slider& slider);

    void drawRotarySlider(juce::Graphics& g, int x, int y, int width, int height, float sliderPos,
        float rotaryStartAngle, float rotaryEndAngle, juce::Slider& slider) override;


private:
    juce::Image imgSliderVertical;
    juce::Image imgSliderRotary;

};
