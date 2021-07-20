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
#include "HeaderComponent.h"
#include "../CommandIDs.h"

class MainPaintingComponent :   public juce::Component
{
public:
    MainPaintingComponent(MainModel&, MidiPlayer&);
    ~MainPaintingComponent();

    void paint(juce::Graphics& g) override;
    void resized() override;

    void mouseDown(const juce::MouseEvent& event) override;

    void addNewTrack(MidiTrack* newTrack);
    void deleteTrackComponent(int index);
    void deleteAllTrackComponents();
private:
    MainModel& model;
    MidiPlayer& player;
    
    std::unique_ptr<HeaderComponent> paintingHeader;
    std::unique_ptr<MainTrackComponent> trackComponent;
    std::unique_ptr<HeaderComponent> velocityHeader;

    bool drawBeatLines;
    bool showToolComponent;
    juce::Colour backgroundColour;
    float scaleFactor;
};