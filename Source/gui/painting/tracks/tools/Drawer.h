/*
  ==============================================================================

    Drawer.h
    Created: 11 Jan 2022 10:57:00am
    Author:  Toko

  ==============================================================================
*/

#pragma once

#include "JuceHeader.h"
#include "Kmp2Tool.h"


class Drawer
{
public:
    Drawer();
    ~Drawer();

    /// <summary>
    /// Sets the painting tool for the drawer.
    /// </summary>
    /// <param name="index">The tools index</param>
    void setSelectedTool(int index);

    /// <summary>
    /// Draws a new path depending on the selected painting
    /// tool.
    /// </summary>
    /// <param name="point">The new point that shall be added.</param>
    /// <returns>A path</returns>
    juce::Path draw(juce::Point<float> point);

    /// <summary>
    /// Resets the painting object. This needs to be called
    /// after a path has been painted.
    /// </summary>
    void reset();
private:
    Tool tool;
    std::unique_ptr<Kmp2Tool> kmp2tool;
};