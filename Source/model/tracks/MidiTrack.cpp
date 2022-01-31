/*
  ==============================================================================

    MidiTrack.cpp
    Created: 21 Jun 2021 5:49:00pm
    Author:  Toko

  ==============================================================================
*/

#include "MidiTrack.h"

MidiTrack::MidiTrack(int width, juce::Colour colour, juce::String name)
{
    this->channel = 1;
    this->program = 0;
    this->width = width;
    audible = true;
    visible = true;
    trackName = name;
    trackColour = colour;
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

juce::Array<float> MidiTrack::calculateIntersections(int x)
{
    juce::Array<float> yValues;

    for each (juce::Path* path in this->pathVector)
    {
        int xBoundLeft = path->getBounds().getX();
        int xBoundRight = path->getBounds().getX() + path->getBounds().getWidth();

        if (x >= xBoundLeft && x <= xBoundRight)
        {
            const float tolerance = 1.0f;
            juce::Line<float> line((float)x, 0, (float)x, 128);

            juce::PathFlatteningIterator iterator(*path, juce::AffineTransform(), tolerance);
            juce::Point<float> intersection;

            while (iterator.next())
            {
                if (line.intersects(juce::Line<float>(iterator.x1,
                    iterator.y1,
                    iterator.x2,
                    iterator.y2),
                    intersection))
                {
                    yValues.add(intersection.getY());
                }

                // the intersects method does not identify intersections between two vertical lines. So it is 
                // necessary to take care of it manually.
                if (iterator.x1 == iterator.x2 && (float)x == iterator.x1)
                {
                    int min = juce::jmin<int>(iterator.y1, iterator.y2);
                    int max = juce::jmax<int>(iterator.y1, iterator.y2);

                    for (int i = min; i < max; i++)
                    {
                        yValues.add(i);
                    }
                }
            }
        }
    }

    return yValues;
}

