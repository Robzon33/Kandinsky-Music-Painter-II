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
#include "../model/ProjectSettings.h"

/* Components */
#include "menu/MenuBarComponent.h"
#include "player/PlayerControlComponent.h"
#include "tracklist/TrackListBoxComponent.h"
#include "painting/MainPaintingComponent.h"
#include "midiMonitor/MidiMonitorComponent.h"
#include "toolbar/ToolBarComponent.h"
#include "customDialogs/ConfigDialog.h"

#include "../extensions/SaveFileGenerator.h"

class KandinskyMusicPainterIIAudioProcessorEditor;

class MainComponent : public juce::Component, 
                      public juce::ApplicationCommandTarget
{
public:
    MainComponent(MainModel&, MidiPlayer&, ProjectSettings&);
    ~MainComponent();

    void paint(juce::Graphics&) override;
    void resized() override;

    juce::ApplicationCommandTarget* getNextCommandTarget() override;
    void getAllCommands(juce::Array<juce::CommandID>& c) override;
    void getCommandInfo(juce::CommandID commandID, juce::ApplicationCommandInfo& result) override;
    bool perform(const InvocationInfo& info) override;
private:
    MainModel& model;
    MidiPlayer& player;
    ProjectSettings& settings;

    juce::ApplicationCommandManager commandManager;

    /* Child components */
    std::unique_ptr<MenuBarComponent> menuBar;
    std::unique_ptr<PlayerControlComponent> playerBar;
    std::unique_ptr<TrackListBoxComponent> trackList;
    std::unique_ptr<MidiMonitorComponent> midiMonitor;
    std::unique_ptr<MainPaintingComponent> mainPainting;
    std::unique_ptr<juce::Viewport> paintViewport;
    std::unique_ptr<ToolBarComponent> toolBar;
    std::unique_ptr<ConfigDialog> configDialog;

    bool showMidiMonitor;
};