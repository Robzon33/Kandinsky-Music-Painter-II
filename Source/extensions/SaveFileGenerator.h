/*
  ==============================================================================

    SaveFileGenerator.h
    Created: 8 Feb 2022 4:55:37pm
    Author:  Toko

  ==============================================================================
*/

#pragma once

#include "JuceHeader.h"
#include "../model/ProjectSettings.h"
#include "../model/MainModel.h"

class SaveFileGenerator
{
public:
    static juce::String convertProjectToXML(ProjectSettings&, MainModel&);
private:
    SaveFileGenerator();

    static void saveMidiTrackData(juce::XmlElement& element, MidiTrack* midiTrack);
};