/*
  ==============================================================================

    Kmp2Line.h
    Created: 31 Jan 2022 7:12:21pm
    Author:  Toko

  ==============================================================================
*/

#pragma once

#include "JuceHeader.h"
#include "Kmp2Tool.h"

class Kmp2Line : public Kmp2Tool
{
public:
    void pushPoint(juce::Point<float> newPoint)
    {
        if (startPoint.getDistanceFrom(newPoint) > 5.0f)
        {
            if (startPoint != juce::Point<float>())
            {
                path.clear();
                path.startNewSubPath(startPoint);
                path.lineTo(newPoint);
            }
            else
            {
                startPoint = newPoint;
            }
        }
    }

    juce::Point<float> startPoint;
};