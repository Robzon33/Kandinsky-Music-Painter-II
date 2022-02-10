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
    settings.addChangeListener(this);
}

MainModel::~MainModel()
{
}

bool MainModel::addMidiTrack()
{
    if (tracks.size() < settings.getMaxNumberOfMidiTracks() - 1)
    {
        MidiTrack* newTrack = new MidiTrack(settings.getWidth(),
                                            RandomColourGenerator::getRandomColour(),
                                            "New Midi Track",
                                            tracks.size() + 1);
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
    tracks.clear(true);
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

    for (auto* track : tracks)
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

void MainModel::updateTrackWidth(int newWidth)
{
    for (auto* track : tracks)
    {
        track->updateWidth(newWidth);
    }
}

void MainModel::changeListenerCallback(juce::ChangeBroadcaster* source)
{
    if (source == &settings)
    {
        this->updateTrackWidth(settings.getWidth());
    }
}
