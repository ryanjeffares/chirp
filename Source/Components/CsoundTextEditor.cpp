/*
  ==============================================================================

    CsoundTextEditor.cpp
    Created: 27 Nov 2021 2:52:35pm
    Author:  ryand

  ==============================================================================
*/

#include "CsoundTextEditor.h"

using namespace chirp::Components;

CsoundTextEditor::CsoundTextEditor()
{
    auto b = getBoundsInParent();
    auto top = juce::LookAndFeel_V4::getDefaultLookAndFeel().getDefaultMenuBarHeight();

    setColour(juce::TextEditor::ColourIds::backgroundColourId, juce::Colour(40, 44, 52));
    setColour(juce::TextEditor::ColourIds::highlightColourId, juce::Colour(juce::uint8(255), juce::uint8(255), juce::uint8(255), 0.2f));

    setFont(LF::getSpaceMono(24));
    setBounds(0, top, b.getWidth() / 2, b.getHeight() / 4 * 3);
    setMultiLine(true, false);
    setReturnKeyStartsNewLine(true);
}