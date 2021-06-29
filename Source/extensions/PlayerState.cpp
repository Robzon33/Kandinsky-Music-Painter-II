/*
  ==============================================================================

    PlayerState.cpp
    Created: 29 Jun 2021 6:06:26pm
    Author:  Toko

  ==============================================================================
*/

#include "PlayerState.h"

PlayerState::PlayerState(std::string name)
	: m_name(name) {

}

PlayerState::~PlayerState() {
}

void PlayerState::Play(MidiPlayer*)
{
	std::cout << "Illegal state transition from " << GetName() << " to Playing\n";
}

void PlayerState::Pause(MidiPlayer*)
{
	std::cout << "Illegal state transition from " << GetName() << " to Paused\n";
}

void PlayerState::Stop(MidiPlayer*)
{
	std::cout << "Illegal state transition from " << GetName() << " to Stopped\n";
}

//==============================================================================

PlayingState::PlayingState()
	: PlayerState(std::string("Playing")) {
}

PlayingState::~PlayingState() {
}

void PlayingState::Pause(MidiPlayer* player)
{
	player->setState(MidiPlayer::ST_PAUSED);
}

void PlayingState::Stop(MidiPlayer* player)
{
	player->setState(MidiPlayer::ST_STOPPED);
}

//==============================================================================

PausedState::PausedState()
	: PlayerState(std::string("Paused")) {
}

PausedState::~PausedState() {
}

void PausedState::Play(MidiPlayer* player)
{
	player->setState(MidiPlayer::ST_PLAYING);
}

void PausedState::Stop(MidiPlayer* player)
{
	player->setState(MidiPlayer::ST_STOPPED);
}

//==============================================================================

StoppedState::StoppedState()
	: PlayerState(std::string("Stopped")) {
}

StoppedState::~StoppedState() {
}

void StoppedState::Play(MidiPlayer* player)
{
	player->setState(MidiPlayer::ST_PLAYING);
}