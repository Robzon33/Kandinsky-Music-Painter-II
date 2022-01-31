/*
  ==============================================================================

    PaintingHelper.cpp
    Created: 28 Jan 2022 5:35:48pm
    Author:  Toko

  ==============================================================================
*/

#include "PaintingHelper.h"

int PaintingHelper::getNumberOfTools()
{
    return static_cast<int>(Tool::NUMBEROFTOOLS);
}

PaintingHelper::Tool PaintingHelper::getTool(int index)
{
    if (0 <= index < getNumberOfTools())
    {
        return static_cast<Tool>(index);
    }
}

juce::DrawableButton* PaintingHelper::getButton(int index)
{
    juce::DrawablePath drawablePath;
    juce::Path p;
    juce::String buttonName;

    switch (index)
    {
    case 0:
    {      
        p.startNewSubPath(1.0f, 1.0f);
        p.lineTo(10.0f, 10.0f);
        buttonName = "Single line";
        break;
    }
    case 1:
    {
        p.addRectangle(3.0f, 3.0f, 13.0f, 10.0f);
        buttonName = "Rectangle";
        break;
    }
    case 2:
    {
        p.addEllipse(3.0f, 3.0f, 13.0f, 10.0f);
        buttonName = "Ellipse";
        break;
    }
    case 3:
    {
        p.startNewSubPath(1.0f, 1.0f);
        p.lineTo(2.0f, 10.0f);
        p.lineTo(5.0f, 7.0f);
        p.lineTo(10.0f, 8.0f);
        buttonName = "Multi line";
        break;
    }
    default:
        return nullptr;
    }
    
    drawablePath.setPath(p);
    drawablePath.setFill(juce::Colours::transparentWhite);
    drawablePath.setStrokeFill(juce::Colours::darkorange);
    drawablePath.setStrokeThickness(0.3f);

    auto* db = new juce::DrawableButton(buttonName, juce::DrawableButton::ImageAboveTextLabel);
    db->setImages(&drawablePath);
    db->setClickingTogglesState(true);
    return db;
}
