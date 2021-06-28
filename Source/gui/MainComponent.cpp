/*
  ==============================================================================

    MainComponent.cpp
    Created: 21 Jun 2021 9:20:53pm
    Author:  Toko

  ==============================================================================
*/

#include "MainComponent.h"

MainComponent::MainComponent(MainModel& m, MidiPlayer& mp)
    : mainModel (m), player (mp)
{
}

MainComponent::~MainComponent()
{
}

void MainComponent::paint(juce::Graphics& g)
{
    g.fillAll(juce::Colours::lightblue);

    g.setColour(juce::Colours::darkblue);
    g.setFont(20.0f);
    g.drawText("Hello KMP II User!", getLocalBounds(), juce::Justification::centred, true);
}

void MainComponent::resized()
{
}

void MainComponent::mouseDown(const juce::MouseEvent& event)
{
    player.play();
}
