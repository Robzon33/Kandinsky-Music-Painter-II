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
    auto message = juce::MidiMessage::noteOn(2, 40, 0.9f);
    this->midiBuffer.addEvent(message, 2);
    processorFlag = true;
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
