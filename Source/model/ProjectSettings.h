/*
  ==============================================================================

    ProjectSettings.h
    Created: 21 Jun 2021 7:18:02pm
    Author:  Toko

  ==============================================================================
*/

#pragma once

#include "JuceHeader.h"

class ProjectSettings : public juce::ChangeBroadcaster
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
    void setPlayerSpeed(int newPlayerSpeed);
    int getPlayerSpeed();
    void setWidth(int newWidth);
    int getWidth();
    int getMaxNumberOfMidiTracks();
private:
    juce::String name;
    int width; /* The projects width in pixels. */
    int playerSpeed; /* The players speed in pixel per second. */
    int bpm;
    const int maxNumberOfMidiTracks = 16;
};