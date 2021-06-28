/*
  ==============================================================================

    MainComponent.h
    Created: 21 Jun 2021 9:20:53pm
    Author:  Toko

  ==============================================================================
*/

#pragma once

#include "JuceHeader.h"
#include "../PluginEditor.h"
#include "../model/MainModel.h"
#include "../player/MidiPlayer.h"

class KandinskyMusicPainterIIAudioProcessorEditor;

class MainComponent : public juce::Component
{
public:
    MainComponent(MainModel&, MidiPlayer&);
    ~MainComponent();

    void paint(juce::Graphics&) override;
    void resized() override;

    void mouseDown(const juce::MouseEvent& event) override;
private:
    MainModel& mainModel;
    MidiPlayer& player;
};