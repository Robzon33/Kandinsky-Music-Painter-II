/*
  ==============================================================================

    VelocityComponent.h
    Created: 14 Jan 2022 10:52:10am
    Author:  Toko

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "../../../model/tracks/MidiTrack.h"

//==============================================================================
/*
*/
class VelocityComponent  : public juce::Component,
    private juce::ChangeListener
{
public:
    VelocityComponent(MidiTrack&, float scaleFactor);
    ~VelocityComponent() override;

    void mouseDown(const juce::MouseEvent& event) override;

    void paint (juce::Graphics&) override;
    void resized() override;

    void changeListenerCallback(juce::ChangeBroadcaster* source) override;

    void setScaleFactor(float newScaleFactor);
private:
    MidiTrack& midiTrack;
    float scaleFactor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (VelocityComponent)
};
