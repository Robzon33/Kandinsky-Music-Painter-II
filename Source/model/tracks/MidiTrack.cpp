/*
  ==============================================================================

    MidiTrack.cpp
    Created: 21 Jun 2021 5:49:00pm
    Author:  Toko

  ==============================================================================
*/

#include "MidiTrack.h"

void MidiTrack::setChannel(int newChannel)
{
    this->channel = newChannel;
}

int MidiTrack::getChannel()
{
    return this->channel;
}

void MidiTrack::setProgram(int newProgram)
{
    this->program = newProgram;
}

int MidiTrack::getProgram()
{
    return this->program;
}

