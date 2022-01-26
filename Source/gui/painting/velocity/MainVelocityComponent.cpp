/*
  ==============================================================================

    MainVelocityComponent.cpp
    Created: 25 Jan 2022 3:46:58pm
    Author:  Toko

  ==============================================================================
*/

#include "MainVelocityComponent.h"

MainVelocityComponent::MainVelocityComponent(MainModel& mm, ProjectSettings& ps)
    : model (mm), settings (ps)
{
}

MainVelocityComponent::~MainVelocityComponent()
{
}

void MainVelocityComponent::paint(juce::Graphics& g)
{
    g.setColour(juce::Colours::black);
    for (int i = 100; i <= settings.getWidth(); i = i + 100)
    {
        g.drawVerticalLine(i, 0.0f, (float)getHeight());
    }
}

void MainVelocityComponent::resized()
{
}

void MainVelocityComponent::setSelectedMidiVelocityData(int index)
{
    this->velocities[index]->toFront(true);
}

void MainVelocityComponent::addVelocityComponent(MidiTrack* newMidiTrack)
{
    VelocityComponent* newVelocityComponent = new VelocityComponent(*newMidiTrack);
    addAndMakeVisible(newVelocityComponent);
    newVelocityComponent->setBounds(getLocalBounds());
    velocities.add(newVelocityComponent);
}

void MainVelocityComponent::deleteVelocityComponent(int index)
{
    velocities.remove(index);
}

void MainVelocityComponent::deleteAllVelocityComponents()
{
    velocities.clear(true);
}
