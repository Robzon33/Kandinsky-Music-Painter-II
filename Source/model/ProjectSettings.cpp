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
    this->playerSpeed = 50;
    this->width = 1000;
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

void ProjectSettings::setPlayerSpeed(int newPlayerSpeed)
{
    if (0 < newPlayerSpeed <= 100)
    {
        this->playerSpeed = newPlayerSpeed;
        sendChangeMessage();
    }
}

int ProjectSettings::getPlayerSpeed()
{
    return this->playerSpeed;
}

void ProjectSettings::setWidth(int newWidth)
{
    this->width = newWidth;
}

int ProjectSettings::getWidth()
{
    return this->width;
}

int ProjectSettings::getMaxNumberOfTracks()
{
    return this->maxNumberOfTracks;
}
