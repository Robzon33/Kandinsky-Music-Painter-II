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

class TrackListBoxComponent :   public juce::ListBox,
                                private juce::ListBoxModel
{
public:
    TrackListBoxComponent(MainModel& mm);
    ~TrackListBoxComponent();

    int getNumRows() override;
    void paintListBoxItem(int rowNumber, juce::Graphics& g, int width, int height,
        bool rowIsSelected) override;
    void listBoxItemClicked(int row, const juce::MouseEvent& event) override;
private:
    MainModel& mainModel;
};
