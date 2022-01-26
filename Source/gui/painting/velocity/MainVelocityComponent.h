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

class MainVelocityComponent : public juce::Component
{
public:
    MainVelocityComponent(MainModel&);
    ~MainVelocityComponent();

    void paint(juce::Graphics& g) override;
    void resized() override;

    void setSelectedMidiVelocityData(int index);
    void addVelocityComponent(MidiVelocityData* newVelocityData);
    void deleteVelocityComponent(int index);
    void deleteAllVelocityComponents();
private:
    MainModel& model;

    juce::OwnedArray<VelocityComponent> velocities;
};