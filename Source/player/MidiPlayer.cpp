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
    mainModel.addChangeListener(this);
    settings.addChangeListener(this);
    processorFlag = false;
    position = 0;
    this->resetPreviousNotesOn();
}

MidiPlayer::~MidiPlayer()
{
    this->stop();
    delete m_pState;
    this->masterReference.clear();
}

void MidiPlayer::hiResTimerCallback()
{
    this->position = position + 1;
    if (position >= settings.getWidth())
    {
        position = 0;
    }
    
    processorFlag = true;

    /* notify change listener */
    sendChangeMessage();
}

void MidiPlayer::play()
{
    m_pState->Play(this);
    this->resetPreviousNotesOn();
    startTimer(1000 / settings.getPlayerSpeed());
}

void MidiPlayer::stop()
{
    m_pState->Stop(this);
    stopTimer();
    this->sendAllNotesOffForEachChannel();
    midiMessageList.clear(true);
    this->position = 0;
    this->resetPreviousNotesOn();
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
        this->produceMidiMessages();
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

juce::OwnedArray<juce::MidiMessage>& MidiPlayer::getMidiMessageList()
{
    return this->midiMessageList;
}

void MidiPlayer::changeListenerCallback(juce::ChangeBroadcaster* source)
{
    if (source == &settings)
    {
        this->updatePlayerSpeed(settings.getPlayerSpeed());
    }
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
                this->addMessageToList(message);
                this->midiBuffer.addEvent(message, 0);
                this->processorFlag = true;
            }
        }
    }
}

void MidiPlayer::sendAllNotesOffForEachChannel()
{
    for (int i = 1; i <= 16; ++i)
    {
        juce::MidiMessage message(juce::MidiMessage::allNotesOff(i));
        if (message.getRawDataSize() == 3)
        {
            midiBuffer.addEvent(message, 0);
            this->processorFlag = true;
        }
    }
}

void MidiPlayer::resetPreviousNotesOn()
{
    previousNotesOn.clear(true);
    for (int i = 1; i <= 16; i++)
    {
        juce::Array<bool>* newArray = new juce::Array<bool>;
        for (int j = 0; j < 128; j++)
        {
            newArray->add(false);
        }
        previousNotesOn.add(newArray);
    }
}

void MidiPlayer::produceMidiMessages()
{
    juce::Array<float> yValues;

    for each (MidiTrack * track in mainModel.getMidiTracks())
    {
        int channel = track->getChannel();

        // initialize a new array on stack to store new note on messages
        juce::Array<bool> noteOnMessages;
        for (int j = 0; j < 128; ++j)
            noteOnMessages.add(false);

        // calculate intersections
        yValues = track->calculateIntersections(this->position);

        // produce note on messages
        if (!yValues.isEmpty())
        {
            for (int i = 0; i < yValues.size(); i++)
            {
                int note = static_cast<int>(127 - yValues[i]);
                
                if (note >= 0 && note <= 127)
                {
                    if (!(previousNotesOn.getUnchecked(channel)->getUnchecked(note)))
                    {
                        juce::uint8 velocity = track->getMidiVelocityData().getVelocity(this->position);
                        juce::MidiMessage message(juce::MidiMessage::noteOn(channel, note, velocity));
                        this->midiBuffer.addEvent(message, 0);

                        (new OutgoingMessageCallback(this, message))->post();
                    }
                    noteOnMessages.set(note, true);
                }
            }
        }

        // produce note off messages
        for (int k = 0; k < 128; ++k)
        {
            if (previousNotesOn.getUnchecked(channel)->getUnchecked(k) && 
                !noteOnMessages.getUnchecked(k))
            {
                juce::MidiMessage message(juce::MidiMessage::noteOff(channel, k));
                (new OutgoingMessageCallback(this, message))->post();
                this->midiBuffer.addEvent(message, 0);
            }
        }

        previousNotesOn.getUnchecked(channel)->swapWithArray(noteOnMessages);
    }
}

void MidiPlayer::addMessageToList(const juce::MidiMessage& message)
{
    midiMessageList.add(new juce::MidiMessage(message));

    if (midiMessageList.size() > 200)
    {
        midiMessageList.removeRange(0, 1, true);
    }
}

void MidiPlayer::updatePlayerSpeed(int pixelsPerSecond)
{
    if (this->getState() == State::ST_PLAYING)
    {
        startTimer(1000 / pixelsPerSecond);
    }
}
