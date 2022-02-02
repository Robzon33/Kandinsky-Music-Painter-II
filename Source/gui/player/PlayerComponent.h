/*
  ==============================================================================

    PlayerComponent.h
    Created: 6 Jul 2021 11:10:28am
    Author:  Toko

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "../../player/MidiPlayer.h"
#include "../../model/ProjectSettings.h"

class PlayerComponent : public juce::Component,
    public juce::Button::Listener,
    public juce::Slider::Listener
{
public:
    PlayerComponent(MidiPlayer&, ProjectSettings&);
    ~PlayerComponent();

    void paint(juce::Graphics& g) override;
    void resized() override;
    void buttonClicked(juce::Button* button) override;
    void sliderValueChanged(juce::Slider* slider) override;
private:
    MidiPlayer& player;
    ProjectSettings& settings;
    juce::Colour colour;

    std::unique_ptr<juce::DrawableButton> playButton, pauseButton, stopButton;
    std::unique_ptr<juce::Slider> tempoSlider;

    void initSlider();
    void initButtons();
};