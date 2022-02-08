/*
  ==============================================================================

    PlayerViewComponent.cpp
    Created: 8 Feb 2022 1:52:25pm
    Author:  Toko

  ==============================================================================
*/

#include "PlayerViewComponent.h"

PlayerViewComponent::PlayerViewComponent(MidiPlayer& mp, float scaleFactor)
    : player (mp)
{
    this->scaleFactor = scaleFactor;
    player.addChangeListener(this);
}

PlayerViewComponent::~PlayerViewComponent()
{
}

void PlayerViewComponent::paint(juce::Graphics& g)
{
    if (player.getPosition() > 0)
    {
        g.setColour(juce::Colours::blue);
        g.drawLine((float)player.getPosition() * scaleFactor, 0, (float)player.getPosition() * scaleFactor, this->height * scaleFactor, scaleFactor);
    }
}

void PlayerViewComponent::resized()
{
}

void PlayerViewComponent::timerCallback()
{
    repaint();
}

void PlayerViewComponent::changeListenerCallback(juce::ChangeBroadcaster* source)
{
    if (player.getState() == MidiPlayer::State::ST_PLAYING)
    {
        this->startTimer(10);
    }
    else
    {
        this->stopTimer();
    }
}

void PlayerViewComponent::setScaleFactor(float newScaleFactor)
{
    this->scaleFactor = newScaleFactor;
    repaint();
}
