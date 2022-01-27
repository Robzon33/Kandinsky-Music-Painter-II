/*
  ==============================================================================

    MainModel.h
    Created: 27 Jun 2021 10:05:23pm
    Author:  Toko

  ==============================================================================
*/

#pragma once

#include "tracks/MidiTrack.h"
#include "ProjectSettings.h"
#include "../extensions/RandomColourGenerator.h"

class MainModel     : public juce::ChangeBroadcaster
{
public:
    MainModel(ProjectSettings& ps);
    ~MainModel();

    bool addMidiTrack();
    MidiTrack* getMidiTrack(int index);
    void deleteTrack(int index);
    void deleteAllTracks();
    int getIndexOfLastTrack();
    juce::String getTrackName(int index);
    juce::Array<MidiTrack*> getAllTracks();
    juce::OwnedArray<MidiTrack>& getMidiTracks();
    int getNumberOfTracks();
private:
    juce::OwnedArray<MidiTrack> tracks;
    ProjectSettings& settings;
};