/*
  ==============================================================================

    MainTrackComponent.cpp
    Created: 14 Jul 2021 7:05:43pm
    Author:  Toko

  ==============================================================================
*/

#include "MainTrackComponent.h"

MainTrackComponent::MainTrackComponent(MainModel& mm, MidiPlayer& mp)
    : model(mm), player(mp)
{
    player.addChangeListener(this);
}

MainTrackComponent::~MainTrackComponent()
{
}

void MainTrackComponent::paint(juce::Graphics& g)
{
    //paint the players position
    g.setColour(juce::Colours::blue);
    g.drawLine(player.getPosition(), 0, player.getPosition(), getHeight(), 2.0f);
}

void MainTrackComponent::resized()
{
}

void MainTrackComponent::changeListenerCallback(juce::ChangeBroadcaster* source)
{
    repaint();
}

void MainTrackComponent::updateContent()
{
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
