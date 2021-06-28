/*
  ==============================================================================

    TrackData.cpp
    Created: 20 Jun 2021 11:21:34pm
    Author:  Toko

  ==============================================================================
*/

#include "TrackData.h"

TrackData::TrackData()
{
    this->audible = true;
    this->visible = true;
    this->trackName = "temp";
    this->trackColour = juce::Colours::red;
}

TrackData::~TrackData()
{
}

void TrackData::addPath(juce::Path* newPath)
{
    this->pathVector.add(newPath);
}

juce::Path& TrackData::getPath(int index)
{
    return *(this->pathVector[index]);
}

juce::OwnedArray<juce::Path>& TrackData::getPathVector()
{
    return this->pathVector;
}

void TrackData::deletePath(int index)
{
    this->pathVector.remove(index);
}

void TrackData::deleteAllPaths()
{
    this->pathVector.clear();
}

void TrackData::movePath(int index, int x, int y)
{
    this->pathVector[index]->applyTransform(juce::AffineTransform::translation(x, y));
}

//==========================================================================
juce::Colour TrackData::getColour()
{
    return this->trackColour;
}

void TrackData::setColour(juce::Colour newColour)
{
    this->trackColour = newColour;
}

juce::String TrackData::getTrackName()
{
    return this->trackName;
}

void TrackData::setTrackName(juce::String newName)
{
    this->trackName = newName;
}

void TrackData::setAudible(bool isAudible)
{
    this->audible = isAudible;
}

bool TrackData::isAudible()
{
    return this->audible;
}

void TrackData::setVisible(bool isVisible)
{
    this->visible = isVisible;
}

bool TrackData::isVisible()
{
    return this->visible;
}

int TrackData::getNumberOfPaths()
{
    return this->pathVector.size();
}
