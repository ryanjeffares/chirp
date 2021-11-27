/*
  ==============================================================================

    ToolBarComponent.h
    Created: 27 Nov 2021 6:44:19pm
    Author:  ryand

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

#include "../Listeners/CustomListener.h"
#include "../Utils/Enums.h"
#include "LF.h" 

namespace chirp
{
    namespace Components
    {
        class ToolBarComponent : public juce::Toolbar,
            public chirp::CustomBroadcaster<chirp::ChirpCommandIDs>,
            public juce::ImageButton::Listener
        {
        public:
            ToolBarComponent();

            void resized() override;
            void buttonClicked(juce::Button*) override;
            void setPlaybackEnabled(bool);

        private:
            juce::ImageButton m_PlayButton, m_RenderButton, m_StopButton;
        };
    }
}
