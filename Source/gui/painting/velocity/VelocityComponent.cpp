/*
  ==============================================================================

    VelocityComponent.cpp
    Created: 14 Jan 2022 10:52:10am
    Author:  Toko

  ==============================================================================
*/

#include <JuceHeader.h>
#include "VelocityComponent.h"

//==============================================================================
VelocityComponent::VelocityComponent(MidiTrack& mt, float scaleFactor)
    : midiTrack (mt)
{
    midiTrack.addChangeListener(this);
    this->scaleFactor = scaleFactor;
}

VelocityComponent::~VelocityComponent()
{
}

void VelocityComponent::mouseDown(const juce::MouseEvent& event)
{
    int index = midiTrack.getMidiVelocityData()
        .getIndexOfPoint((int)(event.getMouseDownX() / this->scaleFactor),
                         (int)(event.getMouseDownY() / this->scaleFactor));

    if (event.mods.isLeftButtonDown())
    {
        if (index == -1)
        {
            midiTrack.getMidiVelocityData().addPoint((int)(event.getMouseDownX() / this->scaleFactor),
                                                     (int)(event.getMouseDownY() / this->scaleFactor));
        }
        if (index != -1)
        {
            midiTrack.getMidiVelocityData().deletePoint(index);
        }
    }
    repaint();
}

void VelocityComponent::paint (juce::Graphics& g)
{
    g.setColour(midiTrack.getColour());
    
    int prevX = -1, prevY = -1;
    
    for each (juce::Point<int>* point in midiTrack.getMidiVelocityData().getPointVector())
    {
        if (prevX >= 0 && prevY >= 0)
        {
            g.drawLine(prevX, prevY, point->getX() * this->scaleFactor, point->getY() * this->scaleFactor, this->scaleFactor);
        }
        g.fillRoundedRectangle(point->getX() * this->scaleFactor - 2, point->getY() * this->scaleFactor - 2, 4, 4, 1.5f);
        prevX = point->getX() * this->scaleFactor;
        prevY = point->getY() * this->scaleFactor;
    }
}

void VelocityComponent::resized()
{
}

void VelocityComponent::changeListenerCallback(juce::ChangeBroadcaster* source)
{
    repaint();
}

void VelocityComponent::setScaleFactor(float newScaleFactor)
{
    this->scaleFactor = newScaleFactor;
    repaint();
}
