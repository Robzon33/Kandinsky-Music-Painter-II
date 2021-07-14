/*
  ==============================================================================

    MenuBarComponent.cpp
    Created: 6 Jul 2021 11:11:07am
    Author:  Toko

  ==============================================================================
*/

#include "MenuBarComponent.h"

MenuBarComponent::MenuBarComponent(MainModel& mm)
    : mainModel(mm)
{
    menuBar.reset(new juce::MenuBarComponent(this));
    addAndMakeVisible(menuBar.get());
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
        menu.addItem(1001, "New Project", true, false);
        menu.addSeparator();
        menu.addItem(1002, "Add Track", true, false);
    }

    return menu;
}

void MenuBarComponent::menuItemSelected(int menuItemId, int)
{
}
