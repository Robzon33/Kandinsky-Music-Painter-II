/*
  ==============================================================================

    TrackComponent.cpp
    Created: 14 Jul 2021 12:19:44pm
    Author:  Toko

  ==============================================================================
*/

#include "TrackComponent.h"

TrackComponent::TrackComponent(MidiTrack& mt, Drawer& d, float scaleFactor)
	: track (mt), drawer (d)
{
    track.addChangeListener(this);
    currentPath = nullptr;
    this->scaleFactor = scaleFactor;
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
        for (auto* path : paths)
        {
            auto pathToDraw = *path;
            pathToDraw.applyTransform(juce::AffineTransform::scale(scaleFactor));
            g.strokePath(pathToDraw, juce::PathStrokeType(scaleFactor));
        }

        // creating a preview while drawing
        if (currentPath != nullptr)
        {
            g.setColour(track.getColour().brighter(0.5f));
            currentPath->applyTransform(juce::AffineTransform::scale(scaleFactor));
            g.strokePath(*currentPath, juce::PathStrokeType(scaleFactor));
        }
    }
}

void TrackComponent::mouseDrag(const juce::MouseEvent& event)
{
    currentPath.reset(new juce::Path(drawer.draw((int)(event.position.getX() / scaleFactor), 
                                                 (int)(event.position.getY() / scaleFactor))));
    repaint();
}

void TrackComponent::mouseUp(const juce::MouseEvent& event)
{
	auto path = drawer.draw((int)(event.position.getX() / scaleFactor),
                            (int)(event.position.getY() / scaleFactor));

	track.addPath(path);
    currentPath = nullptr;
	drawer.reset();
	repaint();
}

void TrackComponent::changeListenerCallback(juce::ChangeBroadcaster* source)
{
    repaint();
}

void TrackComponent::setScaleFactor(float newScaleFactor)
{
    this->scaleFactor = newScaleFactor;
    repaint();
}
