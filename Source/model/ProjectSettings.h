/*
  ==============================================================================

    ProjectSettings.h
    Created: 21 Jun 2021 7:18:02pm
    Author:  Toko

  ==============================================================================
*/

#pragma once

#include "JuceHeader.h"

class ProjectSettings
{
public:
    ProjectSettings();
    ProjectSettings(juce::String projectName);
    ~ProjectSettings();
    void init(juce::String projectName);

    void setName(juce::String newName);
    juce::String getName();
    void setBpm(int newBpm);
    int getBpm();
    void setNumberOfBeats(int newNumberOfBeats);
    int getNumberOfBeats();
private:
    juce::String name;
    int numberOfBeats;
    int bpm;
    int maxNumberOfTracks = 20;
};