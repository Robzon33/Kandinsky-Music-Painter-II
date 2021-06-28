/*
  ==============================================================================

    MidiVelocityData.cpp
    Created: 21 Jun 2021 6:13:09pm
    Author:  Toko

  ==============================================================================
*/

#include "MidiVelocityData.h"

MidiVelocityData::MidiVelocityData()
{
}

MidiVelocityData::~MidiVelocityData()
{
}

void MidiVelocityData::addPoint(int x, int y)
{
    if (this->maxNumberOfPoints < this->pointVector.size())
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
