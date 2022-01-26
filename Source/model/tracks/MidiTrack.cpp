/*
  ==============================================================================

    MidiTrack.cpp
    Created: 21 Jun 2021 5:49:00pm
    Author:  Toko

  ==============================================================================
*/

#include "MidiTrack.h"

MidiTrack::MidiTrack(int width)
{
    this->channel = 1;
    this->program = 0;
    this->width = width;
    audible = true;
    visible = true;
    trackName = "Track";
    trackColour = juce::Colours::red;
    midiVelocityData.reset(new MidiVelocityData(this->width));
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
    if (1 <= newChannel <= 16)
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

MidiVelocityData& MidiTrack::getMidiVelocityData()
{
    return *midiVelocityData;
}

