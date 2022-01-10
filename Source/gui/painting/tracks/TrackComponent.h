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

class TrackComponent :  public juce::Component
{
public:
    TrackComponent(MidiTrack&);
    ~TrackComponent();

    void paint(juce::Graphics& g) override;
    
    void mouseDown(const juce::MouseEvent& event) override;
    void mouseDrag(const juce::MouseEvent& event) override;
private:
    MidiTrack& track;

    /* Path you are currently drawing. */
    juce::Path* currentPath;
};