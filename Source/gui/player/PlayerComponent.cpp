/*
  ==============================================================================

    PlayerComponent.cpp
    Created: 6 Jul 2021 11:10:28am
    Author:  Toko

  ==============================================================================
*/

#include "PlayerComponent.h"

PlayerComponent::PlayerComponent(MidiPlayer& mp)
    : player(mp)
{
    colour = juce::Colours::pink;
    initSlider();
	initButtons();
}

PlayerComponent::~PlayerComponent()
{
}

void PlayerComponent::paint(juce::Graphics& g)
{
	g.fillAll(colour.withAlpha(0.4f));
}

void PlayerComponent::resized()
{
	auto b = getLocalBounds();

	tempoSlider->setBounds(b.removeFromLeft(getWidth() / 4).reduced(20));
	stopButton->setBounds(b.removeFromLeft(getWidth() / 4).reduced(30));
	playButton->setBounds(b.removeFromLeft(getWidth() / 4).reduced(10));
	pauseButton->setBounds(b.removeFromLeft(getWidth() / 4).reduced(30));
}

void PlayerComponent::buttonClicked(juce::Button* button)
{
}

void PlayerComponent::sliderValueChanged(juce::Slider* slider)
{
}

void PlayerComponent::initSlider()
{
	tempoSlider.reset(new juce::Slider());
	addAndMakeVisible(tempoSlider.get());
	tempoSlider->setRange(10, 200, 1);
	tempoSlider->setValue(40); /*TODO*/
	tempoSlider->setSliderStyle(juce::Slider::Rotary);
	tempoSlider->setRotaryParameters(juce::float_Pi * 1.2f, juce::float_Pi * 2.8f, false);
	tempoSlider->setTextBoxStyle(juce::Slider::TextBoxBelow, true, 60, 20);
	tempoSlider->setTextValueSuffix(" bpm");
	tempoSlider->addListener(this);
}

void PlayerComponent::initButtons()
{
	juce::DrawableImage playImage;
	playImage.setImage(juce::ImageCache::getFromMemory(BinaryData::playerplay_png,
		BinaryData::playerplay_pngSize));
	juce::DrawableImage playImageOver(playImage);
	playImageOver.setOverlayColour(juce::Colours::black.withAlpha(0.3f));

	juce::DrawableImage playImageDown(playImage);
	playImageDown.setOverlayColour(juce::Colours::black.withAlpha(0.7f));

	//==============================================================================
	juce::DrawableImage pauseImage;
	pauseImage.setImage(juce::ImageCache::getFromMemory(BinaryData::playerpause_png,
		BinaryData::playerpause_pngSize));
	juce::DrawableImage pauseImageOver(pauseImage);
	pauseImageOver.setOverlayColour(juce::Colours::black.withAlpha(0.3f));

	juce::DrawableImage pauseImageDown(pauseImage);
	pauseImageDown.setOverlayColour(juce::Colours::black.withAlpha(0.7f));

	//==============================================================================
	juce::DrawableImage stopImage;
	stopImage.setImage(juce::ImageCache::getFromMemory(BinaryData::playerstop_png,
		BinaryData::playerstop_pngSize));
	juce::DrawableImage stopImageOver(stopImage);
	stopImageOver.setOverlayColour(juce::Colours::black.withAlpha(0.3f));

	juce::DrawableImage stopImageDown(stopImage);
	stopImageDown.setOverlayColour(juce::Colours::black.withAlpha(0.7f));

	//==============================================================================
	playButton.reset(new juce::DrawableButton("play", juce::DrawableButton::ImageFitted));
	playButton->setImages(&playImage, &playImageOver, &playImageDown);
	addAndMakeVisible(playButton.get());
	playButton->addListener(this); /* playButton.GET()????->addListener(this); */

	pauseButton.reset(new juce::DrawableButton("pause", juce::DrawableButton::ImageFitted));
	pauseButton->setImages(&pauseImage, &pauseImageOver, &pauseImageDown);
	addAndMakeVisible(pauseButton.get());
	pauseButton->addListener(this);

	stopButton.reset(new juce::DrawableButton("stop", juce::DrawableButton::ImageFitted));
	stopButton->setImages(&stopImage, &stopImageOver, &stopImageDown);
	addAndMakeVisible(stopButton.get());
	stopButton->addListener(this);
}
