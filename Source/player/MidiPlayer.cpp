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
    position = 0.0f;
}

MidiPlayer::~MidiPlayer()
{
    this->stop();
    delete m_pState;
}

void MidiPlayer::hiResTimerCallback()
{
    /*auto message = juce::MidiMessage::noteOn(2, 40, 0.9f);
    this->midiBuffer.addEvent(message, 2);*/
    this->position = position + 1;
    this->calculateEvents();
    processorFlag = true;

    if (position > 10)
    {
        position = 0;
    }

    /* notify change listener */
    sendChangeMessage();
}

void MidiPlayer::play()
{
    m_pState->Play(this);
    startTimer(2000);
}

void MidiPlayer::stop()
{
    stopTimer();
    midiBuffer.addEvent(juce::MidiMessage::allNotesOff(1), 1);
}

void MidiPlayer::pause()
{
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

float MidiPlayer::getPosition()
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
        // find intersections
        for each (juce::Path* path in track->getPathVector())
        {
            const float tolerance = 1.0f;
            juce::PathFlatteningIterator iterator(*path, juce::AffineTransform(), tolerance);

            juce::Line<float> line(this->position, 0, this->position, 128);
            juce::Point<float> intersection;

            while (iterator.next())
            {
                if (line.intersects(juce::Line<float>(iterator.x1, iterator.y1, iterator.x2, iterator.y2), intersection))
                {
                    yValues.add(intersection.getY());
                }
            }
        }

        // generate midi messages
        if (!yValues.isEmpty())
        {
            for (int i = 0; i < yValues.size(); i++)
            {
                int note = static_cast<int>(127 - yValues[i]);
                if (0 <= note < 128)
                {
                    juce::uint8 velocity = 100; /* not yet calculated */
                    juce::MidiMessage message(juce::MidiMessage::noteOn(2, note, 0.9f));
                    this->midiBuffer.addEvent(message, 0);
                }
            }
        }
    }
}
