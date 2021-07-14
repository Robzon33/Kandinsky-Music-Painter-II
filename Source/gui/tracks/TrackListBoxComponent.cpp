/*
  ==============================================================================

    TrackListBoxComponent.cpp
    Created: 6 Jul 2021 11:10:14am
    Author:  Toko

  ==============================================================================
*/

#include "TrackListBoxComponent.h"

TrackListBoxComponent::TrackListBoxComponent(MainModel& mm)
    : mainModel(mm), ListBox("Track List Box", this)
{
    setOutlineThickness(0);
    setMultipleSelectionEnabled(false);
    setClickingTogglesRowSelection(true);
    setColour(backgroundColourId, juce::Colours::darkgrey.darker());
    setRowHeight(40);
}

TrackListBoxComponent::~TrackListBoxComponent()
{
}

int TrackListBoxComponent::getNumRows()
{
    //return mainModel.getNumberOfTracks();
    return 10;
}

void TrackListBoxComponent::paintListBoxItem(int rowNumber, juce::Graphics& g, int width, int height, bool rowIsSelected)
{
    if (rowIsSelected)
        g.fillAll(juce::Colour(128, 116, 105));
	else if (rowNumber % 2)
		g.fillAll(juce::Colours::darkgrey.darker(0.2f));

	g.setColour(juce::Colours::lightblue);
	g.setFont(height * 0.7f);

	g.drawText("Dummy Text", 5, 0, width, height,
		juce::Justification::centredLeft, true);
}

void TrackListBoxComponent::listBoxItemClicked(int row, const juce::MouseEvent& event)
{
    if (event.mods.isLeftButtonDown())
    {
        // select track
    }
    if (event.mods.isRightButtonDown())
    {
        juce::PopupMenu m;
        m.addItem(100, "Edit");
        m.addSeparator();
        m.addItem(105, "Delete track");

        const int result = m.show();
        if (result == 100) { /*parent.showTrackConfigDialog(row, getRowPosition(row, true));*/ }
        if (result == 105) { /*parent.deleteTrack(row);*/ }
    }
}
