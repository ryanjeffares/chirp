/*
  ==============================================================================

    MenuBarComponent.cpp
    Created: 27 Nov 2021 12:48:33am
    Author:  ryand

  ==============================================================================
*/

#include "MenuBarComponent.h"

using namespace chirp;
using namespace chirp::Components;

MenuBarComponent::MenuBarComponent()
{
    m_BarNames = { "File", "Edit", "View", "Run" };
    m_MenuBar.reset(new juce::MenuBarComponent(this));    
    addAndMakeVisible(m_MenuBar.get());

    setApplicationCommandManagerToWatch(&m_CommandManager);
    m_CommandManager.registerAllCommandsForTarget(this);
    m_CommandManager.setFirstCommandTarget(this);
    addKeyListener(m_CommandManager.getKeyMappings());
    setWantsKeyboardFocus(true);
}

MenuBarComponent::~MenuBarComponent()
{
}

void MenuBarComponent::resized()
{
    auto b = getLocalBounds();
    m_MenuBar->setBounds(b.removeFromTop(juce::LookAndFeel_V4::getDefaultLookAndFeel().getDefaultMenuBarHeight()));
}

juce::StringArray MenuBarComponent::getMenuBarNames()
{
    return m_BarNames;
}

juce::PopupMenu MenuBarComponent::getMenuForIndex(int topLevelMenuIndex, const juce::String& menuName)
{
    juce::PopupMenu menu;

    switch (topLevelMenuIndex)
    {
        case 0: // File
            menu.addCommandItem(&m_CommandManager, ChirpCommandIDs::Open);
            menu.addCommandItem(&m_CommandManager, ChirpCommandIDs::Save);
            break;
        case 3: // Run
            menu.addCommandItem(&m_CommandManager, ChirpCommandIDs::Render);
            menu.addCommandItem(&m_CommandManager, ChirpCommandIDs::Run);
            menu.addCommandItem(&m_CommandManager, ChirpCommandIDs::Stop);
            break;
    }

    return menu;
}

void MenuBarComponent::menuItemSelected(int menuItemId, int topLevelMenuIndex)
{

}

void MenuBarComponent::getCommandInfo(juce::CommandID commandId, juce::ApplicationCommandInfo& result)
{
    switch (commandId)
    {
        case ChirpCommandIDs::Open:
            result.setInfo("Open", "Open an existing Csound file.", "File", 0);
            result.addDefaultKeypress('o', juce::ModifierKeys::commandModifier);
            break;
        case ChirpCommandIDs::Save:
            result.setInfo("Save", "Save the currently opened Csound file.", "File", 0);
            result.addDefaultKeypress('s', juce::ModifierKeys::commandModifier);
            break;
        case ChirpCommandIDs::Render:
            result.setInfo("Render", "Render the currently opened Csound file.", "Run", 0);
            result.addDefaultKeypress('r', juce::ModifierKeys::commandModifier | juce::ModifierKeys::shiftModifier);
            break;
        case ChirpCommandIDs::Run:
            result.setInfo("Run", "Run the currently opened Csound file.", "Run", 0);
            result.addDefaultKeypress('r', juce::ModifierKeys::commandModifier);
            break;
        case ChirpCommandIDs::Stop:
            result.setInfo("Stop", "Stop the currently playing Csound file.", "Run", 0);
            result.addDefaultKeypress('c', juce::ModifierKeys::commandModifier);
            break;
    }
}

bool MenuBarComponent::perform(const InvocationInfo& info)
{
    switch (info.commandID)
    {
        case ChirpCommandIDs::Open:
            openFile();
            return true;
        case ChirpCommandIDs::Save:
            saveFile();
            return true;
        case ChirpCommandIDs::Render:
            renderCsound();
            return true;
        case ChirpCommandIDs::Run:
            runCsound();
            return true;
        case ChirpCommandIDs::Stop:
            stopCsound();
            return true;
        default:
            return false;
    }
}

void MenuBarComponent::getAllCommands(juce::Array<juce::CommandID>& commands)
{
    juce::Array<juce::CommandID> c{ ChirpCommandIDs::Open, ChirpCommandIDs::Save, ChirpCommandIDs::Render, ChirpCommandIDs::Run, ChirpCommandIDs::Stop };
    commands.addArray(c);
}

juce::ApplicationCommandTarget* MenuBarComponent::getNextCommandTarget()
{
    return nullptr;
}

void MenuBarComponent::saveFile()
{
    customBroadcast(ChirpCommandIDs::Save);
}

void MenuBarComponent::openFile()
{
    customBroadcast(ChirpCommandIDs::Open);
}

void MenuBarComponent::renderCsound()
{
    customBroadcast(ChirpCommandIDs::Render);
}

void MenuBarComponent::runCsound()
{
    customBroadcast(ChirpCommandIDs::Run);
}

void MenuBarComponent::stopCsound()
{
    customBroadcast(ChirpCommandIDs::Stop);
}