/*
  ==============================================================================

    MidiTrack.h
    Created: 21 Jun 2021 5:49:00pm
    Author:  Toko
    
    MidiTrack extends TrackData. An MidiTrack object holds necessary MIDI
    data like program and channel number.

  ==============================================================================
*/

#pragma once

#include "TrackData.h"
#include "MidiVelocityData.h"

class MidiTrack : public TrackData
{
public:
    void setChannel(int newChannel);
    int getChannel();
    void setProgram(int newProgram);
    int getProgram();
private:
    int channel, program;
    std::unique_ptr<MidiVelocityData> midiVelocityData;
};