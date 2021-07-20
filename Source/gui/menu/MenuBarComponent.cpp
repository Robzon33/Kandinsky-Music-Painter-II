/*
  ==============================================================================

    MenuBarComponent.cpp
    Created: 6 Jul 2021 11:11:07am
    Author:  Toko

  ==============================================================================
*/

#include "MenuBarComponent.h"

MenuBarComponent::MenuBarComponent(MainModel& mm, juce::ApplicationCommandManager& acm)
    : mainModel(mm), commandManager (acm)
{
    menuBar.reset(new juce::MenuBarComponent(this));
    addAndMakeVisible(menuBar.get());
    setApplicationCommandManagerToWatch(&commandManager);
}

MenuBarComponent::~MenuBarComponent()
{
}

void MenuBarComponent::resized()
{
    menuBar->setBounds(getLocalBounds());
}

juce::StringArray MenuBarComponent::getMenuBarNames()
{
    return { "Project", "Painting"};
}

juce::PopupMenu MenuBarComponent::getMenuForIndex(int menuIndex, const juce::String&)
{
    juce::PopupMenu menu;

    if (menuIndex == 0)
    {
        menu.addCommandItem(&commandManager, CommandIDs::newProject);
        //menu.addSeparator();
        menu.addCommandItem(&commandManager, CommandIDs::addMidiTrack);
        menu.addCommandItem(&commandManager, CommandIDs::deleteTrack);  
        menu.addCommandItem(&commandManager, CommandIDs::deleteAllTracks);
    }

    return menu;
}

void MenuBarComponent::menuItemSelected(int menuItemId, int)
{
}
