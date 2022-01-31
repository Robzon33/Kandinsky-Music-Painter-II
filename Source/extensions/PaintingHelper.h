/*
  ==============================================================================

    PaintingHelper.h
    Created: 28 Jan 2022 5:35:48pm
    Author:  Toko

  ==============================================================================
*/

#pragma once

#include "JuceHeader.h"

class PaintingHelper
{
public:
    /// <summary>
    /// Available tools for painting graphical objects.
    /// </summary>
    enum class Tool
    {
        singleLine = 0,
        rectangle,
        ellipse,
        sinus,
        NUMBEROFTOOLS
    };

    /// <summary>
    /// Gets the number of available tools.
    /// </summary>
    /// <returns>The number of tools.</returns>
    static int getNumberOfTools();

    /// <summary>
    /// Gets a specific tool.
    /// </summary>
    /// <param name="index">The index you want to get the tool for.</param>
    /// <returns>A tool</returns>
    static Tool getTool(int index);

    /// <summary>
    /// Gets a prepared Button for each tool.
    /// </summary>
    /// <param name="index">The index for a specific button.</param>
    /// <returns>A button you can use in a component.</returns>
    static juce::DrawableButton* getButton(int index);
private:
    PaintingHelper();
};