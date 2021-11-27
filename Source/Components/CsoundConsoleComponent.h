/*
  ==============================================================================

    CsoundConsoleComponent.h
    Created: 26 Nov 2021 11:05:33pm
    Author:  ryand

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

#include "LF.h"

namespace chirp
{
    namespace Components
    {
        class CsoundConsoleComponent : public juce::TextEditor, public juce::Button::Listener, public juce::ChangeBroadcaster
        {
        public:
            CsoundConsoleComponent();

            void resized();

            void buttonClicked(juce::Button*) override;

        private:
            juce::TextButton m_ClearOutputOnPlay;
            juce::TextButton m_IncreaseSize, m_DecreaseSize;

            juce::Font m_Font;
        };
    }
}
