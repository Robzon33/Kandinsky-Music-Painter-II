/*
  ==============================================================================

    ConfigDialog.h
    Created: 2 Feb 2022 10:38:37am
    Author:  Toko

  ==============================================================================
*/

#pragma once

#include "JuceHeader.h"
#include "../../model/ProjectSettings.h"

class TrackWidthSliderComponent : public juce::SliderPropertyComponent
{
public:
    TrackWidthSliderComponent(const juce::String& propertyName, double rangeMin, double rangeMax, double intervall, int value)
        : SliderPropertyComponent(propertyName, rangeMin, rangeMax, 100)
    {
        setValue(value);
    };

    void setValue(double newValue) override
    {
        slider.setValue(newValue);
    };
private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(TrackWidthSliderComponent)
};

class ConfigDialog : public juce::Component,
                     private juce::Button::Listener
{
public:
    ConfigDialog(ProjectSettings&);
    ~ConfigDialog();

    void paint(juce::Graphics& g) override;
    void resized() override;
    
    void loadContent();
    void applyNewSettings();

    juce::DialogWindow* getDialogWindow();
private:
    ProjectSettings& settings;
    juce::PropertyPanel propertyPanel;
    juce::TextButton applyButton;
    juce::TextButton resetButton;
    juce::TextPropertyComponent* nameComp;
    TrackWidthSliderComponent* widthSliderComp;

    void buttonClicked(juce::Button*) override;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(ConfigDialog)
};