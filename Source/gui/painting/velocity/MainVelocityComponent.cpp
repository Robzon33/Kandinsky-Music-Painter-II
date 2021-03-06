/*
  ==============================================================================

    MainVelocityComponent.cpp
    Created: 25 Jan 2022 3:46:58pm
    Author:  Toko

  ==============================================================================
*/

#include "MainVelocityComponent.h"

MainVelocityComponent::MainVelocityComponent(MainModel& mm, ProjectSettings& ps, float scaleFactor)
    : model (mm), settings (ps)
{
    this->scaleFactor = scaleFactor;
}

MainVelocityComponent::~MainVelocityComponent()
{
}

void MainVelocityComponent::paint(juce::Graphics& g)
{
    g.setColour(juce::Colours::black);
    for (int i = 100; i <= settings.getWidth(); i = i + 100)
    {
        g.drawVerticalLine(i * this->scaleFactor, 0.0f, (float)height * scaleFactor);
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
    VelocityComponent* newVelocityComponent = new VelocityComponent(*newMidiTrack, scaleFactor);
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

void MainVelocityComponent::setWidth()
{
    setSize(settings.getWidth() * this->scaleFactor, this->height * this->scaleFactor);

    for (auto* vc : velocities)
    {
        vc->setSize(settings.getWidth() * this->scaleFactor, this->height * this->scaleFactor);
    }
}

void MainVelocityComponent::setScaleFactor(float newScaleFactor)
{
    this->scaleFactor = newScaleFactor;
    setWidth();

    for (auto* vc : velocities)
    {
        vc->setScaleFactor(this->scaleFactor);
    }
}

void MainVelocityComponent::loadModel()
{
    this->velocities.clear(true);
    for (auto* track : model.getAllTracks())
    {
        addVelocityComponent(track);
    }
}
