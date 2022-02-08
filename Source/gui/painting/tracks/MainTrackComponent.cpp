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
    drawer.reset(new Drawer());
    playerViewComponent.reset(new PlayerViewComponent(mp, scaleFactor));
    addAndMakeVisible(playerViewComponent.get());
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
}

void MainTrackComponent::resized()
{
    playerViewComponent->setBounds(getLocalBounds());
    for each (TrackComponent * tc in tracks)
    {
        tc->setBounds(getLocalBounds());
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
    this->resized();
}

void MainTrackComponent::setScaleFactor(float newScaleFactor)
{
    this->scaleFactor = newScaleFactor;
    this->setWidth();
    for each (TrackComponent * tc in tracks)
    {
        tc->setScaleFactor(scaleFactor);
    }
    playerViewComponent->setScaleFactor(scaleFactor);
}
