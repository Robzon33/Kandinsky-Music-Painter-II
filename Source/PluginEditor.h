/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "gui/MainComponent.h"
#include "model/MainModel.h"
#include "player/MidiPlayer.h"
#include "model/ProjectSettings.h"

class MainComponent;

//==============================================================================
/**
*/
class KandinskyMusicPainterIIAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    KandinskyMusicPainterIIAudioProcessorEditor (KandinskyMusicPainterIIAudioProcessor&, MainModel&, MidiPlayer& mp, ProjectSettings&);
    ~KandinskyMusicPainterIIAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;
private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    KandinskyMusicPainterIIAudioProcessor& audioProcessor;
    MainModel& mainModel;
    MidiPlayer& midiPlayer;
    ProjectSettings& settings;

    // The editors components
    juce::ScopedPointer<MainComponent> mainComponent;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (KandinskyMusicPainterIIAudioProcessorEditor)
};
