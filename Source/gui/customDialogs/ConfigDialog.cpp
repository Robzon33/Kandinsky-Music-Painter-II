/*
  ==============================================================================

    ConfigDialog.cpp
    Created: 2 Feb 2022 10:38:37am
    Author:  Toko

  ==============================================================================
*/

#include "ConfigDialog.h"

ConfigDialog::ConfigDialog(ProjectSettings& ps)
    : settings(ps)
{
    juce::Array<juce::PropertyComponent*> comps;

    nameComp = new juce::TextPropertyComponent(juce::Value(settings.getName()),
                                                                            "Project name",
                                                                            200,
                                                                            false);
    comps.add(nameComp);

    widthSliderComp = new TrackWidthSliderComponent("Track width",
                                                     100,
                                                     20000, 
                                                     100, 
                                                     settings.getWidth());
    comps.add(widthSliderComp);

    propertyPanel.addProperties(comps);
    addAndMakeVisible(propertyPanel);

    applyButton.setButtonText("apply");
    addAndMakeVisible(applyButton);
    applyButton.addListener(this);

    resetButton.setButtonText("reset");
    addAndMakeVisible(resetButton);
    resetButton.addListener(this);
}

ConfigDialog::~ConfigDialog()
{
}

void ConfigDialog::paint(juce::Graphics& g)
{
    g.fillAll(juce::Colour::greyLevel(0.8f));
}

void ConfigDialog::resized()
{
    juce::Rectangle<int> area(getLocalBounds().reduced(4));

    propertyPanel.setBounds(area.removeFromTop(area.getHeight() * 0.8f));

    applyButton.setBounds(area.removeFromLeft(area.getWidth() * 0.5f));
    resetButton.setBounds(area);
}

void ConfigDialog::loadContent()
{
    nameComp->setText(settings.getName());
    widthSliderComp->setValue(settings.getWidth());
}

void ConfigDialog::applyNewSettings()
{
    settings.setName(nameComp->getText());
    settings.setWidth(widthSliderComp->getValue());
}

juce::DialogWindow* ConfigDialog::getDialogWindow()
{
    juce::DialogWindow::LaunchOptions options;
    options.content.setNonOwned(this);
    options.content->setSize(300, 300);
    options.dialogTitle = "Project Settings";
    options.dialogBackgroundColour = juce::Colour(0xff0e345a);
    options.escapeKeyTriggersCloseButton = true;
    options.useNativeTitleBar = false;
    options.resizable = true;

    return options.launchAsync();
}

void ConfigDialog::buttonClicked(juce::Button* button)
{
    if (button == &applyButton)
    {
        applyNewSettings();
    }
    if (button == &resetButton)
    {
        loadContent();
    }
}
