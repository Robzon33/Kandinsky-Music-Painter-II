/*
  ==============================================================================

    Kmp2Sinus.h
    Created: 31 Jan 2022 9:34:09pm
    Author:  Toko

  ==============================================================================
*/

#pragma once

#include "JuceHeader.h"
#include "Kmp2Tool.h"

class Kmp2Sinus : public Kmp2Tool
{
    void pushPoint(juce::Point<float> newPoint)
    {
        if (startPoint.getDistanceFrom(newPoint) > 5.0f)
        {
            if (startPoint != juce::Point<float>())
            {
                juce::Rectangle<float> rectangle(startPoint, newPoint);

                juce::Point<float> controlPoint1(rectangle.getX(), rectangle.getY() + rectangle.getHeight() / 2);
                juce::Point<float> controlPoint2(rectangle.getX() + rectangle.getWidth() / 4, rectangle.getY());
                juce::Point<float> controlPoint3(rectangle.getX() + rectangle.getWidth() / 2, rectangle.getY() + rectangle.getHeight() / 2);
                juce::Point<float> controlPoint4(rectangle.getX() + rectangle.getWidth() / 4 * 3, rectangle.getY() + rectangle.getHeight());
                juce::Point<float> controlPoint5(rectangle.getX() + rectangle.getWidth(), rectangle.getY() + rectangle.getHeight() / 2);

                path.clear();
                path.startNewSubPath(controlPoint1);
                path.quadraticTo(controlPoint2, controlPoint3);
                path.quadraticTo(controlPoint4, controlPoint5);
            }
            else
            {
                startPoint = newPoint;
            }
        }
    }

    juce::Point<float> startPoint;
};