/*
  ==============================================================================

    TrackData.h
    Created: 20 Jun 2021 11:21:34pm
    Author:  Toko

	Base class for all tracks. It contains basic information about a track and
	graphical objects. 
	You're not supposed to create an instance of this class.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

class TrackData
{
public:
    TrackData();
    ~TrackData();

    //==========================================================================
    void addPath(juce::Path* newPath);
    juce::Path& getPath(int index);
    juce::OwnedArray<juce::Path>& getPathVector();
    void deletePath(int index);
    void deleteAllPaths();
    void movePath(int index, int x, int y);

	//==========================================================================
	juce::Colour getColour();
	void setColour(juce::Colour newColour);
	juce::String getTrackName();
	void setTrackName(juce::String newName);
	void setAudible(bool isAudible);
	bool isAudible();
	void setVisible(bool isVisible);
	bool isVisible();
	int getNumberOfPaths();
protected:
	juce::OwnedArray<juce::Path> pathVector;
	juce::String trackName;
	juce::Colour trackColour;
	bool visible, audible;
};