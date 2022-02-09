/*
  ==============================================================================

    MainPaintingComponent.h
    Created: 6 Jul 2021 11:10:50am
    Author:  Toko

  ==============================================================================
*/

#pragma once

#include "JuceHeader.h"
#include "../../model/MainModel.h"
#include "../../player/MidiPlayer.h"
#include "tracks/MainTrackComponent.h"
#include "velocity/MainVelocityComponent.h"
#include "HeaderComponent.h"
#include "../CommandIDs.h"

class MainPaintingComponent :   public juce::Component,
                                public juce::ChangeListener,
                                public juce::ApplicationCommandTarget
{
public:
    MainPaintingComponent(MainModel&, MidiPlayer&, ProjectSettings&, juce::ApplicationCommandManager&);
    ~MainPaintingComponent();

    void paint(juce::Graphics& g) override;
    void resized() override;
    void mouseDown(const juce::MouseEvent& event) override;
    void changeListenerCallback(juce::ChangeBroadcaster*) override;

    juce::ApplicationCommandTarget* getNextCommandTarget() override;
    void getAllCommands(juce::Array<juce::CommandID>& c) override;
    void getCommandInfo(juce::CommandID commandID, juce::ApplicationCommandInfo& result) override;
    bool perform(const InvocationInfo& info) override;

    void addNewTrack(MidiTrack* newTrack);
    void deleteTrackComponent(int index);
    void deleteAllTrackComponents();
    void setSelectedTrack(int index);
    void setSelectedTool(int index);
    void setScaleFactor(float newScaleFactor);
    void loadModel();
private:
    MainModel& model;
    MidiPlayer& player;
    ProjectSettings& settings;
    juce::ApplicationCommandManager& commandManager;
    
    std::unique_ptr<HeaderComponent> paintingHeader;
    std::unique_ptr<MainTrackComponent> mainTrackComponent;
    std::unique_ptr<HeaderComponent> velocityHeader;
    std::unique_ptr<MainVelocityComponent> mainVelocityComponent;

    bool drawBeatLines;
    juce::Colour backgroundColour;
    float scaleFactor;
    const int defaultComponentHight = 336;
};