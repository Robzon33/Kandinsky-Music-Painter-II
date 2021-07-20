/*
  ==============================================================================

    MainPaintingComponent.cpp
    Created: 6 Jul 2021 11:10:50am
    Author:  Toko

  ==============================================================================
*/

#include "MainPaintingComponent.h"

MainPaintingComponent::MainPaintingComponent(MainModel& mm, MidiPlayer& mp)
    : model (mm), player (mp)
{
    drawBeatLines = true;
    showToolComponent = false;
    scaleFactor = 1.0f;
    backgroundColour = juce::Colours::whitesmoke;

    paintingHeader.reset(new HeaderComponent("Painting"));
    addAndMakeVisible(paintingHeader.get());

    trackComponent.reset(new MainTrackComponent(model, player));
    addAndMakeVisible(trackComponent.get());

    velocityHeader.reset(new HeaderComponent("Velocity"));
    addAndMakeVisible(velocityHeader.get());
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
}

void MainPaintingComponent::mouseDown(const juce::MouseEvent& event)
{
    model.TestFunction();
    player.play();
}

void MainPaintingComponent::addNewTrack(MidiTrack* newTrack)
{
    trackComponent->addTrackComponent(newTrack);
}

void MainPaintingComponent::deleteTrackComponent(int index)
{
    trackComponent->deleteTrackComponent(index);
}

void MainPaintingComponent::deleteAllTrackComponents()
{
    trackComponent->deleteAllTrackComponents();
}
