/*
  ==============================================================================

    ToolBarComponent.h
    Created: 27 Jan 2022 10:47:39am
    Author:  Toko

  ==============================================================================
*/

#pragma once

#include "JuceHeader.h"
#include "../CommandIDs.h"
#include "../painting/tracks/tools/Kmp2Tool.h"

class ToolBarComponent : public juce::Component,
                         public juce::Button::Listener
{
public:
    ToolBarComponent(juce::ApplicationCommandManager&);
    ~ToolBarComponent();

    void paint(juce::Graphics&) override;
    void resized() override;

    void buttonClicked(juce::Button* button) override;

    int getIndexOfSelectedButton();
private:
    juce::OwnedArray<juce::DrawableButton> buttons;
    juce::ApplicationCommandManager& commandManager;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(ToolBarComponent)
};