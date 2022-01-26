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

class MidiTrack : public juce::ChangeBroadcaster
{
public:
    MidiTrack(int width);
    ~MidiTrack(); 

    //==========================================================================
    void addPath(juce::Path* newPath);
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
    int getNumberOfPaths();
    MidiVelocityData& getMidiVelocityData();
private:
    int channel, program;
    std::unique_ptr<MidiVelocityData> midiVelocityData;
    juce::OwnedArray<juce::Path> pathVector;
    juce::String trackName;
    juce::Colour trackColour;
    bool visible, audible;
    int width;
};