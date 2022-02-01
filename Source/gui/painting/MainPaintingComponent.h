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

class MainPaintingComponent :   public juce::Component
{
public:
    MainPaintingComponent(MainModel&, MidiPlayer&, ProjectSettings&);
    ~MainPaintingComponent();

    void paint(juce::Graphics& g) override;
    void resized() override;

    void mouseDown(const juce::MouseEvent& event) override;

    void addNewTrack(MidiTrack* newTrack);
    void deleteTrackComponent(int index);
    void deleteAllTrackComponents();
    void setSelectedTrack(int index);
    void setSelectedTool(int index);
    int getComponentHeight();
private:
    MainModel& model;
    MidiPlayer& player;
    ProjectSettings& settings;
    
    std::unique_ptr<HeaderComponent> paintingHeader;
    std::unique_ptr<MainTrackComponent> trackComponent;
    std::unique_ptr<HeaderComponent> velocityHeader;
    std::unique_ptr<MainVelocityComponent> velocityComponent;

    bool drawBeatLines;
    juce::Colour backgroundColour;
    float scaleFactor;
    const int defaultComponentHight = 338;
};