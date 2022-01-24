/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
KandinskyMusicPainterIIAudioProcessorEditor::KandinskyMusicPainterIIAudioProcessorEditor (KandinskyMusicPainterIIAudioProcessor& p, MainModel& m, MidiPlayer& mp, ProjectSettings& ps)
    : AudioProcessorEditor (&p), audioProcessor (p), mainModel (m), midiPlayer (mp), settings (ps)
{
    mainComponent = new MainComponent(mainModel, midiPlayer, settings);
    addAndMakeVisible(mainComponent);

    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (1200, 600);
}

KandinskyMusicPainterIIAudioProcessorEditor::~KandinskyMusicPainterIIAudioProcessorEditor()
{
}

//==============================================================================
void KandinskyMusicPainterIIAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.setColour (juce::Colours::white);
    g.setFont (15.0f);
    g.drawFittedText ("Hello World!", getLocalBounds(), juce::Justification::centred, 1);
}

void KandinskyMusicPainterIIAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..

    juce::Rectangle<int> area(getLocalBounds());

    if (mainComponent != nullptr)
    {
        mainComponent->setBounds(area);
    }
}

void KandinskyMusicPainterIIAudioProcessorEditor::testProcessor()
{
}
