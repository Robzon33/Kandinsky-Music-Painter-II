/*
  ==============================================================================

    MainModel.h
    Created: 27 Jun 2021 10:05:23pm
    Author:  Toko

  ==============================================================================
*/

#pragma once

#include "tracks/TrackData.h"

class MainModel
{
public:
    MainModel();
    ~MainModel();

    void TestFunction();
    bool GetTest();

    juce::Array<TrackData*> getAllTracks();
    int getNumberOfTracks();
private:
    juce::OwnedArray<TrackData> tracks;
    bool test = false;
};