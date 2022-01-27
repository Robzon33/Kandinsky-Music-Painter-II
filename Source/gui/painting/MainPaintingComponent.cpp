/*
  ==============================================================================

    MainPaintingComponent.cpp
    Created: 6 Jul 2021 11:10:50am
    Author:  Toko

  ==============================================================================
*/

#include "MainPaintingComponent.h"

MainPaintingComponent::MainPaintingComponent(MainModel& mm, MidiPlayer& mp, ProjectSettings& ps)
    : model (mm), player (mp), settings (ps)
{
    drawBeatLines = true;
    showToolComponent = false;
    scaleFactor = 1.0f;
    backgroundColour = juce::Colours::black.brighter(0.1f);

    paintingHeader.reset(new HeaderComponent("Painting"));
    addAndMakeVisible(paintingHeader.get());

    trackComponent.reset(new MainTrackComponent(model, player, settings));
    addAndMakeVisible(trackComponent.get());

    velocityHeader.reset(new HeaderComponent("Velocity"));
    addAndMakeVisible(velocityHeader.get());

    velocityComponent.reset(new MainVelocityComponent(model, settings));
    addAndMakeVisible(velocityComponent.get());
}

MainPaintingComponent::~MainPaintingComponent()
{
}

void MainPaintingComponent::paint(juce::Graphics& g)
{
    g.fillAll(backgroundColour);
}

void MainPaintingComponent::resized()
{
    auto b = getLocalBounds();

    paintingHeader->setBounds(b.removeFromTop(40));

    trackComponent->setBounds(b.removeFromTop(128 * scaleFactor));

    if (showToolComponent)
    {

    }

    velocityHeader->setBounds(b.removeFromTop(40));

    velocityComponent->setBounds(b.removeFromTop(128));
}

void MainPaintingComponent::mouseDown(const juce::MouseEvent& event)
{
}

void MainPaintingComponent::addNewTrack(MidiTrack* newTrack)
{
    trackComponent->addTrackComponent(newTrack);
    velocityComponent->addVelocityComponent(newTrack);
}

void MainPaintingComponent::deleteTrackComponent(int index)
{
    trackComponent->deleteTrackComponent(index);
    velocityComponent->deleteVelocityComponent(index);
}

void MainPaintingComponent::deleteAllTrackComponents()
{
    trackComponent->deleteAllTrackComponents();
    velocityComponent->deleteAllVelocityComponents();
}

void MainPaintingComponent::setSelectedTrack(int index)
{
    trackComponent->setSelectedTrack(index);
    velocityComponent->setSelectedMidiVelocityData(index);
}
