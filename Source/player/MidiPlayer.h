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
#include "../extensions/PlayerState.h"

class PlayerState;

class MidiPlayer    : private juce::HighResolutionTimer
{
public:
    enum State
    {
        ST_STOPPED = 0,
        ST_PLAYING,
        ST_PAUSED
    };

    MidiPlayer(ProjectSettings& ps, MainModel& mm);
    ~MidiPlayer();

    void hiResTimerCallback() override;
    void play();
    void stop();
    void pause();
    juce::MidiBuffer getMidiBuffer();

    void setState(State state);
    State getState();
private:
    juce::MidiBuffer midiBuffer;
    MainModel& mainModel;
    ProjectSettings& settings;
    PlayerState* m_pState;
    float position; /* The players position in beats. */
    bool processorFlag; /* Indicates whether the processor is allowed to acces the midi buffer. */
};
