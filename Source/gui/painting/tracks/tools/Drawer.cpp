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
    tool = Tool::rectangle;
}

Drawer::~Drawer()
{
}

void Drawer::setSelectedTool(Tool newSelectedTool)
{
    tool = newSelectedTool;
}

juce::Path* Drawer::createPath(juce::OwnedArray<juce::Point<int>> &points)
{
    juce::Path* newPath = new juce::Path();
    
    if (tool == Tool::singleLine)
    {
        if (points.size() == 2)
        {
            newPath->startNewSubPath((float)points[0]->getX(), (float)points[0]->getY());
            newPath->lineTo((float)points[1]->getX(), (float)points[1]->getY());
            return newPath;
        }
    }
    if (tool == Tool::rectangle)
    {
        if (points.size() == 2)
        {
            float x = juce::jmin<float>((float)points[0]->getX(), (float)points[1]->getX());
            float y = juce::jmin<float>((float)points[0]->getY(), (float)points[1]->getY());
            float width = std::abs((float)points[0]->getX() - (float)points[1]->getX());
            float height = std::abs((float)points[0]->getY() - (float)points[1]->getY());
            newPath->addRectangle(x, y, width, height);
            return newPath;
        }
    }

    return nullptr;
}
