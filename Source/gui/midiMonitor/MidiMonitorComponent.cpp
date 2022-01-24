/*
  ==============================================================================

    MidiMonitorComponent.cpp
    Created: 24 Jan 2022 4:08:25pm
    Author:  Toko

  ==============================================================================
*/

#include "MidiMonitorComponent.h"

MidiMonitorComponent::MidiMonitorComponent(MidiPlayer& mp)
    : midiPlayer (mp)
{
    mp.addChangeListener(this);

    outgoingMidiLabel.setText("Midi Messages", juce::NotificationType::dontSendNotification);
    outgoingMidiLabel.setFont(juce::Font(15.00f, juce::Font::plain));
    outgoingMidiLabel.setJustificationType(juce::Justification::centredLeft);
    outgoingMidiLabel.setEditable(false, false, false);
    outgoingMidiLabel.setColour(juce::TextEditor::textColourId, juce::Colours::black);
    outgoingMidiLabel.setColour(juce::TextEditor::backgroundColourId, juce::Colour(0x00000000));
    addAndMakeVisible(outgoingMidiLabel);

    midiMonitor.setMultiLine(true);
    midiMonitor.setReturnKeyStartsNewLine(false);
    midiMonitor.setReadOnly(true);
    midiMonitor.setScrollbarsShown(true);
    midiMonitor.setCaretVisible(false);
    midiMonitor.setPopupMenuEnabled(false);
    midiMonitor.setText({});
    addAndMakeVisible(midiMonitor);
}

MidiMonitorComponent::~MidiMonitorComponent()
{
}

void MidiMonitorComponent::paint(juce::Graphics&)
{
}

void MidiMonitorComponent::resized()
{
    auto area = this->getLocalBounds();

    outgoingMidiLabel.setBounds(area.removeFromTop(15));
    midiMonitor.setBounds(area);
}

void MidiMonitorComponent::changeListenerCallback(juce::ChangeBroadcaster* source)
{
    if (midiPlayer.getState() != MidiPlayer::State::ST_STOPPED)
    {
        juce::String messageText;

        for (auto& m : midiPlayer.getMidiMessageList())
        {
            messageText << m->getDescription() << "\n";
        }

        midiMonitor.insertTextAtCaret(messageText);
    }
    else
    {
        midiMonitor.clear();
    }
}
