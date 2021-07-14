/*
  ==============================================================================

    MenuBarComponent.h
    Created: 6 Jul 2021 11:11:07am
    Author:  Toko

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "../../model/MainModel.h"

class MenuBarComponent :   public juce::Component,
                        public juce::MenuBarModel
{
public:
    MenuBarComponent(MainModel& mm);
    ~MenuBarComponent();

    //==============================================================================
    void resized() override;

    //==============================================================================
    juce::StringArray getMenuBarNames() override;
    juce::PopupMenu getMenuForIndex(int menuIndex, const juce::String& /*menuName*/) override;
    void menuItemSelected(int menuItemId, int /*topLevelMenuIndex*/) override;
private:
    std::unique_ptr<juce::MenuBarComponent> menuBar;
    MainModel& mainModel;
};