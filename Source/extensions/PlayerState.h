/*
  ==============================================================================

    PlayerState.h
    Created: 29 Jun 2021 6:06:25pm
    Author:  Toko

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "../player/MidiPlayer.h"

class MidiPlayer;

class PlayerState {
public:
	PlayerState(std::string name);
	virtual ~PlayerState();

	virtual void Play(MidiPlayer* player);
	virtual void Pause(MidiPlayer* player);
	virtual void Stop(MidiPlayer* player);

	juce::String GetName() { return m_name; }
private:
	juce::String   m_name;
};

//==============================================================================

class PlayingState : public PlayerState {
public:
	PlayingState();
	virtual ~PlayingState();

	virtual void Pause(MidiPlayer* player);
	virtual void Stop(MidiPlayer* player);
};

//==============================================================================

class PausedState : public PlayerState {
public:
	PausedState();
	virtual ~PausedState();

	virtual void Play(MidiPlayer* player);
	virtual void Stop(MidiPlayer* player);
};

//==============================================================================

class StoppedState : public PlayerState {
public:
	StoppedState();
	virtual ~StoppedState();

	virtual void Play(MidiPlayer* player);
};