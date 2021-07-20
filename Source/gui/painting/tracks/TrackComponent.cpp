/*
  ==============================================================================

    TrackComponent.cpp
    Created: 14 Jul 2021 12:19:44pm
    Author:  Toko

  ==============================================================================
*/

#include "TrackComponent.h"

TrackComponent::TrackComponent(MidiTrack& mt)
	: track (mt)
{
    currentPath = nullptr;
}

TrackComponent::~TrackComponent()
{
}

void TrackComponent::paint(juce::Graphics& g)
{
    if (track.isVisible())
    {
        g.setColour(track.getColour());

        //paint existing paths
        juce::OwnedArray<juce::Path>& paths = track.getPathVector();
        for each (juce::Path* path in paths)
        {
            g.strokePath(*path, juce::PathStrokeType(1));
        }
    }
}

void TrackComponent::mouseDown(const juce::MouseEvent& event)
{
    if (currentPath == nullptr)
    {
        currentPath = new juce::Path();
        currentPath->startNewSubPath(event.getMouseDownX(), event.getMouseDownY());
    }
    else
    {
        currentPath->lineTo(event.getMouseDownX(), event.getMouseDownY());
        track.addPath(currentPath);
        currentPath = nullptr;
        repaint();
    }

}
