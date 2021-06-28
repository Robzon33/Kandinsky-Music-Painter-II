/*
  ==============================================================================

    ProjectSettings.cpp
    Created: 21 Jun 2021 7:18:02pm
    Author:  Toko

  ==============================================================================
*/

#include "ProjectSettings.h"

ProjectSettings::ProjectSettings()
{
    this->init("unnamed");
}

ProjectSettings::ProjectSettings(juce::String name)
{
    this->init(name);
}

ProjectSettings::~ProjectSettings()
{
}

void ProjectSettings::init(juce::String projectName)
{
    this->name = projectName;
    this->bpm = 60;
    this->numberOfBeats = 20;
}

void ProjectSettings::setName(juce::String newName)
{
    this->name = newName;
}

juce::String ProjectSettings::getName()
{
    return this->name;
}

void ProjectSettings::setBpm(int newBpm)
{
    this->bpm = newBpm;
}

int ProjectSettings::getBpm()
{
    return this->bpm;
}

void ProjectSettings::setNumberOfBeats(int newNumberOfBeats)
{
    this->numberOfBeats = newNumberOfBeats;
}

int ProjectSettings::getNumberOfBeats()
{
    return this->numberOfBeats;
}
