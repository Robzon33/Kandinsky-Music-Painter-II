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

class MidiMonitorListBoxModel : public juce::ListBoxModel
{
public:
    MidiMonitorListBoxModel(juce::OwnedArray<juce::MidiMessage>& list)
        : midiMessageList(list)
    {
    }

    int getNumRows() override { return midiMessageList.size(); }

    void paintListBoxItem(int row, juce::Graphics& g, int width, int height, bool rowIsSelected) override
    {
        if (juce::isPositiveAndBelow(row, midiMessageList.size()))
        {
            g.setColour(juce::Colours::red);

            const juce::MidiMessage& message = *(midiMessageList[row]);
            if (message.isNoteOff()) { g.setColour(juce::Colours::blue.withAlpha(0.1f)); }
            if (message.isNoteOn()) { g.setColour(juce::Colours::blue.withAlpha(0.2f)); }
            if (message.isProgramChange()) { g.setColour(juce::Colours::blue.withAlpha(0.3f)); }

            g.fillAll();

            double time = message.getTimeStamp();
            const int minutes = ((int)(time / 60.0)) % 60;
            const int seconds = ((int)time) % 60;
            const int millis = ((int)(time * 1000.0)) % 1000;

            g.setColour(juce::Colours::black);
            g.drawText(juce::String::formatted("%02d:%02d.%03d",
                minutes,
                seconds,
                millis)
                + "  -  " + message.getDescription(),
                juce::Rectangle<int>(width, height).reduced(4, 0),
                juce::Justification::centredLeft, true);
        }
    }

private:
    juce::OwnedArray<juce::MidiMessage>& midiMessageList;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MidiMonitorListBoxModel)
};

class MidiMonitorComponent : public juce::Component, 
                             public juce::ChangeListener,
                             private juce::Timer
{
public:
    MidiMonitorComponent(MidiPlayer&);
    ~MidiMonitorComponent();

    void paint(juce::Graphics&) override;
    void resized() override;

    void timerCallback() override;
    void changeListenerCallback(juce::ChangeBroadcaster* source) override;
private:
    MidiPlayer& midiPlayer;

    //juce::TextEditor midiMonitor;
    juce::Label outgoingMidiLabel;

    juce::ListBox messageListBox;
    juce::OwnedArray<juce::MidiMessage>& midiMessageList;
    MidiMonitorListBoxModel midiLogListBoxModel;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MidiMonitorComponent)
};