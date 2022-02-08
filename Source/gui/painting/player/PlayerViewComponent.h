/*
  ==============================================================================

    PlayerViewComponent.h
    Created: 8 Feb 2022 1:52:25pm
    Author:  Toko

  ==============================================================================
*/

#pragma once

#include "JuceHeader.h"
#include "../../../player/MidiPlayer.h"

class PlayerViewComponent : public juce::Component, public juce::Timer, public juce::ChangeListener
{
public:
    PlayerViewComponent(MidiPlayer&, float scaleFactor);
    ~PlayerViewComponent();

    void paint(juce::Graphics&) override;
    void resized() override;

    void timerCallback() override;

    void changeListenerCallback(juce::ChangeBroadcaster* source);

    void setScaleFactor(float newScaleFactor);
private:
    MidiPlayer& player;
    float scaleFactor;
    const int height = 128;
};