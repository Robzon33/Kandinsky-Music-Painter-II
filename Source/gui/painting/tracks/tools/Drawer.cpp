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
    this->setSelectedTool(0);
}

Drawer::~Drawer()
{
}

void Drawer::setSelectedTool(int index)
{
    tool = static_cast<Tool>(index);
    kmp2tool.reset(Kmp2Tool::Create(static_cast<Tool>(index)));
}

juce::Path Drawer::draw(juce::Point<float> point)
{
    kmp2tool.get()->pushPoint(point);
    return kmp2tool.get()->path;
}

void Drawer::reset()
{
    kmp2tool.reset(Kmp2Tool::Create(tool));
}

