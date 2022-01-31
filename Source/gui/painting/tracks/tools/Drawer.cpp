/*
  ==============================================================================

    Drawer.cpp
    Created: 11 Jan 2022 10:57:00am
    Author:  Toko

  ==============================================================================
*/

#include "Drawer.h"

Drawer::Drawer()
{
    tool = PaintingHelper::Tool::singleLine;
}

Drawer::~Drawer()
{
}

void Drawer::setSelectedTool(int index)
{
    tool = PaintingHelper::getTool(index);
}

juce::Path* Drawer::createPath(juce::OwnedArray<juce::Point<int>> &points)
{
    juce::Path* newPath = new juce::Path();
    
    if (tool == PaintingHelper::Tool::singleLine)
    {
        if (points.size() == 2)
        {
            newPath->startNewSubPath((float)points[0]->getX(), (float)points[0]->getY());
            newPath->lineTo((float)points[1]->getX(), (float)points[1]->getY());
            return newPath;
        }
    }
    if (tool == PaintingHelper::Tool::rectangle)
    {
        if (points.size() == 2)
        {
            float x = juce::jmin<float>((float)points[0]->getX(), (float)points[1]->getX());
            float y = juce::jmin<float>((float)points[0]->getY(), (float)points[1]->getY());
            float width = std::abs((float)points[0]->getX() - (float)points[1]->getX());
            float height = std::abs((float)points[0]->getY() - (float)points[1]->getY());
            newPath->addRectangle(x, y, width, height);
            return newPath;
        }
    }
    if (tool == PaintingHelper::Tool::ellipse)
    {
        if (points.size() == 2)
        {
            float x = juce::jmin<float>((float)points[0]->getX(), (float)points[1]->getX());
            float y = juce::jmin<float>((float)points[0]->getY(), (float)points[1]->getY());
            float width = std::abs((float)points[0]->getX() - (float)points[1]->getX());
            float height = std::abs((float)points[0]->getY() - (float)points[1]->getY());
            newPath->addEllipse(x, y, width, height);
            return newPath;
        }
    }
    if (tool == PaintingHelper::Tool::sinus)
    {
        if (points.size() == 2)
        {
            juce::Rectangle<float> rectangle(points[0]->toFloat(), points[1]->toFloat());

            juce::Point<float> controlPoint1(rectangle.getX(), rectangle.getY() + rectangle.getHeight() / 2);
            juce::Point<float> controlPoint2(rectangle.getX() + rectangle.getWidth() / 4, rectangle.getY());
            juce::Point<float> controlPoint3(rectangle.getX() + rectangle.getWidth() / 2, rectangle.getY() + rectangle.getHeight() / 2);
            juce::Point<float> controlPoint4(rectangle.getX() + rectangle.getWidth() / 4 * 3, rectangle.getY() + rectangle.getHeight());
            juce::Point<float> controlPoint5(rectangle.getX() + rectangle.getWidth(), rectangle.getY() + rectangle.getHeight() / 2);

            newPath->startNewSubPath(controlPoint1);
            newPath->quadraticTo(controlPoint2, controlPoint3);
            newPath->quadraticTo(controlPoint4, controlPoint5);
            return newPath;
        }
    }

    return nullptr;
}
