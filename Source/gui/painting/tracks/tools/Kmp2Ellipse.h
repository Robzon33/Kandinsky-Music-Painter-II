/*
  ==============================================================================

    Kmp2Ellipse.h
    Created: 31 Jan 2022 9:33:56pm
    Author:  Toko

  ==============================================================================
*/

#pragma once

#include "JuceHeader.h"
#include "Kmp2Tool.h"

class Kmp2Ellipse : public Kmp2Tool
{
    void pushPoint(juce::Point<float> newPoint)
    {
        if (startPoint.getDistanceFrom(newPoint) > 5.0f)
        {
            if (startPoint != juce::Point<float>())
            {
                float x = juce::jmin<float>(startPoint.getX(), newPoint.getX());
                float y = juce::jmin<float>(startPoint.getY(), newPoint.getY());
                float width = std::abs(startPoint.getX() - newPoint.getX());
                float height = std::abs(startPoint.getY() - newPoint.getY());

                path.clear();
                path.addEllipse(x, y, width, height);
            }
            else
            {
                startPoint = newPoint;
            }
        }
    }

    juce::Point<float> startPoint;
};