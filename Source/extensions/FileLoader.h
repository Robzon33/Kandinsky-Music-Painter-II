/*
  ==============================================================================

    FileLoader.h
    Created: 9 Feb 2022 10:31:48am
    Author:  Toko

  ==============================================================================
*/

#pragma once

#include "JuceHeader.h"
#include "../model/MainModel.h"
#include "../model/ProjectSettings.h"

class FileLoader
{
public:
    static void loadSaveFile(std::unique_ptr<juce::XmlElement> element, MainModel&, ProjectSettings&);
private:
    FileLoader();

    static void loadSettings(juce::XmlElement* element, ProjectSettings& settings);
    static void loadModel(juce::XmlElement* element, MainModel& model);
    static void loadTrack(juce::XmlElement* element, MidiTrack& midiTrack);
    static void loadMidiData(juce::XmlElement* element, MidiTrack& midiTrack);
    static void loadMidiVelocityDat(juce::XmlElement* element, MidiVelocityData& midiVelocityData);
};