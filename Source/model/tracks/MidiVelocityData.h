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
    MidiVelocityData();
    ~MidiVelocityData();

    void addPoint(int x, int y);
    void deletePoint(int index);
private:
    juce::OwnedArray<juce::Point<int>> pointVector;
    int maxNumberOfPoints = 20;
};