/*
  ==============================================================================

    MidiTrack.cpp
    Created: 21 Jun 2021 5:49:00pm
    Author:  Toko

  ==============================================================================
*/

#include "MidiTrack.h"

MidiTrack::MidiTrack()
{
    this->channel = 1;
    this->program = 0;
    audible = true;
    visible = true;
    trackName = "Track";
    trackColour = juce::Colours::red;
}

MidiTrack::~MidiTrack()
{
}

void MidiTrack::addPath(juce::Path* newPath)
{
    this->pathVector.add(newPath);
}

juce::Path& MidiTrack::getPath(int index)
{
    return *(this->pathVector[index]);
}

juce::OwnedArray<juce::Path>& MidiTrack::getPathVector()
{
    return this->pathVector;
}

void MidiTrack::deletePath(int index)
{
    this->pathVector.remove(index);
}

void MidiTrack::deleteAllPaths()
{
    this->pathVector.clear();
}

void MidiTrack::movePath(int index, int x, int y)
{
    this->pathVector[index]->applyTransform(juce::AffineTransform::translation(x, y));
}

//==========================================================================

void MidiTrack::setChannel(int newChannel)
{
    this->channel = newChannel;
}

int MidiTrack::getChannel()
{
    return this->channel;
}

void MidiTrack::setProgram(int newProgram)
{
    this->program = newProgram;
    sendChangeMessage();
}

int MidiTrack::getProgram()
{
    return this->program;
}

juce::Colour MidiTrack::getColour()
{
    return this->trackColour;
}

void MidiTrack::setColour(juce::Colour newColour)
{
    this->trackColour = newColour;
    this->sendChangeMessage();
}

juce::String MidiTrack::getTrackName()
{
    return this->trackName;
}

void MidiTrack::setTrackName(juce::String newName)
{
    this->trackName = newName;
}

void MidiTrack::setAudible(bool isAudible)
{
    this->audible = isAudible;
}

bool MidiTrack::isAudible()
{
    return this->audible;
}

void MidiTrack::setVisible(bool isVisible)
{
    this->visible = isVisible;
}

bool MidiTrack::isVisible()
{
    return this->visible;
}

int MidiTrack::getNumberOfPaths()
{
    return this->pathVector.size();
}

