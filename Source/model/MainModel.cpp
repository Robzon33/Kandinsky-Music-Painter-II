/*
  ==============================================================================

    MainModel.cpp
    Created: 27 Jun 2021 10:05:23pm
    Author:  Toko

  ==============================================================================
*/

#include "MainModel.h"

MainModel::MainModel()
{
}

MainModel::~MainModel()
{
}

void MainModel::TestFunction()
{
    /*TrackData* track = new TrackData();

    juce::Path* newPath = new juce::Path();
    newPath->startNewSubPath(1, 120);
    newPath->lineTo(10, 10);
    track->addPath(newPath);
    this->tracks.add(track);*/
}

bool MainModel::GetTest()
{
    return test;
}

bool MainModel::addMidiTrack()
{
    if (tracks.size() <= 20/*from project settings*/)
    {
        MidiTrack* newTrack = new MidiTrack();
        tracks.add(newTrack);
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

juce::Array<TrackData*> MainModel::getAllTracks()
{
    juce::Array<TrackData*> tracksToReturn;

    for each (TrackData* track in tracks)
    {
        tracksToReturn.add(track);
    }

    return tracksToReturn;
}

int MainModel::getNumberOfTracks()
{
    return tracks.size();
}
