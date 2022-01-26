/*
  ==============================================================================

    MidiVelocityData.cpp
    Created: 21 Jun 2021 6:13:09pm
    Author:  Toko

  ==============================================================================
*/

#include "MidiVelocityData.h"

MidiVelocityData::MidiVelocityData(int width)
{
    this->width = width;
    this->pointVector.insert(0, new juce::Point<int>(0, 
                                                     this->defaultVelocityValue));
    this->pointVector.insert(1, new juce::Point<int>(this->width, 
                                                     this->defaultVelocityValue));
}

MidiVelocityData::~MidiVelocityData()
{
}

void MidiVelocityData::addPoint(int x, int y)
{
    if (this->pointVector.size() < this->maxNumberOfPoints)
    {
        for (int i = 0; i < this->pointVector.size(); ++i)
        {
            if (this->pointVector[i]->getX() > x)
            {
                this->pointVector.insert(i, new juce::Point<int>(x, y));
                break;
            }
        }
    }
}

void MidiVelocityData::deletePoint(int index)
{
    if (index > 0 && index < this->pointVector.size())
    {
        pointVector.remove(index);
    }
}

void MidiVelocityData::updateWidth(int newWidth)
{
    //TODO
}

juce::OwnedArray<juce::Point<int>>& MidiVelocityData::getPointVector()
{
    return pointVector;
}

int MidiVelocityData::getIndexOfPoint(int x, int y)
{
    for (int i = 0; i < this->pointVector.size(); i++)
    {
        if (abs(this->pointVector[i]->getX() - x) < 4 &&
            abs(this->pointVector[i]->getY() - y) < 4)
        {
            return i;
        }
    }
    return -1;
}
