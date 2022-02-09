/*
  ==============================================================================

    MainVelocityComponent.h
    Created: 25 Jan 2022 3:46:58pm
    Author:  Toko

  ==============================================================================
*/

#pragma once

#include "JuceHeader.h"
#include "VelocityComponent.h"
#include "../../../model/MainModel.h"
#include "../../../model/ProjectSettings.h"

class MainVelocityComponent : public juce::Component
{
public:
    MainVelocityComponent(MainModel&, ProjectSettings&, float scaleFactor);
    ~MainVelocityComponent();

    void paint(juce::Graphics& g) override;
    void resized() override;

    void setSelectedMidiVelocityData(int index);
    void addVelocityComponent(MidiTrack* newMidiTrack);
    void deleteVelocityComponent(int index);
    void deleteAllVelocityComponents();

    void setWidth();
    void setScaleFactor(float newScaleFactor);
    void loadModel();
private:
    MainModel& model;
    ProjectSettings& settings;

    juce::OwnedArray<VelocityComponent> velocities;
    const int height = 128;
    float scaleFactor;
};