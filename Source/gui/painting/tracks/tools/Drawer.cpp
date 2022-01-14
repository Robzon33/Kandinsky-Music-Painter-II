/*
  ==============================================================================

    Drawer.cpp
    Created: 11 Jan 2022 10:57:00am
    Author:  Toko

  ==============================================================================
*/

#include "Drawer.h"

Drawer::Drawer()
{
}

Drawer::~Drawer()
{
}

void Drawer::setSelectedTool()
{
}

juce::Path* Drawer::createPath(juce::OwnedArray<juce::Point<int>> &points)
{
    juce::Path* newPath = new juce::Path();
    
    /* todo: if selected tool = kmp2Line */
    if (points.size() == 2)
    {
        newPath->startNewSubPath((float)points[0]->getX(), (float)points[0]->getY());
        newPath->lineTo((float)points[1]->getX(), (float)points[1]->getY());
        return newPath;
    }

    return nullptr;
}
