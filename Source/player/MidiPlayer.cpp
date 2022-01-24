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
    mm.addChangeListener(this);
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
    this->produceMidiMessages();
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
    startTimer(100);
}

void MidiPlayer::stop()
{
    m_pState->Stop(this);

    stopTimer();
    midiBuffer.addEvent(juce::MidiMessage::allNotesOff(1), 1);
    this->position = 0;
    sendChangeMessage();
}

void MidiPlayer::pause()
{
    m_pState->Pause(this);

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

void MidiPlayer::changeListenerCallback(juce::ChangeBroadcaster* source)
{
    if (source == &mainModel)
    {
        for each (MidiTrack* track in mainModel.getMidiTracks())
        {
            track->addChangeListener(this);
        }
    }
    else
    {
        for each (MidiTrack* track in mainModel.getMidiTracks())
        {
            if (source == track)
            {
                juce::MidiMessage message(juce::MidiMessage::programChange(track->getChannel(),
                    track->getProgram()));
                this->midiBuffer.addEvent(message, 0);
                this->processorFlag = true;
            }
        }
    }
}

void MidiPlayer::produceMidiMessages()
{
    juce::Array<float> yValues;

    for each (MidiTrack * track in mainModel.getMidiTracks())
    {
        int channel = 1; /* TODO: get channel from track! */

        // initialize a new array on stack to store new note on messages
        juce::OwnedArray<bool> noteOnMessages;
        for (int j = 0; j < 128; ++j)
            noteOnMessages.add(false);

        // calculate intersections
        for each (juce::Path * path in track->getPathVector())
        {
            yValues.addArray(this->calculateIntersections(path));
        }

        // produce note on messages
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
                        noteOnMessages.set(note, new bool(true), true);
                        this->midiBuffer.addEvent(message, 0);
                    }
                    noteOnMessages.set(note, new bool(true), true);
                }
            }
        }

        // produce note off messages
        for (int k = 0; k < 128; ++k)
        {
            if (previousNotesOn[k] && !noteOnMessages[k])
            {
                juce::MidiMessage message(juce::MidiMessage::noteOff(channel, k));
                this->midiBuffer.addEvent(message, 0);
            }
        }

        previousNotesOn.swapWith(noteOnMessages);
    }
}

juce::Array<float> MidiPlayer::calculateIntersections(juce::Path* path)
{
    juce::Array<float> yValues;

    int xBoundLeft = path->getBounds().getX();
    int xBoundRight = path->getBounds().getX() + path->getBounds().getWidth();

    if (this->position >= xBoundLeft && this->position <= xBoundRight)
    {
	    const float tolerance = 1.0f;
	    juce::Line<float> line((float)this->position, 0, (float)this->position, 128);

	    juce::PathFlatteningIterator iterator(*path, juce::AffineTransform(), tolerance);
	    juce::Point<float> intersection;

	    while (iterator.next())
	    {
		    if (line.intersects(juce::Line<float>(iterator.x1, iterator.y1, iterator.x2, iterator.y2), intersection))
		    {
			    yValues.add(intersection.getY());
		    }

            // the intersects method does not identify intersections between two vertical lines. So it is 
            // necessary to take care of it manually.
		    if (iterator.x1 == iterator.x2)
		    {
			    int min = juce::jmin<int>(iterator.y1, iterator.y2);
			    int max = juce::jmax<int>(iterator.y1, iterator.y2);

			    for (int i = min; i < max; i++)
			    {
				    yValues.add(i);
			    }
		    }
	    }
    }

	return yValues;
}
