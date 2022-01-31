/*
  ==============================================================================

    Drawer.h
    Created: 11 Jan 2022 10:57:00am
    Author:  Toko

  ==============================================================================
*/

#pragma once

#include "JuceHeader.h"
#include "..\..\..\..\extensions\PaintingHelper.h"
//
//enum Tool
//{
//    singleLine = 0,
//    rectangle = 1
//};

class Drawer
{
public:
    Drawer();
    ~Drawer();

    void setSelectedTool(int index);
    juce::Path* createPath(juce::OwnedArray<juce::Point<int>> &points);
private:
    PaintingHelper::Tool tool;

    juce::OwnedArray<juce::Point<int>> currentPoints;
};