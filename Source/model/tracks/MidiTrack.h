/*
  ==============================================================================

    MidiTrack.h
    Created: 21 Jun 2021 5:49:00pm
    Author:  Toko
    
    A MidiTrack contains the graphical objects, track configurations and MIDI
    data.

  ==============================================================================
*/

#pragma once

#include "MidiVelocityData.h"
#include "JuceHeader.h"

class MidiTrack : public juce::ChangeBroadcaster
{
public:
    MidiTrack(int width, juce::Colour, juce::String);
    ~MidiTrack(); 

    //==========================================================================
    void addPath(juce::Path newPath);
    juce::Path& getPath(int index);
    juce::OwnedArray<juce::Path>& getPathVector();
    void deletePath(int index);
    void deleteAllPaths();
    void movePath(int index, int x, int y);

    //==========================================================================
    void setChannel(int newChannel);
    int getChannel();
    void setProgram(int newProgram);
    int getProgram();
    void setColour(juce::Colour newColour);
    juce::Colour getColour();
    juce::String getTrackName();
    void setTrackName(juce::String newName);
    void setAudible(bool isAudible);
    bool isAudible();
    void setVisible(bool isVisible);
    bool isVisible();
    MidiVelocityData& getMidiVelocityData();

    /// <summary>
    /// Returns the number of all paths.
    /// </summary>
    /// <returns></returns>
    int getNumberOfPaths();

    /// <summary>
    /// Calculates all intersections between all existing paths and
    /// a given x coordinate.
    /// </summary>
    /// <param name="x">coordinate</param>
    /// <returns>A list of y values from the calculation</returns>
    juce::Array<float> calculateIntersections(int x);
private:
    int channel, program;
    std::unique_ptr<MidiVelocityData> midiVelocityData;
    juce::OwnedArray<juce::Path> pathVector;
    juce::String trackName;
    juce::Colour trackColour;
    bool visible, audible;
    int width;
};