/*
  ==============================================================================

    SaveFileGenerator.cpp
    Created: 8 Feb 2022 4:55:37pm
    Author:  Toko

  ==============================================================================
*/

#include "SaveFileGenerator.h"

juce::String SaveFileGenerator::convertProjectToXML(ProjectSettings& projectSettings, MainModel& mainModel)
{
    juce::String xmlDoc;
    juce::XmlElement project("KMP2PROJECT");

    // save settings
    juce::XmlElement* settings = new juce::XmlElement("SETTINGS");
    settings->setAttribute("projectname", projectSettings.getName());
    settings->setAttribute("trackwidth", projectSettings.getWidth());
    project.addChildElement(settings);

    // save midi tracks
    juce::XmlElement* midiTrackElements = new juce::XmlElement("TRACKS");
    for each (MidiTrack* midiTrack in mainModel.getMidiTracks())
    {
        juce::XmlElement* midiTrackElement = new juce::XmlElement("TRACK");
        saveMidiTrackData(*midiTrackElement, midiTrack);
        midiTrackElements->addChildElement(midiTrackElement);
    }
    project.addChildElement(midiTrackElements);

    xmlDoc.append(project.createDocument(juce::String()), 200000);
    return xmlDoc;
}

void SaveFileGenerator::saveMidiTrackData(juce::XmlElement& element, MidiTrack* midiTrack)
{
    //store all attributes
    element.setAttribute("name", midiTrack->getTrackName());
    element.setAttribute("colour", midiTrack->getColour().toString());
    element.setAttribute("audible", midiTrack->isAudible());
    element.setAttribute("visible", midiTrack->isVisible());

    //store all paths
    juce::XmlElement* pathObjects = new juce::XmlElement("PATHS");
    for each (juce::Path* path in midiTrack->getPathVector())
    {
        juce::XmlElement* pathToStore = new juce::XmlElement("Path");
        juce::String pathString = path->toString();
        pathToStore->setAttribute("data", pathString);
        pathObjects->addChildElement(pathToStore);
    }
    element.addChildElement(pathObjects);

    //store midi data
    juce::XmlElement* midiData = new juce::XmlElement("MIDIDATA");
    midiData->setAttribute("program", midiTrack->getProgram());
    midiData->setAttribute("channel", midiTrack->getChannel());
    element.addChildElement(midiData);

    juce::XmlElement* velocity = new juce::XmlElement("VELOCITY");
    //iterate through the list of points except from first and last one
    for (int i = 1; i < midiTrack->getMidiVelocityData().getPointVector().size() - 1; ++i)
    {
        juce::XmlElement* point = new juce::XmlElement("Point");
        point->setAttribute("x", midiTrack->getMidiVelocityData().getPointVector()[i]->getX());
        point->setAttribute("y", midiTrack->getMidiVelocityData().getPointVector()[i]->getY());
        velocity->addChildElement(point);
    }
    element.addChildElement(velocity);
}
