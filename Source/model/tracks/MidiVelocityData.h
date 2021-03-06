/*
  ==============================================================================

    MidiVelocityData.h
    Created: 21 Jun 2021 6:13:09pm
    Author:  Toko
    
    This class stores and manages the tracks velocity data.

  ==============================================================================
*/

#pragma once

#include "JuceHeader.h"

class MidiVelocityData {
public:
    /// <summary>
    /// Constructor
    /// </summary>
    /// <param name="width"></param>
    MidiVelocityData(int width);

    /// <summary>
    /// Destructor
    /// </summary>
    ~MidiVelocityData();

    /// <summary>
    /// Adds a point to the array.
    /// </summary>
    /// <param name="x">coordinate</param>
    /// <param name="y">coordinate</param>
    void addPoint(int x, int y);
    
    /// <summary>
    /// Deletes a point. It is not possible to delete the first 
    /// or last point.
    /// </summary>
    /// <param name="index">The points index you try to delete</param>
    void deletePoint(int index);

    /// <summary>
    /// Sets a new width. Some points might get deleted if the width
    /// gets less and thus they are out of bounds.
    /// </summary>
    /// <param name="newWidth">The new width</param>
    void updateWidth(int newWidth);

    /// <summary>
    /// Returns a list of all existing points.
    /// </summary>
    /// <returns></returns>
    juce::OwnedArray<juce::Point<int>>& getPointVector();

    /// <summary>
    /// Returns the index of a point from the pointVector. If
    /// you have not hit a point it returns -1.
    /// </summary>
    /// <param name="x">coordinate</param>
    /// <param name="y">coordinate</param>
    /// <returns>Index of a point</returns>
    int getIndexOfPoint(int x, int y);

    /// <summary>
    /// Returns a velocity for a given position.
    /// </summary>
    /// <param name="x">coordinate</param>
    /// <returns>A velocity (0 - 127)</returns>
    int getVelocity(int x);
private:
    juce::OwnedArray<juce::Point<int>> pointVector;
    int maxNumberOfPoints = 20;
    int width;
    const int defaultVelocityValue = 70;
};