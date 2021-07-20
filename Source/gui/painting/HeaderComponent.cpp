/*
  ==============================================================================

    HeaderComponent.cpp
    Created: 14 Jul 2021 1:36:30pm
    Author:  Toko

  ==============================================================================
*/

#include "HeaderComponent.h"

HeaderComponent::HeaderComponent(juce::String text)
{
    title = text;
}

HeaderComponent::~HeaderComponent()
{
}

void HeaderComponent::paint(juce::Graphics& g)
{
    g.fillAll(juce::Colours::darkgrey);
    g.setColour(juce::Colours::orange);
    g.drawText("  " + title, getLocalBounds(), juce::Justification::centred, false);
}
