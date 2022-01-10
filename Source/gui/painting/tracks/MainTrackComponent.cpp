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
    //draw beat lines
    g.setColour(juce::Colours::black);
    int thickness = 1;
    for (int i = 0; i <= settings.getNumberOfBeats(); ++i)
    {
        g.drawVerticalLine(i * 100, 0.0f, (float)getHeight());
    }

    //paint the players position
    g.setColour(juce::Colours::blue);
    g.drawLine(player.getPosition() * 100.0f, 0, player.getPosition() * 100.0f, getHeight(), 1.0f);
}

void MainTrackComponent::resized()
{
}

void MainTrackComponent::changeListenerCallback(juce::ChangeBroadcaster* source)
{
    if (source == &player)
    {
        repaint();
    } 
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
