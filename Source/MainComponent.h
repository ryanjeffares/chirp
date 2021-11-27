#pragma once

#include <JuceHeader.h>

#include "csound.hpp"

#include "Components/CsoundConsoleComponent.h"
#include "Components/MenuBarComponent.h"
#include "Components/CsoundTextEditor.h"
#include "Components/ToolBarComponent.h"

//==============================================================================
/*
    This component lives inside our window, and this is where you should put all
    your controls and content.
*/
class MainComponent  : public juce::Component, 
    public juce::Timer, 
    public juce::ChangeListener,
    public chirp::CustomListener<chirp::ChirpCommandIDs>
{
public:
    //==============================================================================
    MainComponent();
    ~MainComponent() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

    void changeListenerCallback(juce::ChangeBroadcaster*) override;

    void customListenerCallback(chirp::CustomBroadcaster<chirp::ChirpCommandIDs>* broadcaster, chirp::ChirpCommandIDs option) override;

    void timerCallback() override;

    inline chirp::Components::MenuBarComponent* getMenuBar() { return &m_MenuBar; }

private:
    //==============================================================================

    void prepareCsoundPlayback(bool run);

    void displayNewCsoundFile(juce::File csoundFile);
    void saveCsoundFile();

    void performCsound(bool run);

    void pushCsoundOutputMessage(std::string&& message);
    bool popCsoundOutputMessage(std::string& fileName, std::chrono::milliseconds timeout);

    juce::File m_CurrentCsoundFile;

    std::unique_ptr<juce::FileChooser> m_FileChooser;

    chirp::Components::MenuBarComponent m_MenuBar;
    chirp::Components::CsoundTextEditor m_TextEditor;
    chirp::Components::CsoundConsoleComponent m_CsoundOutputConsole;    
    chirp::Components::ToolBarComponent m_ToolBar;

    Csound* m_Csound;

    std::atomic_bool m_ClearOutputOnPlay;
    std::atomic_bool m_CsoundShouldStop;
    std::atomic_bool m_CsoundRunning;
    std::queue<std::string> m_CsoundOutputMessages;
    std::mutex m_Mutex;
    std::condition_variable m_PopulatedNotifier;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};
