/*
  ==============================================================================

    HeaderComponent.h
    Created: 14 Jul 2021 1:36:30pm
    Author:  Toko

  ==============================================================================
*/

#pragma once

#include "JuceHeader.h"

class HeaderComponent : public juce::Component
{
public:
    HeaderComponent(juce::String text);
    ~HeaderComponent();

    void paint(juce::Graphics& g) override;
private:
    juce::String title;
};