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
    MainTrackComponent(MainModel&, MidiPlayer&, ProjectSettings&, float scaleFactor);
    ~MainTrackComponent();

    void paint(juce::Graphics& g) override;
    void resized() override;

    void changeListenerCallback(juce::ChangeBroadcaster* source);

    void setSelectedTrack(int index);
    void addTrackComponent(MidiTrack* newTrack);
    void deleteTrackComponent(int index);
    void deleteAllTrackComponents();
    void setSelectedTool(int index);
    void setWidth();
    void setScaleFactor(float newScaleFactor);
private:
    MainModel& model;
    MidiPlayer& player;
    ProjectSettings& settings;

    std::unique_ptr<Drawer> drawer;
    juce::OwnedArray<TrackComponent> tracks;
    const int height = 128;
    float scaleFactor;
};