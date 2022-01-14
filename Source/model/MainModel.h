/*
  ==============================================================================

    MainModel.h
    Created: 27 Jun 2021 10:05:23pm
    Author:  Toko

  ==============================================================================
*/

#pragma once

#include "tracks/MidiTrack.h"

class MainModel
{
public:
    MainModel();
    ~MainModel();

    bool addMidiTrack();
    MidiTrack* getMidiTrack(int index);
    void deleteTrack(int index);
    void deleteAllTracks();
    int getIndexOfLastTrack();
    juce::String getTrackName(int index);
    juce::Array<MidiTrack*> getAllTracks();
    int getNumberOfTracks();
private:
    juce::OwnedArray<MidiTrack> tracks;
    bool test = false;
};