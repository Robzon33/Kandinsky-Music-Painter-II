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
VelocityComponent::VelocityComponent(MidiVelocityData& mvd)
    : midiVelocityData (mvd)
{
}

VelocityComponent::~VelocityComponent()
{
}

void VelocityComponent::mouseDown(const juce::MouseEvent& event)
{
    int index = midiVelocityData.getIndexOfPoint(event.getMouseDownX(),
                                                 event.getMouseDownY());

    if (event.mods.isLeftButtonDown())
    {
        if (index == -1)
        {
            midiVelocityData.addPoint(event.getMouseDownX(),
                                      event.getMouseDownY());
        }
        if (index != -1)
        {
            midiVelocityData.deletePoint(index);
        }
    }
    repaint();
}

void VelocityComponent::paint (juce::Graphics& g)
{
    g.setColour(juce::Colours::cadetblue);
    
    int prevX = -1, prevY = -1;
    
    for each (juce::Point<int>* point in midiVelocityData.getPointVector())
    {
        if (prevX >= 0 && prevY >= 0)
        {
            g.drawLine(prevX, prevY, point->getX(), point->getY(), 1.0f);
        }
        g.fillRoundedRectangle(point->getX() - 2, point->getY() - 2, 4, 4, 1.5f);
        prevX = point->getX();
        prevY = point->getY();
    }
}

void VelocityComponent::resized()
{
}
