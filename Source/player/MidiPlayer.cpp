/*
  ==============================================================================

    MidiPlayer.cpp
    Created: 27 Jun 2021 10:06:04pm
    Author:  Toko

  ==============================================================================
*/

#include "MidiPlayer.h"

MidiPlayer::MidiPlayer(ProjectSettings& ps, MainModel& mm)
    : settings (ps), mainModel (mm)
{
    processorFlag = false;
    position = 0.0f;
}

MidiPlayer::~MidiPlayer()
{
    this->stop();
}

void MidiPlayer::hiResTimerCallback()
{
    auto message = juce::MidiMessage::noteOn(2, 40, 0.9f);
    this->midiBuffer.addEvent(message, 2);
    processorFlag = true;
}

void MidiPlayer::play()
{
    startTimer(2000);
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
