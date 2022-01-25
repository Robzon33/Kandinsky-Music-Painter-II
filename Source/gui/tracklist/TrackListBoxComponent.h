/*
  ==============================================================================

    TrackListBoxComponent.h
    Created: 6 Jul 2021 11:10:14am
    Author:  Toko

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "../../model/MainModel.h"
#include "../CommandIDs.h"
#include "config/TrackConfigComponent.h"

class TrackListBoxComponent :   public juce::ListBox,
                                private juce::ListBoxModel,
                                private juce::ChangeListener
{
public:
    TrackListBoxComponent(MainModel&, juce::ApplicationCommandManager&);
    ~TrackListBoxComponent();

    int getNumRows() override;
    void paintListBoxItem(int rowNumber, juce::Graphics& g, int width, int height,
        bool rowIsSelected) override;
    void listBoxItemClicked(int row, const juce::MouseEvent& event) override;

    void changeListenerCallback(juce::ChangeBroadcaster* source) override;

    void showTrackConfigDialog(int row);
private:
    MainModel& mainModel;
    juce::ApplicationCommandManager& commandManager;
};
