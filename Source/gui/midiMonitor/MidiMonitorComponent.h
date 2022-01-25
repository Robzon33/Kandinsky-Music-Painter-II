/*
  ==============================================================================

    MidiMonitorComponent.h
    Created: 24 Jan 2022 4:08:25pm
    Author:  Toko

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "../../player/MidiPlayer.h"

class MidiMonitorComponent : public juce::Component, 
                             public juce::ChangeListener,
                             private juce::Timer
{
public:
    MidiMonitorComponent(MidiPlayer& mp);
    ~MidiMonitorComponent();

    void paint(juce::Graphics&) override;
    void resized() override;

    void timerCallback() override;
    void changeListenerCallback(juce::ChangeBroadcaster* source) override;
private:
    MidiPlayer& midiPlayer;

    juce::TextEditor midiMonitor;
    juce::Label outgoingMidiLabel;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MidiMonitorComponent)
};