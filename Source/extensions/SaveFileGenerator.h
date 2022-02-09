/*
  ==============================================================================

    SaveFileGenerator.h
    Created: 8 Feb 2022 4:55:37pm
    Author:  Toko

    Static class to save a project as a xml file.

  ==============================================================================
*/

#pragma once

#include "JuceHeader.h"
#include "../model/ProjectSettings.h"
#include "../model/MainModel.h"

class SaveFileGenerator
{
public:
    /// <summary>
    /// Converts a KMP II project to a xml document.
    /// </summary>
    /// <param name="">The current project settings</param>
    /// <param name="">The current main model</param>
    /// <returns>A xml document as a string</returns>
    static juce::String convertProjectToXML(ProjectSettings&, MainModel&);
private:
    SaveFileGenerator();

    /// <summary>
    /// Converts a track to xml elements and adds it to a given xml element.
    /// </summary>
    /// <param name="element">A reference to a xml element</param>
    /// <param name="midiTrack">A midi track that needs to be converted</param>
    static void convertMidiTrackData(juce::XmlElement& element, MidiTrack* midiTrack);
};