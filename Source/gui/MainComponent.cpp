/*
  ==============================================================================

    MainComponent.cpp
    Created: 21 Jun 2021 9:20:53pm
    Author:  Toko

  ==============================================================================
*/

#include "MainComponent.h"

MainComponent::MainComponent(MainModel& m, MidiPlayer& mp, ProjectSettings& ps)
    : model (m), player (mp), settings (ps)
{
    menuBar.reset(new MenuBarComponent(model, commandManager));
    addAndMakeVisible(menuBar.get());
    
    playerBar.reset(new PlayerComponent(player));
    addAndMakeVisible(playerBar.get());
    
    trackList.reset(new TrackListBoxComponent(model));
    addAndMakeVisible(trackList.get());
    
    paintArea.reset(new MainPaintingComponent(model, player));
    paintArea->setSize(settings.getNumberOfBeats() * 100, 500);
    addAndMakeVisible(paintArea.get());

    paintViewport.reset(new juce::Viewport("Paint Viewport"));
    addAndMakeVisible(paintViewport.get());
    paintViewport->setViewedComponent(paintArea.get(), false);

    commandManager.registerAllCommandsForTarget(this);
    commandManager.setFirstCommandTarget(this);
}

MainComponent::~MainComponent()
{
}

void MainComponent::paint(juce::Graphics& g)
{
}

void MainComponent::resized()
{
    auto b = getLocalBounds();

    menuBar->setBounds(b.removeFromTop(30));
    playerBar->setBounds(b.removeFromBottom(100));
    trackList->setBounds(b.removeFromLeft(150));
    paintViewport->setBounds(b);
}

juce::ApplicationCommandTarget* MainComponent::getNextCommandTarget()
{
    return nullptr;
}

void MainComponent::getAllCommands(juce::Array<juce::CommandID>& c)
{
    juce::Array<juce::CommandID> commands{ CommandIDs::addMidiTrack,
                                           CommandIDs::deleteTrack,
                                           CommandIDs::deleteAllTracks };

    c.addArray(commands);
}

void MainComponent::getCommandInfo(juce::CommandID commandID, juce::ApplicationCommandInfo& result)
{
    switch (commandID)
    {
    case CommandIDs::addMidiTrack:
        result.setInfo("Add", "Adds a new track to the current project", "Track", 0);
        break;
    case CommandIDs::deleteTrack:
        result.setInfo("Delete", "Deletes the currently selected track", "Track", 0);
        break;
    case CommandIDs::deleteAllTracks:
        result.setInfo("Delete all", "Deletes all tracks from the current project", "Track", 0);
        break;
    default:
        break;
    }
}

bool MainComponent::perform(const InvocationInfo& info)
{
    switch (info.commandID)
    {
    case CommandIDs::addMidiTrack:
    {
        if (model.addMidiTrack())
        {
            int index = model.getIndexOfLastTrack();
            MidiTrack* newTrack = model.getMidiTrack(index);
            paintArea->addNewTrack(newTrack);
            trackList->updateContent();
            trackList->selectRow(index);
        }
        break;
    }
    case CommandIDs::deleteTrack:
    {
        int indexOfSelectedTrack = trackList->getSelectedRow();
        model.deleteTrack(indexOfSelectedTrack);
        paintArea->deleteTrackComponent(indexOfSelectedTrack);
        trackList->updateContent();
        if (trackList->getSelectedRow() == -1)
        {
            trackList->selectRow(model.getIndexOfLastTrack());
        }
        break;
    }  
    case CommandIDs::deleteAllTracks:
    {
        model.deleteAllTracks();
        paintArea->deleteAllTrackComponents();
        trackList->updateContent();
        break;
    }
    default:
        return false;
    }

    return true;
}
