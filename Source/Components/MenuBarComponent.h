/*
  ==============================================================================

    MenuBarComponent.h
    Created: 27 Nov 2021 12:48:33am
    Author:  ryand

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

#include "../Listeners/CustomListener.h"
#include "../Utils/Enums.h"

namespace chirp
{
    namespace Components
    {
        class MenuBarComponent : public juce::Component,
            public juce::MenuBarModel,
            public chirp::CustomBroadcaster<chirp::ChirpCommandIDs>,
            public juce::ApplicationCommandTarget
        {
        public:

            MenuBarComponent();
            ~MenuBarComponent();

            void resized() override;

            juce::StringArray getMenuBarNames() override;
            juce::PopupMenu getMenuForIndex(int topLevelMenuIndex, const juce::String& menuName);
            void menuItemSelected(int menuItemId, int topLevelMenuIndex) override;
            void getCommandInfo(juce::CommandID commandId, juce::ApplicationCommandInfo& result) override;
            bool perform(const InvocationInfo& info) override;
            void getAllCommands(juce::Array<juce::CommandID>& commands) override;
            juce::ApplicationCommandTarget* getNextCommandTarget() override;

            inline juce::ApplicationCommandManager* getCommandManager() { return &m_CommandManager; }

        private:

            void saveFile();
            void openFile();
            void renderCsound();
            void runCsound();

            juce::ApplicationCommandManager m_CommandManager;
            std::unique_ptr<juce::MenuBarComponent> m_MenuBar;
            juce::StringArray m_BarNames;
        };
    }
}
