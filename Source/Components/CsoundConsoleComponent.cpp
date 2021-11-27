/*
  ==============================================================================

    CsoundConsoleComponent.cpp
    Created: 26 Nov 2021 11:05:33pm
    Author:  ryand

  ==============================================================================
*/

#include "CsoundConsoleComponent.h"

using namespace chirp::Components;

CsoundConsoleComponent::CsoundConsoleComponent()
{    
    m_Font = LF::getSpaceMono(16);

    setReadOnly(true);
    setCaretVisible(false);
    setMultiLine(true, false);
    setFont(m_Font);

    setColour(juce::TextEditor::ColourIds::backgroundColourId, juce::Colour(30, 30, 30));
    setColour(juce::TextEditor::ColourIds::highlightColourId, juce::Colour(juce::uint8(255), juce::uint8(255), juce::uint8(255), 0.2f));

    m_ClearOutputOnPlay.setClickingTogglesState(true);
    m_ClearOutputOnPlay.setState(juce::Button::ButtonState::buttonNormal);
    m_ClearOutputOnPlay.setButtonText("Clear on Play");
    m_ClearOutputOnPlay.addListener(this);    
    addAndMakeVisible(m_ClearOutputOnPlay);

    m_IncreaseSize.setButtonText("+");
    m_IncreaseSize.addListener(this);
    addAndMakeVisible(m_IncreaseSize);

    m_DecreaseSize.setButtonText("-");
    m_DecreaseSize.addListener(this);
    addAndMakeVisible(m_DecreaseSize);
}

void CsoundConsoleComponent::resized()
{
    m_ClearOutputOnPlay.setBounds(getWidth() - 70, 0, 70, 35);    
    m_IncreaseSize.setBounds(getWidth() - 100, 0, 30, 35);
    m_DecreaseSize.setBounds(getWidth() - 130, 0, 30, 35);
}

void CsoundConsoleComponent::buttonClicked(juce::Button* button)
{
    if (button == &m_ClearOutputOnPlay)
    {
        sendChangeMessage();
    }
    else if (button == &m_IncreaseSize)
    {
        auto currentSize = m_Font.getHeight();
        currentSize++;
        m_Font = LF::getSpaceMono(currentSize);
        applyFontToAllText(m_Font);        
    }
    else if (button == &m_DecreaseSize)
    {
        auto currentSize = m_Font.getHeight();
        currentSize--;
        m_Font = LF::getSpaceMono(currentSize);
        applyFontToAllText(m_Font);
    }
}