/*
  ==============================================================================

    Drawer.h
    Created: 11 Jan 2022 10:57:00am
    Author:  Toko

  ==============================================================================
*/

#pragma once

#include "JuceHeader.h"

class Drawer
{
public:
    Drawer();
    ~Drawer();

    void setSelectedTool(/*selected Tool*/);
    juce::Path* createPath(juce::OwnedArray<juce::Point<int>> &points);
private:
    // selected Tool. In Abhängigkeit vom selected Tool wird das Objekt gezeichnet.

    juce::OwnedArray<juce::Point<int>> currentPoints;
};