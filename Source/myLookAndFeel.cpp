/*
  ==============================================================================

    myLookAndFeel.cpp
    Created: 8 Nov 2024 7:46:56pm
    Author:  Dominik

  ==============================================================================
*/

#include "myLookAndFeel.h"

//==============================================================================
myLookAndFeel::myLookAndFeel()
{
}

//==============================================================================
void myLookAndFeel::setLookAndFeelSliderVertical(juce::Image inputImage)
{
    // Edit this line to match png file from project Resources
    imgSliderVertical = inputImage;
}

void myLookAndFeel::setLookAndFeelSliderRotary(juce::Image inputImage)
{
    imgSliderRotary = inputImage;
}

//==============================================================================
void myLookAndFeel::drawLinearSlider(juce::Graphics& g, int x, int y, int width, int height,
    float sliderPos,
    float minSliderPos,
    float maxSliderPos,
    const juce::Slider::SliderStyle style, juce::Slider& slider)
{
    const int frameCount = 23;           // Liczba klatek w obrazie
    const int frameWidth = imgSliderVertical.getWidth();  // Upewnij siê, ¿e obraz ma prawid³owe wymiary
    const int frameHeight = imgSliderVertical.getHeight() / frameCount;  // Oblicz wysokoœæ jednej klatki

    // Obliczanie frameId w zale¿noœci od pozycji suwaka
    int frameId = static_cast<int>((slider.getValue() - slider.getMinimum()) /
        (slider.getMaximum() - slider.getMinimum()) * (frameCount - 1));

    frameId = juce::jlimit(0, frameCount - 1, frameId);  // Upewnij siê, ¿e frameId jest w zakresie

    const int sourceY = frameId * frameHeight; // Wyliczenie pozycji klatki w obrazie Ÿród³owym

    // Rysowanie odpowiedniej klatki w docelowym miejscu
    g.drawImage(imgSliderVertical,
        x, y, width, height,            // Obszar docelowy na suwaku
        0, sourceY, frameWidth, frameHeight // Wycinek obrazu Ÿród³owego (klatka)
    );
}

void myLookAndFeel::drawRotarySlider(juce::Graphics& g,
    int x, int y, int width, int height, float sliderPos,
    float rotaryStartAngle, float rotaryEndAngle, juce::Slider& slider)
{
    const double rotation = (slider.getValue() - slider.getMinimum())
        / (slider.getMaximum() - slider.getMinimum());

    const int frames = imgSliderRotary.getHeight() / imgSliderRotary.getWidth();
    const int frameId = (int)std::ceil(rotation * (frames - 1.0));

    const float radius = juce::jmin(width / 2.0f, height / 2.0f);
    const float centerX = x + width * 0.5f;
    const float centerY = y + height * 0.5f;

    // Wylicz lewy górny róg obrazka tak, aby by³ wyœrodkowany
    const float imageX = centerX - radius;
    const float imageY = centerY - radius;

    g.drawImage(imgSliderRotary,
        (int)imageX, (int)imageY,                // Pozycja docelowa (lewy górny róg obrazka)
        2 * (int)radius, 2 * (int)radius,        // Wymiary docelowe (œrednica)
        0, frameId * imgSliderRotary.getWidth(), // Pozycja Ÿród³owa w obrazku
        imgSliderRotary.getWidth(), imgSliderRotary.getWidth()); // Wymiary wycinka Ÿród³owego
}
