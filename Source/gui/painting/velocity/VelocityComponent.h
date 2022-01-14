/*
  ==============================================================================

    VelocityComponent.h
    Created: 14 Jan 2022 10:52:10am
    Author:  Toko

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class VelocityComponent  : public juce::Component
{
public:
    VelocityComponent();
    ~VelocityComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (VelocityComponent)
};
