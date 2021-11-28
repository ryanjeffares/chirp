#pragma once

#include <JuceHeader.h>

#include "csound.hpp"

#include "Components/CsoundConsoleOutputComponent.h"
#include "Components/MenuBarComponent.h"
#include "Components/CsoundTextEditor.h"
#include "Components/ToolBarComponent.h"

//==============================================================================
/*
    This component lives inside our window, and this is where you should put all
    your controls and content.
*/

namespace chirp
{
    class MainComponent : public juce::Component,
        public juce::ChangeListener,
        public chirp::CustomListener<chirp::ChirpCommandIDs>,
        public chirp::CustomListener<bool>
    {
    public:
        //==============================================================================
        MainComponent();
        ~MainComponent() override;

        //==============================================================================
        void paint(juce::Graphics&) override;
        void resized() override;

        void changeListenerCallback(juce::ChangeBroadcaster*) override;
        void customListenerCallback(chirp::CustomBroadcaster<chirp::ChirpCommandIDs>* broadcaster, chirp::ChirpCommandIDs option) override;
        void customListenerCallback(chirp::CustomBroadcaster<bool>* broadcaster, bool value) override;
        juce::String getCsoundConsoleOutput();

        inline Components::MenuBarComponent* getMenuBar() { return &m_MenuBar; }

    private:
        //==============================================================================

        void prepareCsoundPlayback(bool run);

        void displayNewCsoundFile(juce::File csoundFile);
        void saveCsoundFile();

        void performCsound(bool run);

        juce::File m_CurrentCsoundFile;

        std::unique_ptr<juce::FileChooser> m_FileChooser;

        Components::MenuBarComponent m_MenuBar;
        Components::CsoundTextEditor m_TextEditor;
        Components::CsoundConsoleOutputComponent m_CsoundOutputConsole;
        Components::ToolBarComponent m_ToolBar;

        Csound* m_Csound;

        std::atomic_bool m_ClearOutputOnPlay;
        std::atomic_bool m_CsoundShouldStop;
        std::atomic_bool m_CsoundRunning;

        std::vector<std::string> m_CsoundOutputMessages;
        int m_LastDisplayedMessageIndex = 0;
        std::mutex m_Mutex;
        std::condition_variable m_PopulatedNotifier;

        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MainComponent)
    };
}
