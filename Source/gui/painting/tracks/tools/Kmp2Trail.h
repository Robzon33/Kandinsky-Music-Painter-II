/*
  ==============================================================================

    Kmp2Trail.h
    Created: 31 Jan 2022 3:10:23pm
    Author:  Toko

  ==============================================================================
*/

#pragma once

#include "JuceHeader.h"
#include "Kmp2Tool.h"

class Kmp2Trail : public Kmp2Tool
{
    void pushPoint(juce::Point<float> newPoint)
    {
        if (lastPoint.getDistanceFrom(newPoint) > 5.0f)
        {
            if (lastPoint != juce::Point<float>())
            {
                juce::Path newSegment;
                newSegment.startNewSubPath(lastPoint);
                newSegment.lineTo(newPoint);
                path.addPath(newSegment);
            }

            lastPoint = newPoint;
        }
    }

    juce::Point<float> lastPoint;
};