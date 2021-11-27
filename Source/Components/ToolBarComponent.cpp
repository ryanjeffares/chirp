/*
  ==============================================================================

    ToolBarComponent.cpp
    Created: 27 Nov 2021 6:44:19pm
    Author:  ryand

  ==============================================================================
*/

#include "ToolBarComponent.h"

using namespace chirp;
using namespace chirp::Components;

ToolBarComponent::ToolBarComponent()
{
    setColour(ColourIds::backgroundColourId, juce::Colour(30, 30, 30));

    auto playImage = juce::PNGImageFormat::loadFrom(BinaryData::play_png, BinaryData::play_pngSize);
    auto hoveredPlay = playImage.createCopy();
    hoveredPlay.duplicateIfShared();
    hoveredPlay.desaturate();

    m_PlayButton.setImages(
        false, true, true, 
        playImage, 1, {},
        hoveredPlay, 1, {},
        hoveredPlay, 1, juce::Colours::lightgrey
    );
    m_PlayButton.addListener(this);

    auto renderImage = juce::PNGImageFormat::loadFrom(BinaryData::render_png, BinaryData::render_pngSize);
    auto hoveredRender = renderImage.createCopy();
    hoveredRender.duplicateIfShared();
    hoveredRender.desaturate();

    m_RenderButton.setImages(
        false, true, true,
        renderImage, 1, {},
        hoveredRender, 1, {},
        hoveredRender, 1, juce::Colours::lightgrey
    );
    m_RenderButton.addListener(this);

    auto stopImage = juce::PNGImageFormat::loadFrom(BinaryData::stop_png, BinaryData::stop_pngSize);
    auto hoveredStop = stopImage.createCopy();
    hoveredStop.duplicateIfShared();
    hoveredStop.desaturate();

    m_StopButton.setImages(
        false, true, true,
        stopImage, 1, {},
        hoveredStop, 1, {},
        hoveredStop, 1, juce::Colours::lightgrey
    );
    m_StopButton.addListener(this);

    addAndMakeVisible(m_PlayButton);
    addAndMakeVisible(m_RenderButton);
    addAndMakeVisible(m_StopButton);
}

void ToolBarComponent::resized()
{
    auto space = getHeight() / 5;
    auto buttonHeight = getHeight() - (space * 2);
    m_PlayButton.setBounds(space, space, buttonHeight, buttonHeight);
    m_RenderButton.setBounds((space * 2) + buttonHeight, space, buttonHeight, buttonHeight);
    m_StopButton.setBounds((space * 3) + (buttonHeight * 2), space, buttonHeight, buttonHeight);
}

void ToolBarComponent::buttonClicked(juce::Button* button)
{
    if (button == &m_PlayButton)
    {
        setPlaybackEnabled(false);
        customBroadcast(chirp::ChirpCommandIDs::Run);
    }
    else if (button == &m_RenderButton)
    {
        setPlaybackEnabled(false);
        customBroadcast(chirp::ChirpCommandIDs::Render);
    }
    else if (button == &m_StopButton)
    {
        customBroadcast(chirp::ChirpCommandIDs::Stop);
    }
}

void ToolBarComponent::setPlaybackEnabled(bool state)
{
    m_PlayButton.setEnabled(state);
    m_RenderButton.setEnabled(state);
}