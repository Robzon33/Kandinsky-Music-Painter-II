/*
  ==============================================================================

    MainTrackComponent.cpp
    Created: 14 Jul 2021 7:05:43pm
    Author:  Toko

  ==============================================================================
*/

#include "MainTrackComponent.h"

MainTrackComponent::MainTrackComponent(MainModel& mm, MidiPlayer& mp, ProjectSettings& ps)
    : model(mm), player(mp), settings (ps)
{
    player.addChangeListener(this);
}

MainTrackComponent::~MainTrackComponent()
{
}

void MainTrackComponent::paint(juce::Graphics& g)
{
    //draw vertical lines
	g.setColour(juce::Colours::black);
	for (int i = 100; i <= settings.getWidth(); i = i + 100)
	{
		g.drawVerticalLine(i, 0.0f, (float)getHeight());
	}

    //paint the players position
    int thickness = 1;
    if (player.getPosition() > 0)
    {
        g.setColour(juce::Colours::blue);
        g.drawLine((float)player.getPosition(), 0, (float)player.getPosition(), getHeight(), 1.0f);
    }
}

void MainTrackComponent::resized()
{
}

void MainTrackComponent::changeListenerCallback(juce::ChangeBroadcaster* source)
{
    if (source == &player)
    {
        repaint(); // not nice because i draw everything at every time i receive the callback. Maybe outsourcing to another component for the player.
    }
}

void MainTrackComponent::setSelectedTrack(int index)
{
    this->tracks[index]->toFront(true);
}

void MainTrackComponent::addTrackComponent(MidiTrack* newTrack)
{
    TrackComponent* newTrackComponent = new TrackComponent(*newTrack);
    addAndMakeVisible(newTrackComponent);
    newTrackComponent->setBounds(getLocalBounds());
    tracks.add(newTrackComponent);
}

void MainTrackComponent::deleteTrackComponent(int index)
{
    tracks.remove(index);
}

void MainTrackComponent::deleteAllTrackComponents()
{
    tracks.clear(true);
}
