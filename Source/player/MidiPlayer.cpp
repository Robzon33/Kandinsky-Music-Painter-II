/*
  ==============================================================================

    MidiPlayer.cpp
    Created: 27 Jun 2021 10:06:04pm
    Author:  Toko

  ==============================================================================
*/

#include "MidiPlayer.h"

MidiPlayer::MidiPlayer(ProjectSettings& ps, MainModel& mm)
    : settings (ps), mainModel (mm), m_pState(new StoppedState())
{
    processorFlag = false;
    position = 0;
}

MidiPlayer::~MidiPlayer()
{
    this->stop();
    delete m_pState;
}

void MidiPlayer::hiResTimerCallback()
{
    this->position = position + 1;
    if (position >= settings.getNumberOfBeats() * 100)
    {
        position = 0;
    }
    this->calculateEvents();
    processorFlag = true;

    /* notify change listener */
    sendChangeMessage();
}

void MidiPlayer::play()
{
    m_pState->Play(this);
    
    previousNotesOn.clear(true);
    for (int i = 0; i < 128; i++)
    {
        previousNotesOn.add(false);
    }
    startTimer(10);
}

void MidiPlayer::stop()
{
    stopTimer();
    midiBuffer.addEvent(juce::MidiMessage::allNotesOff(1), 1);
    this->position = 0;
    sendChangeMessage();
}

void MidiPlayer::pause()
{
    stopTimer();
    midiBuffer.addEvent(juce::MidiMessage::allNotesOff(1), 1);
}

juce::MidiBuffer MidiPlayer::getMidiBuffer()
{
    juce::MidiBuffer bufferToReturn;
    if (processorFlag)
    {
        bufferToReturn = this->midiBuffer;
        this->midiBuffer.clear();
        processorFlag = false;
    }
    return bufferToReturn;
}

int MidiPlayer::getPosition()
{
    return position;
}

void MidiPlayer::setState(State state)
{
	delete m_pState;

	if (state == ST_STOPPED)
	{
		m_pState = new StoppedState();
	}
	else if (state == ST_PLAYING)
	{
		m_pState = new PlayingState();
	}
	else
	{
		m_pState = new PausedState();
	}
}

MidiPlayer::State MidiPlayer::getState()
{
    if (dynamic_cast<StoppedState*>(m_pState))
    {
        return State::ST_STOPPED;
    }
    else if (dynamic_cast<PlayingState*>(m_pState))
    {
        return State::ST_PLAYING;
    }
    else
    {
        return State::ST_PAUSED;
    }
}

void MidiPlayer::registerListener(juce::ChangeListener* listener)
{
    this->addChangeListener(listener);
}

void MidiPlayer::calculateEvents()
{
    juce::Array<float> yValues;

    for each (TrackData* track in mainModel.getAllTracks())
    {
        int channel = 1; /* TODO: get channel from track! */
        
        // initialize a new array on stack to store new note on messages
        juce::OwnedArray<bool> newNoteOn;
        for (int j = 0; j < 128; ++j)
            newNoteOn.add(false);

        // find intersections
        for each (juce::Path* path in track->getPathVector())
        {
            const float tolerance = 1.0f;
            juce::PathFlatteningIterator iterator(*path, juce::AffineTransform(), tolerance);

            juce::Line<float> line((float)this->position, 0, (float)this->position, 128);
            juce::Point<float> intersection;

            while (iterator.next())
            {
                if (line.intersects(juce::Line<float>(iterator.x1, iterator.y1, iterator.x2, iterator.y2), intersection))
                {
                    yValues.add(intersection.getY());
                }
            }
        }

        // generate Midi Messages
        if (!yValues.isEmpty())
        {
            for (int i = 0; i < yValues.size(); i++)
            {
                int note = static_cast<int>(127 - yValues[i]);

                if (note >= 0 && note <= 127)
                {
                    if (!previousNotesOn[note])
                    {
                        juce::MidiMessage message(juce::MidiMessage::noteOn(channel, note, 0.9f));
                        newNoteOn.set(note, new bool(true), true);
                        this->midiBuffer.addEvent(message, 0);
                    }
                    newNoteOn.set(note, new bool(true), true);
                }
            }
        }

        // after all note on messages have been added to the buffer send note off messages
        for (int k = 0; k < 128; ++k)
        {
            if (previousNotesOn[k] && !newNoteOn[k])
            {
                juce::MidiMessage message(juce::MidiMessage::noteOff(channel, k));
                this->midiBuffer.addEvent(message, 0);
            }
        }

        previousNotesOn.swapWith(newNoteOn);
    }
}
