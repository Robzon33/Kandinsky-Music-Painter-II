/*
  ==============================================================================

    Kmp2Tool.h
    Created: 31 Jan 2022 7:35:17pm
    Author:  Toko

  ==============================================================================
*/

#pragma once

#include "JuceHeader.h"

enum class Tool
{
    singleLine = 0,
    rectangle,
    ellipse,
    sinus,
    trail,
    NUMBEROFTOOLS
};

class Kmp2Tool
{
public:
    /// <summary>
    /// Virtual destructor.
    /// </summary>
    virtual ~Kmp2Tool() {};

    /// <summary>
    /// Adds a point to a graphical object.
    /// </summary>
    /// <param name="newPoint">The new point</param>
    virtual void pushPoint(juce::Point<float> newPoint) = 0;

    /// <summary>
    /// Creates an instance of a KMP2 Tool.
    /// </summary>
    /// <param name="tool"></param>
    /// <returns>A new instance (f.e. Kmp2Line)</returns>
    static Kmp2Tool* Create(Tool tool);

    /// <summary>
    /// Returns the number of tools in the enum class Tool
    /// </summary>
    /// <returns></returns>
    static int getNumberOfTools();

    /// <summary>
    /// Provides a button for each Tool.
    /// </summary>
    /// <param name="index"></param>
    /// <returns>A prepared button you can use in a component</returns>
    static juce::DrawableButton* getButton(int index);
    
    juce::Path path;
};

