/*
  ==============================================================================

    PlayerControlComponent.cpp
    Created: 6 Jul 2021 11:10:28am
    Author:  Toko

  ==============================================================================
*/

#include "PlayerControlComponent.h"

PlayerControlComponent::PlayerControlComponent(MidiPlayer& mp, ProjectSettings& ps)
    : player(mp), settings(ps)
{
    colour = juce::Colours::pink;
    initSlider();
	initButtons();
}

PlayerControlComponent::~PlayerControlComponent()
{
}

void PlayerControlComponent::paint(juce::Graphics& g)
{
	g.fillAll(colour.withAlpha(0.4f));
}

void PlayerControlComponent::resized()
{
	auto b = getLocalBounds();

	tempoSlider->setBounds(b.removeFromLeft(getWidth() / 4).reduced(10));
	stopButton->setBounds(b.removeFromLeft(getWidth() / 4).reduced(30));
	playButton->setBounds(b.removeFromLeft(getWidth() / 4).reduced(10));
	pauseButton->setBounds(b.removeFromLeft(getWidth() / 4).reduced(30));
}

void PlayerControlComponent::buttonClicked(juce::Button* button)
{
	if (button == playButton.get())		{ player.play(); }
	if (button == pauseButton.get())	{ player.pause(); }
	if (button == stopButton.get())		{ player.stop(); }
}

void PlayerControlComponent::sliderValueChanged(juce::Slider* slider)
{
	settings.setPlayerSpeed((int)slider->getValue());
}

void PlayerControlComponent::initSlider()
{
	tempoSlider.reset(new juce::Slider());
	addAndMakeVisible(tempoSlider.get());
	tempoSlider->setRange(1, 100, 1);
	tempoSlider->setValue(settings.getPlayerSpeed());
	tempoSlider->setSliderStyle(juce::Slider::Rotary);
	tempoSlider->setRotaryParameters(juce::float_Pi * 1.2f, juce::float_Pi * 2.8f, false);
	tempoSlider->setTextBoxStyle(juce::Slider::TextBoxBelow, true, 120, 30);
	tempoSlider->setTextValueSuffix(" pixels per second");
	tempoSlider->addListener(this);
}

void PlayerControlComponent::initButtons()
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
	playButton->addListener(this);

	pauseButton.reset(new juce::DrawableButton("pause", juce::DrawableButton::ImageFitted));
	pauseButton->setImages(&pauseImage, &pauseImageOver, &pauseImageDown);
	addAndMakeVisible(pauseButton.get());
	pauseButton->addListener(this);

	stopButton.reset(new juce::DrawableButton("stop", juce::DrawableButton::ImageFitted));
	stopButton->setImages(&stopImage, &stopImageOver, &stopImageDown);
	addAndMakeVisible(stopButton.get());
	stopButton->addListener(this);
}
