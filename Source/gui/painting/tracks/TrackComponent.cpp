/*
  ==============================================================================

    TrackComponent.cpp
    Created: 14 Jul 2021 12:19:44pm
    Author:  Toko

  ==============================================================================
*/

#include "TrackComponent.h"

TrackComponent::TrackComponent(MidiTrack& mt, Drawer& d)
	: track (mt), drawer (d)
{
    track.addChangeListener(this);
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

        if (currentPath != nullptr)
        {
            g.setColour(track.getColour().brighter(0.5f));
            g.strokePath(*currentPath, juce::PathStrokeType(1));
        }
    }
}

void TrackComponent::mouseDown(const juce::MouseEvent& event)
{
    if (currentPoints.size() == 0)
    {
        currentPoints.add(new juce::Point<int>(event.getMouseDownX(), event.getMouseDownY()));
    }
    else if (currentPoints.size() > 0)
    {
        currentPoints.add(new juce::Point<int>(event.getMouseDownX(), event.getMouseDownY()));
        auto* path = drawer.createPath(currentPoints);
        if (path != nullptr)
        {
            track.addPath(path);
            currentPoints.clear(true);
            currentPath = nullptr;
            repaint();
        }
    }
}

void TrackComponent::mouseMove(const juce::MouseEvent& event)
{
    if (currentPoints.size() > 0)
    {
        currentPoints.add(new juce::Point<int>(event.getMouseDownX(), event.getMouseDownY()));
        currentPath.reset(drawer.createPath(currentPoints));
        repaint();
        currentPoints.removeLast(1, true);
    }
}

void TrackComponent::mouseDrag(const juce::MouseEvent& event)
{
    if (currentPoints.size() > 0)
    {
        currentPoints.add(new juce::Point<int>(event.getMouseDownX(), event.getMouseDownY()));
        currentPath.reset(drawer.createPath(currentPoints));
        repaint();
        currentPoints.removeLast(1, true);
    }
}

void TrackComponent::changeListenerCallback(juce::ChangeBroadcaster* source)
{
    repaint();
}
