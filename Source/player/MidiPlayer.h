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
                    public juce::ChangeBroadcaster,
                    public juce::ChangeListener
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

    juce::OwnedArray<juce::MidiMessage>& getMidiMessageList();

    void changeListenerCallback(juce::ChangeBroadcaster* source);
private:
    juce::MidiBuffer midiBuffer;
    MainModel& mainModel;
    ProjectSettings& settings;
    PlayerState* m_pState;
    int position; /* The players position in pixels (x-axis). */
    bool processorFlag; /* Indicates whether the processor is allowed to acces the midi buffer. */
    juce::OwnedArray<juce::Array<bool>> previousNotesOn; /* Indicates for each midi channel wether a certain note has been played in the previous step. */
    juce::OwnedArray<juce::MidiMessage> midiMessageList;

    /// <summary>
    /// Produces note off midi messages and adds them to the midi buffer.
    /// </summary>
    void sendAllNotesOffForEachChannel();

    /// <summary>
    /// Resets or initializes the previous notes on array with false values for each channel.
    /// </summary>
    void resetPreviousNotesOn();

    /// <summary>
    /// Produces Midi Messages and adds them to the Midi Buffer.
    /// </summary>
    void produceMidiMessages();

    /// <summary>
    /// Adds a Midi Message to the players outgoing messages list.
    /// </summary>
    /// <param name="message">The message that needs to be added to the list.</param>
    void addMessageToList(const juce::MidiMessage& message);

    /// <summary>
    /// Adjusts the players timer to the configured speed.
    /// </summary>
    /// <param name="pixelsPerSecond">The new speed in pixels per seconds.</param>
    void updatePlayerSpeed(int pixelsPerSecond);

    /* This is used to dispach an outgoing message to the message thread. */
    struct OutgoingMessageCallback : public juce::CallbackMessage
    {
        OutgoingMessageCallback(MidiPlayer* mp, const juce::MidiMessage& m)
            : midiPlayer (mp), message (m)
        {
        }

        void messageCallback() override
        {
            if (midiPlayer != nullptr)
                midiPlayer->addMessageToList(message);
        }

        juce::MidiMessage message;
        juce::WeakReference<MidiPlayer> midiPlayer;
    };

    juce::WeakReference<MidiPlayer>::Master masterReference;
    friend class juce::WeakReference<MidiPlayer>;
};
