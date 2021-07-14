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
    menuBar.reset(new MenuBarComponent(mainModel));
    addAndMakeVisible(menuBar.get());
    playerBar.reset(new PlayerComponent(player));
    addAndMakeVisible(playerBar.get());
    trackList.reset(new TrackListBoxComponent(mainModel));
    addAndMakeVisible(trackList.get());
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
    auto b = getLocalBounds();

    menuBar->setBounds(b.removeFromTop(30));
    playerBar->setBounds(b.removeFromBottom(100));
    trackList->setBounds(b.removeFromLeft(150));
}

void MainComponent::mouseDown(const juce::MouseEvent& event)
{
    mainModel.TestFunction();
    player.play();
    //MidiPlayer::State currentState = player.getState();
}
