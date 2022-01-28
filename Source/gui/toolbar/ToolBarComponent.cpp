/*
  ==============================================================================

    ToolBarComponent.cpp
    Created: 27 Jan 2022 10:47:39am
    Author:  Toko

  ==============================================================================
*/

#include "ToolBarComponent.h"

ToolBarComponent::ToolBarComponent(juce::ApplicationCommandManager& acm)
    : commandManager (acm)
{
    //that was code from the juce demo
    //for (int i = 0; i < 4; ++i)
    //{
    //    juce::DrawablePath normal, over;

    //    juce::Path p;
    //    p.addStar({}, i + 5, 20.0f, 50.0f, -0.2f);
    //    normal.setPath(p);
    //    normal.setFill(juce::Colours::lightblue);
    //    normal.setStrokeFill(juce::Colours::black);
    //    normal.setStrokeThickness(4.0f);

    //    over.setPath(p);
    //    over.setFill(juce::Colours::blue);
    //    over.setStrokeFill(juce::Colours::black);
    //    over.setStrokeThickness(4.0f);

    //    auto* db = addToList(new juce::DrawableButton(juce::String(i + 5) + " points", juce::DrawableButton::ImageAboveTextLabel));
    //    db->setImages(&normal, &over, nullptr);
    //    db->setClickingTogglesState(true);
    //    db->setRadioGroupId(23456);

    //    //int buttonSize = 50;
    //    //db->setBounds(25 + i * buttonSize, 180, buttonSize, buttonSize);

    //    if (i == 0)
    //        db->setToggleState(true, juce::dontSendNotification);
    //}

    juce::DrawablePath drawablePath;
    juce::Path p;
    p.startNewSubPath(5.0f, 5.0f);
    p.lineTo(10.0f, 10.0f);
    
    drawablePath.setPath(p);
    //drawablePath.setFill(juce::Colours::navajowhite);
    drawablePath.setStrokeFill(juce::Colours::darkorange);
    drawablePath.setStrokeThickness(0.5f);

    auto* db = addToList(new juce::DrawableButton("Single line", juce::DrawableButton::ImageAboveTextLabel));
    db->setImages(&drawablePath);
    db->setClickingTogglesState(true);
    db->setRadioGroupId(23456);
    db->addListener(this);

    //==============================================================================
    juce::Path p1;
    p1.addRectangle(3.0f, 3.0f, 13.0f, 10.0f);

    drawablePath.setPath(p1);
    drawablePath.setFill(juce::Colours::transparentWhite);
    //drawablePath.setFill(juce::Colours::navajowhite);
    drawablePath.setStrokeFill(juce::Colours::darkorange);
    drawablePath.setStrokeThickness(1.0f);

    auto* db1 = addToList(new juce::DrawableButton("Rectangle", juce::DrawableButton::ImageAboveTextLabel));
    db1->setImages(&drawablePath);
    db1->setClickingTogglesState(true);
    db1->setRadioGroupId(23456);
    db1->addListener(this);
}

ToolBarComponent::~ToolBarComponent()
{
}

void ToolBarComponent::paint(juce::Graphics& g)
{
    g.fillAll(juce::Colours::black.brighter(0.2f));
}

void ToolBarComponent::resized()
{
    auto b = getLocalBounds();

    for (int i = 0; i < buttons.size(); i++)
    {
        buttons[i]->setBounds(b.removeFromLeft(60));
    }
}

void ToolBarComponent::buttonClicked(juce::Button* button)
{
    /*for (int i = 0; i < buttons.size(); i++)
    {
        if (buttons[i]->getToggleState())
        {

        }
    }*/
    commandManager.invokeDirectly(CommandIDs::selectTool, true);
}

int ToolBarComponent::getIndexOfSelectedButton()
{
    for (int i = 0; i < buttons.size(); i++)
    {
        if (buttons[i]->getToggleState())
        {
            return i;
        }
    }
}
