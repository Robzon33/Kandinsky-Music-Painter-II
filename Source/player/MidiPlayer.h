/*
  ==============================================================================

    MidiPlayer.h
    Created: 27 Jun 2021 10:06:04pm
    Author:  Toko

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "../model/MainModel.h"
#include "../model/ProjectSettings.h"

class MidiPlayer    : private juce::HighResolutionTimer
{
public:
    MidiPlayer(MainModel&, ProjectSettings&);
    ~MidiPlayer();

    void hiResTimerCallback() override;
    void play();
    void stop();
    juce::MidiBuffer getMidiBuffer();
private:
    juce::MidiBuffer midiBuffer;
    MainModel& mainModel;
    ProjectSettings& settings;
    float position; /* The players position in beats. */
    bool processorFlag; /* Indicates whether the processor is allowed to acces the midi buffer. */
};
