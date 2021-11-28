#include "MainComponent.h"

using namespace chirp;
using namespace chirp::Components;

//==============================================================================
MainComponent::MainComponent() 
    : m_ClearOutputOnPlay(false), m_CsoundShouldStop(false), m_CsoundOutputConsole(this)
{
    setSize (600, 400);
    m_Csound = new Csound();       

    auto b = getLocalBounds();
    auto top = LF::getDefaultLookAndFeel().getDefaultMenuBarHeight();

    m_CsoundOutputConsole.addCustomListener(this);
    addAndMakeVisible(m_CsoundOutputConsole);    

    addAndMakeVisible(m_TextEditor);

    m_MenuBar.addCustomListener(this);
    addAndMakeVisible(m_MenuBar);

    m_ToolBar.addCustomListener(this);
    addAndMakeVisible(m_ToolBar);
}

MainComponent::~MainComponent()
{
    LF::releaseResources();
    delete m_Csound;
}

//==============================================================================
void MainComponent::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (juce::Colours::black);
}

void MainComponent::changeListenerCallback(juce::ChangeBroadcaster* broadcaster)
{
    /*if (broadcaster == &m_CsoundOutputConsole)
    {
        auto state = m_ClearOutputOnPlay.load();
        m_ClearOutputOnPlay.store(!state);
    }*/
}

void MainComponent::customListenerCallback(CustomBroadcaster<ChirpCommandIDs>* broadcaster, ChirpCommandIDs option)
{    
    switch (option)
    {
        case ChirpCommandIDs::Open:
            m_FileChooser.reset(new juce::FileChooser("Select Csound file to open.", juce::File(), "*.csd"));
            m_FileChooser->launchAsync(
                juce::FileBrowserComponent::openMode | juce::FileBrowserComponent::canSelectFiles, 
                [this](const juce::FileChooser& chooser)
                {
                    juce::File chosenFile(chooser.getResult());
                    if (chosenFile.existsAsFile())
                    {
                        displayNewCsoundFile(chosenFile);
                    }
                }
            );
            break;
        case ChirpCommandIDs::Save:
            saveCsoundFile();
            break;
        case ChirpCommandIDs::Run:
            prepareCsoundPlayback(true);
            break;
        case ChirpCommandIDs::Render:
            prepareCsoundPlayback(false);
            break;
        case ChirpCommandIDs::Stop:
            if (m_CsoundRunning.load())
            {
                m_CsoundShouldStop.store(true);
            }
            break;
    }
}

void MainComponent::customListenerCallback(CustomBroadcaster<bool>* broadcaster, bool value)
{
    if (broadcaster == &m_CsoundOutputConsole)
    {
        m_ClearOutputOnPlay.store(value);
    }
}

void MainComponent::resized()
{
    auto bounds = getBounds();
    auto top = juce::LookAndFeel_V4::getDefaultLookAndFeel().getDefaultMenuBarHeight();

    m_MenuBar.setBounds(bounds.removeFromTop(top));
    m_ToolBar.setBounds(bounds.removeFromTop(getHeight() / 15));
    m_TextEditor.setBounds(bounds.removeFromTop(bounds.getHeight() / 3 * 2));    
    m_CsoundOutputConsole.setBounds(bounds);
    m_CsoundOutputConsole.resizeChildren();
}

juce::String MainComponent::getCsoundConsoleOutput()
{
    if (m_Csound != nullptr)
    {
        juce::String message = "";
        auto messageCount = m_Csound->GetMessageCnt();

        if (messageCount == 0)
        {
            return message;
        }

        while (m_Csound->GetMessageCnt() > 0)
        {
            juce::String newMessage = m_Csound->GetFirstMessage();
            message += newMessage;
            m_Csound->PopFirstMessage();
        }

        return message;
    }

    return juce::String();
}

void MainComponent::displayNewCsoundFile(juce::File csoundFile)
{
    m_CurrentCsoundFile = csoundFile;
    juce::StringArray lines;
    m_CurrentCsoundFile.readLines(lines);
    m_TextEditor.setText(lines.joinIntoString("\n"));
}

void MainComponent::saveCsoundFile()
{
    if (m_CurrentCsoundFile.existsAsFile())
    {
        m_CurrentCsoundFile.replaceWithText(m_TextEditor.getText());
    }
}

void MainComponent::prepareCsoundPlayback(bool run)
{
    m_ToolBar.setPlaybackEnabled(false);
    std::thread csoundThread(&MainComponent::performCsound, this, run);
    csoundThread.detach();
}

void MainComponent::performCsound(bool run)
{
    m_CsoundRunning.store(true);

    if (m_ClearOutputOnPlay.load())
    {
        juce::MessageManagerLock mmLock;
        m_CsoundOutputConsole.clear();
    }    

    m_Csound->Reset();
    m_Csound->CreateMessageBuffer(0);

    auto compileResult = m_Csound->CompileCsd(m_CurrentCsoundFile.getFullPathName().getCharPointer());
    if (compileResult == 0)
    {
        if (run) 
        {
            m_Csound->SetOption("-odac");
        }

        auto startResult = m_Csound->Start();
        if (startResult == 0)
        {
            while (m_Csound->PerformKsmps() == 0)
            {
                if (m_CsoundShouldStop.load())
                {
                    m_Csound->Stop();
                    break;
                }
            }            
        }
    }

    m_Csound->Cleanup();

    {
        juce::MessageManagerLock mm;
        m_ToolBar.setPlaybackEnabled(true); 
    }

    m_CsoundRunning.store(false);
}
