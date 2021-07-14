/*
  ==============================================================================

    RandomColourGenerator.cpp
    Created: 5 Jul 2021 5:55:16pm
    Author:  Toko

  ==============================================================================
*/

#include "RandomColourGenerator.h"

juce::Colour RandomColourGenerator::getRandomColour()
{
	juce::Random r;
	return juce::Colour(r.nextInt(255), r.nextInt(255), r.nextInt(255));
}
