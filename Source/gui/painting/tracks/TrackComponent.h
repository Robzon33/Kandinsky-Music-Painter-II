/*
  ==============================================================================

    TrackComponent.h
    Created: 14 Jul 2021 12:19:44pm
    Author:  Toko

  ==============================================================================
*/

#pragma once

#include "JuceHeader.h"
#include "../../../model/tracks/MidiTrack.h"
#include "tools/Drawer.h"

class TrackComponent :  public juce::Component,
    public juce::ChangeListener
{
public:
    TrackComponent(MidiTrack&, Drawer&, float scaleFactor);
    ~TrackComponent();

    void paint(juce::Graphics& g) override;

    void mouseDrag(const juce::MouseEvent& event) override;
    void mouseUp(const juce::MouseEvent& event) override;

    void changeListenerCallback(juce::ChangeBroadcaster* source) override;

    void setScaleFactor(float newScaleFactor);
private:
    MidiTrack& track;
    Drawer& drawer;

    /* Path you are currently drawing. */
    std::unique_ptr<juce::Path> currentPath;
    float scaleFactor;
};