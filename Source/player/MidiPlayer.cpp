/*
  ==============================================================================

    MidiPlayer.cpp
    Created: 27 Jun 2021 10:06:04pm
    Author:  Toko

  ==============================================================================
*/

#include "MidiPlayer.h"

MidiPlayer::MidiPlayer(MainModel& m, ProjectSettings& p)
    : mainModel (m), settings (p)
{
    this->processorFlag = false;
}

MidiPlayer::~MidiPlayer()
{
    this->stopTimer();
}

void MidiPlayer::hiResTimerCallback()
{
    auto message = juce::MidiMessage::noteOn(1, 60, 0.9f);
    this->midiBuffer.addEvent(message, 1);
    processorFlag = true;
}

void MidiPlayer::play()
{
    startTimer(600 / this->settings.getBpm());
}

void MidiPlayer::stop()
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
