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

class TrackComponent :  public juce::Component
{
public:
    TrackComponent(MidiTrack&);
    ~TrackComponent();

    void paint(juce::Graphics& g) override;
    
    void mouseDown(const juce::MouseEvent& event) override;
    void mouseMove(const juce::MouseEvent& event) override;
    void mouseDrag(const juce::MouseEvent& event) override;
private:
    MidiTrack& track;
    std::unique_ptr<Drawer> drawer;

    /* Path you are currently drawing. */
    std::unique_ptr<juce::Path> currentPath;

    /* Points you are using for the current object. */
    juce::OwnedArray<juce::Point<int>> currentPoints;
};