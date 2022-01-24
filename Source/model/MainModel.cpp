/*
  ==============================================================================

    MainModel.cpp
    Created: 27 Jun 2021 10:05:23pm
    Author:  Toko

  ==============================================================================
*/

#include "MainModel.h"

MainModel::MainModel(ProjectSettings& ps)
    : settings (ps)
{
}

MainModel::~MainModel()
{
}

bool MainModel::addMidiTrack()
{
    if (tracks.size() <= settings.getMaxNumberOfTracks())
    {
        MidiTrack* newTrack = new MidiTrack();
        tracks.add(newTrack);
        this->sendChangeMessage();
        return true;
    }

    return false;
}

MidiTrack* MainModel::getMidiTrack(int index)
{
    return tracks[index];
}

void MainModel::deleteTrack(int index)
{
    tracks.remove(index);
}

void MainModel::deleteAllTracks()
{
    tracks.clear();
}

int MainModel::getIndexOfLastTrack()
{
    return tracks.size() - 1;
}

juce::String MainModel::getTrackName(int index)
{
    return tracks[index]->getTrackName();
}

juce::Array<MidiTrack*> MainModel::getAllTracks()
{
    juce::Array<MidiTrack*> tracksToReturn;

    for each (MidiTrack* track in tracks)
    {
        tracksToReturn.add(track);
    }

    return tracksToReturn;
}

juce::OwnedArray<MidiTrack>& MainModel::getMidiTracks()
{
    return tracks;
}

int MainModel::getNumberOfTracks()
{
    return tracks.size();
}
