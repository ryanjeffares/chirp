/*
  ==============================================================================

    CsoundConsoleOutputComponent.h
    Created: 28 Nov 2021 8:06:26pm
    Author:  ryand

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

#include "LF.h"
#include "../Listeners/CustomListener.h"
#include "../Utils/Functions.h"

namespace chirp
{
    class MainComponent;

    namespace Components
    {
        class CsoundConsoleOutputComponent : public juce::TextEditor, 
            public juce::Timer,
            public juce::TextButton::Listener,
            public chirp::CustomBroadcaster<bool>
        {
        public:
            CsoundConsoleOutputComponent(chirp::MainComponent* owner);

            // cannot overwrite TextEditor::resized, must call this
            void resizeChildren();
            void timerCallback() override;
            void buttonClicked(juce::Button* button) override;

        private:
            juce::Font m_Font;

            juce::TextButton m_IncreaseSize, m_DecreaseSize, m_ClearOnPlay;
            chirp::MainComponent* m_Owner;
        };
    }
}