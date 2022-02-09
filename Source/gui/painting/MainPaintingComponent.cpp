/*
  ==============================================================================

    MainPaintingComponent.cpp
    Created: 6 Jul 2021 11:10:50am
    Author:  Toko

  ==============================================================================
*/

#include "MainPaintingComponent.h"

MainPaintingComponent::MainPaintingComponent(MainModel& mm, MidiPlayer& mp, ProjectSettings& ps, juce::ApplicationCommandManager& acm)
    : model (mm), player (mp), settings (ps), commandManager (acm)
{
    drawBeatLines = true;
    scaleFactor = 2.0f;
    backgroundColour = juce::Colours::black.brighter(0.1f);

    paintingHeader.reset(new HeaderComponent("Painting"));
    addAndMakeVisible(paintingHeader.get());

    mainTrackComponent.reset(new MainTrackComponent(model, player, settings, scaleFactor));
    addAndMakeVisible(mainTrackComponent.get());

    velocityHeader.reset(new HeaderComponent("Velocity"));
    addAndMakeVisible(velocityHeader.get());

    mainVelocityComponent.reset(new MainVelocityComponent(model, settings, scaleFactor));
    addAndMakeVisible(mainVelocityComponent.get());

    setSize(settings.getWidth() * scaleFactor, defaultComponentHight * scaleFactor);
    commandManager.registerAllCommandsForTarget(this);
    settings.addChangeListener(this);
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

    paintingHeader->setBounds(b.removeFromTop(40 * scaleFactor));
    mainTrackComponent->setBounds(b.removeFromTop(128 * scaleFactor));
    velocityHeader->setBounds(b.removeFromTop(40 * scaleFactor));
    mainVelocityComponent->setBounds(b.removeFromTop(128 * scaleFactor));
}

void MainPaintingComponent::mouseDown(const juce::MouseEvent& event)
{
}

void MainPaintingComponent::changeListenerCallback(juce::ChangeBroadcaster* source)
{
    if (source == &settings)
    {
        setSize(settings.getWidth() * scaleFactor, defaultComponentHight * scaleFactor);
        mainTrackComponent->setWidth();
        mainVelocityComponent->setWidth();
    }
}

juce::ApplicationCommandTarget* MainPaintingComponent::getNextCommandTarget()
{
    return findFirstTargetParentComponent();
}

void MainPaintingComponent::getAllCommands(juce::Array<juce::CommandID>& c)
{
    juce::Array<juce::CommandID> commands{ CommandIDs::setZoom100, CommandIDs::setZoom200, CommandIDs::setZoom400 };

    c.addArray(commands);
}

void MainPaintingComponent::getCommandInfo(juce::CommandID commandID, juce::ApplicationCommandInfo& result)
{
    switch (commandID)
    {
    case CommandIDs::setZoom100:
        result.setInfo("Zoom 100%", "Updates the painting area scale factor", "Gui", 0);
        result.setTicked(scaleFactor == 1.0f);
        break;
    case CommandIDs::setZoom200:
        result.setInfo("Zoom 200%", "Updates the painting area scale factor", "Gui", 0);
        result.setTicked(scaleFactor == 2.0f);
        break;
    case CommandIDs::setZoom400:
        result.setInfo("Zoom 400%", "Updates the painting area scale factor", "Gui", 0);
        result.setTicked(scaleFactor == 4.0f);
        break;
    default:
        break;
    }
}

bool MainPaintingComponent::perform(const InvocationInfo& info)
{
    switch (info.commandID)
    {
    case CommandIDs::setZoom100:
    {
        this->setScaleFactor(1.0f);
        break;
    }
    case CommandIDs::setZoom200:
    {
        this->setScaleFactor(2.0f);
        break;
    }
    case CommandIDs::setZoom400:
    {
        this->setScaleFactor(4.0f);
        break;
    }
    default:
        return false;
    }

    return true;
}

void MainPaintingComponent::addNewTrack(MidiTrack* newTrack)
{
    mainTrackComponent->addTrackComponent(newTrack);
    mainVelocityComponent->addVelocityComponent(newTrack);
}

void MainPaintingComponent::deleteTrackComponent(int index)
{
    mainTrackComponent->deleteTrackComponent(index);
    mainVelocityComponent->deleteVelocityComponent(index);
}

void MainPaintingComponent::deleteAllTrackComponents()
{
    mainTrackComponent->deleteAllTrackComponents();
    mainVelocityComponent->deleteAllVelocityComponents();
}

void MainPaintingComponent::setSelectedTrack(int index)
{
    mainTrackComponent->setSelectedTrack(index);
    mainVelocityComponent->setSelectedMidiVelocityData(index);
}

void MainPaintingComponent::setSelectedTool(int index)
{
    mainTrackComponent->setSelectedTool(index);
}

void MainPaintingComponent::setScaleFactor(float newScaleFactor)
{
    this->scaleFactor = newScaleFactor;
    setSize(settings.getWidth() * scaleFactor, defaultComponentHight * scaleFactor);
    this->mainTrackComponent->setScaleFactor(scaleFactor);
    this->mainVelocityComponent->setScaleFactor(scaleFactor);
}

void MainPaintingComponent::loadModel()
{
    this->mainTrackComponent->loadModel();
    this->mainVelocityComponent->loadModel();
}
