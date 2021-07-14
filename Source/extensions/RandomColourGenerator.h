/*
  ==============================================================================

    RandomColourGenerator.h
    Created: 5 Jul 2021 5:55:16pm
    Author:  Toko

	Static class to provide a random colour.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class RandomColourGenerator
{
public:
	static juce::Colour getRandomColour();
private:
	// Disallow creating an instance of this object
	RandomColourGenerator() {};
};