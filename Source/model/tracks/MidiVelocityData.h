/*
  ==============================================================================

    MidiVelocityData.h
    Created: 21 Jun 2021 6:13:09pm
    Author:  Toko
    
    This class stores and manages the tracks velocity data.

  ==============================================================================
*/

#pragma once
#include "../JuceLibraryCode/JuceHeader.h"

class MidiVelocityData {
public:
    MidiVelocityData(int width);
    ~MidiVelocityData();

    void addPoint(int x, int y);
    void deletePoint(int index);
    void updateWidth(int newWidth);
    juce::OwnedArray<juce::Point<int>>& getPointVector();

    /// <summary>
    /// Returns the index of a point from the pointVector. If
    /// you have not hit a point it returns -1.
    /// </summary>
    /// <param name="x">coordinate</param>
    /// <param name="y">coordinate</param>
    /// <returns></returns>
    int getIndexOfPoint(int x, int y);
private:
    juce::OwnedArray<juce::Point<int>> pointVector;
    int maxNumberOfPoints = 20;
    int width;
    const int defaultVelocityValue = 70;
};