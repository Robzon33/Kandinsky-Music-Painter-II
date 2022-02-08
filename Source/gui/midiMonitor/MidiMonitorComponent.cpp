/*
  ==============================================================================

    MidiMonitorComponent.cpp
    Created: 24 Jan 2022 4:08:25pm
    Author:  Toko

  ==============================================================================
*/

#include "MidiMonitorComponent.h"

MidiMonitorComponent::MidiMonitorComponent(MidiPlayer& mp)
    :   midiPlayer (mp), 
        midiMessageList (mp.getMidiMessageList()),
        midiLogListBoxModel (midiMessageList)
{
    mp.addChangeListener(this);

    outgoingMidiLabel.setText("Midi Messages", juce::NotificationType::dontSendNotification);
    outgoingMidiLabel.setFont(juce::Font(15.00f, juce::Font::plain));
    outgoingMidiLabel.setJustificationType(juce::Justification::centredLeft);
    outgoingMidiLabel.setEditable(false, false, false);
    outgoingMidiLabel.setColour(juce::TextEditor::textColourId, juce::Colours::black);
    outgoingMidiLabel.setColour(juce::TextEditor::backgroundColourId, juce::Colour(0x00000000));
    addAndMakeVisible(outgoingMidiLabel);

    /*midiMonitor.setMultiLine(true);
    midiMonitor.setReturnKeyStartsNewLine(false);
    midiMonitor.setReadOnly(true);
    midiMonitor.setScrollbarsShown(true);
    midiMonitor.setCaretVisible(false);
    midiMonitor.setPopupMenuEnabled(false);
    midiMonitor.setText({});
    addAndMakeVisible(midiMonitor);*/
    addAndMakeVisible(messageListBox);
    messageListBox.setModel(&midiLogListBoxModel);
    messageListBox.setColour(juce::ListBox::backgroundColourId, juce::Colour(0x32ffffff));
    messageListBox.setColour(juce::ListBox::outlineColourId, juce::Colours::black);
    messageListBox.setRowSelectedOnMouseDown(false);

    this->startTimer(1000);
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
    messageListBox.setBounds(area);
}

void MidiMonitorComponent::timerCallback()
{
    messageListBox.updateContent();
    messageListBox.scrollToEnsureRowIsOnscreen(midiMessageList.size() - 1);
    messageListBox.repaint();
}

void MidiMonitorComponent::changeListenerCallback(juce::ChangeBroadcaster* source)
{
    if (midiPlayer.getState() == MidiPlayer::State::ST_STOPPED)
    {
        messageListBox.updateContent();
    }
}
