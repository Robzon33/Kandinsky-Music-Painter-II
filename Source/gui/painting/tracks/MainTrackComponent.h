/*
  ==============================================================================

    MainTrackComponent.h
    Created: 14 Jul 2021 7:05:43pm
    Author:  Toko

    Component class for all tracks.

  ==============================================================================
*/

#pragma once

#include "JuceHeader.h"
#include "../../../model/MainModel.h"
#include "../../../player/MidiPlayer.h"

#include "TrackComponent.h"

class MainTrackComponent : public juce::Component,
    public juce::ChangeListener
{
public:
    MainTrackComponent(MainModel&, MidiPlayer&);
    ~MainTrackComponent();

    void paint(juce::Graphics& g) override;
    void resized() override;

    void changeListenerCallback(juce::ChangeBroadcaster* source);

    void updateContent();
    void addTrackComponent(MidiTrack* newTrack);
    void deleteTrackComponent(int index);
    void deleteAllTrackComponents();
private:
    MainModel& model;
    MidiPlayer& player;

    juce::OwnedArray<TrackComponent> tracks;
};