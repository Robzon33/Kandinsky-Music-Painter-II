/*
  ==============================================================================

    MainVelocityComponent.cpp
    Created: 25 Jan 2022 3:46:58pm
    Author:  Toko

  ==============================================================================
*/

#include "MainVelocityComponent.h"

MainVelocityComponent::MainVelocityComponent(MainModel& mm)
    : model (mm)
{
}

MainVelocityComponent::~MainVelocityComponent()
{
}

void MainVelocityComponent::paint(juce::Graphics& g)
{
    g.setColour(juce::Colours::aquamarine);
    g.fillAll();
}

void MainVelocityComponent::resized()
{
}

void MainVelocityComponent::setSelectedMidiVelocityData(int index)
{
    this->velocities[index]->toFront(true);
}

void MainVelocityComponent::addVelocityComponent(MidiVelocityData* newVelocityData)
{
    VelocityComponent* newVelocityComponent = new VelocityComponent(*newVelocityData);
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
