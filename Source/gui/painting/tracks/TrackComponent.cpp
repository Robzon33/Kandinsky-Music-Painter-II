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

        // creating a preview while drawing
        if (currentPath != nullptr)
        {
            g.setColour(track.getColour().brighter(0.5f));
            g.strokePath(*currentPath, juce::PathStrokeType(1));
        }
    }
}

void TrackComponent::mouseDrag(const juce::MouseEvent& event)
{
    currentPath.reset(new juce::Path(drawer.draw(event.position)));
    repaint();
}

void TrackComponent::mouseUp(const juce::MouseEvent& event)
{
	auto path = drawer.draw(event.position);

	track.addPath(path);
    currentPath = nullptr;
	drawer.reset();
	repaint();
}

void TrackComponent::changeListenerCallback(juce::ChangeBroadcaster* source)
{
    repaint();
}
