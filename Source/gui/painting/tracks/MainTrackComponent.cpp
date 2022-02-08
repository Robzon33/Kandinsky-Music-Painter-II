/*
  ==============================================================================

    MainTrackComponent.cpp
    Created: 14 Jul 2021 7:05:43pm
    Author:  Toko

  ==============================================================================
*/

#include "MainTrackComponent.h"

MainTrackComponent::MainTrackComponent(MainModel& mm, MidiPlayer& mp, ProjectSettings& ps, float scaleFactor)
    : model(mm), player(mp), settings (ps)
{
    player.addChangeListener(this);
    drawer.reset(new Drawer());
    this->scaleFactor = scaleFactor;
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
		g.drawVerticalLine(i * scaleFactor, 0.0f, (float)this->height * scaleFactor);
	}

    //paint the players position
    int thickness = 1;
    if (player.getPosition() > 0)
    {
        g.setColour(juce::Colours::blue);
        g.drawLine((float)player.getPosition() * scaleFactor, 0, (float)player.getPosition() * scaleFactor, this->height * scaleFactor, scaleFactor);
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
    TrackComponent* newTrackComponent = new TrackComponent(*newTrack, *drawer, scaleFactor);
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

void MainTrackComponent::setSelectedTool(int index)
{
    drawer->setSelectedTool(index);
}

void MainTrackComponent::setWidth()
{
    setSize(settings.getWidth() * scaleFactor, this->height * scaleFactor);

    for each (TrackComponent * tc in tracks)
    {
        tc->setSize(settings.getWidth() * scaleFactor, this->height * scaleFactor);
    }
}

void MainTrackComponent::setScaleFactor(float newScaleFactor)
{
    this->scaleFactor = newScaleFactor;
    setWidth();
    for each (TrackComponent * tc in tracks)
    {
        tc->setScaleFactor(scaleFactor);
    }
}
