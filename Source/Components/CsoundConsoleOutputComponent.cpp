/*
  ==============================================================================

    CsoundConsoleOutputComponent.cpp
    Created: 28 Nov 2021 8:06:26pm
    Author:  ryand

  ==============================================================================
*/

#include "../MainComponent.h"
#include "CsoundConsoleOutputComponent.h"

using namespace chirp;
using namespace chirp::Components;

CsoundConsoleOutputComponent::CsoundConsoleOutputComponent(MainComponent* owner)
    : m_Owner(owner)
{
    m_Font = LF::getSpaceMono(16);
    setFont(m_Font);
    setReadOnly(true);
    setCaretVisible(false);
    setMultiLine(true, false);

    setColour(juce::TextEditor::ColourIds::backgroundColourId, juce::Colour(30, 30, 30));
    setColour(juce::TextEditor::ColourIds::highlightColourId, juce::Colour(juce::uint8(255), juce::uint8(255), juce::uint8(255), 0.2f));
    setColour(juce::TextEditor::ColourIds::textColourId, juce::Colours::white);

    m_IncreaseSize.setButtonText("+");
    m_IncreaseSize.addListener(this);
    m_DecreaseSize.setButtonText("-");
    m_DecreaseSize.addListener(this);
    m_ClearOnPlay.setButtonText("Clear on Play");
    m_ClearOnPlay.addListener(this);
    
    addAndMakeVisible(m_IncreaseSize);
    addAndMakeVisible(m_DecreaseSize);
    addAndMakeVisible(m_ClearOnPlay);

    startTimer(100);
}

void CsoundConsoleOutputComponent::resizeChildren()
{    
    m_ClearOnPlay.setBounds(getWidth() - 70, 0, 70, 35);
    m_DecreaseSize.setBounds(getWidth() - 105, 0, 35, 35);
    m_IncreaseSize.setBounds(getWidth() - 140, 0, 35, 35);    
}

void CsoundConsoleOutputComponent::timerCallback()
{
    const auto message = m_Owner->getCsoundConsoleOutput();
    if (message.isNotEmpty())
    {
        auto lines = chirp::Functions::splitString(message);
        for (const auto& l : lines)
        {
            if (l.containsIgnoreCase("warning"))
                setColour(ColourIds::textColourId, juce::Colours::yellow);
            else if (l.containsIgnoreCase("error"))
                setColour(ColourIds::textColourId, juce::Colours::red);
            else if (l.contains("out of range:"))
                setColour(ColourIds::textColourId, juce::Colours::orange);
            else
                setColour(ColourIds::textColourId, juce::Colours::white);

            insertTextAtCaret(l);
        }
    }
}

void CsoundConsoleOutputComponent::buttonClicked(juce::Button* button)
{
    if (button == &m_IncreaseSize)
    {
        auto size = m_Font.getHeight() + 1;
        m_Font.setHeight(size);
        applyFontToAllText(m_Font);
    }
    else if (button == &m_DecreaseSize)
    {
        auto size = m_Font.getHeight() - 1;
        m_Font.setHeight(size);
        applyFontToAllText(m_Font);
    }
    else if (button == &m_ClearOnPlay)
    {
        customBroadcast(m_ClearOnPlay.getState());
    }
}
