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
    int getPosition();

    void setState(State state);
    State getState();

    void registerListener(juce::ChangeListener* listener);
private:
    juce::MidiBuffer midiBuffer;
    MainModel& mainModel;
    ProjectSettings& settings;
    PlayerState* m_pState;
    int position; /* The players position in pixels (x-axis). */
    bool processorFlag; /* Indicates whether the processor is allowed to acces the midi buffer. */
    juce::OwnedArray<bool> previousNotesOn; /* Indicates wether a certain note has been played in the previous step. */

    /// <summary>
    /// Produces Midi Messages and adds them to the Midi Buffer.
    /// </summary>
    void produceMidiMessages();

    /// <summary>
    /// Calculates all intersections between the given path and the current players position.
    /// </summary>
    /// <returns></returns>
    juce::Array<float> calculateIntersections(juce::Path* path);
};
