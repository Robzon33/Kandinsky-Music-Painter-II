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

class MidiPlayer :  private juce::HighResolutionTimer,
                    public juce::ChangeBroadcaster    
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
    float getPosition();

    void setState(State state);
    State getState();

    void registerListener(juce::ChangeListener* listener);
private:
    juce::MidiBuffer midiBuffer;
    MainModel& mainModel;
    ProjectSettings& settings;
    PlayerState* m_pState;
    float position; /* The players position in beats. */
    bool processorFlag; /* Indicates whether the processor is allowed to acces the midi buffer. */
    juce::OwnedArray<bool> previousNotesOn; /* Indicates wether a certain note has been played in the previous step. */

    /// <summary>
    /// Calculate intersections between all track data paths and the current players position.
    /// </summary>
    void calculateEvents();

    /// <summary>
    /// Checks the calculated y values and eliminates the values which have been used to
    /// generate a note on message in the previous step
    /// </summary>
    void filterYValues(juce::Array<float> yValues);
};
