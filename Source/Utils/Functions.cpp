/*
  ==============================================================================

    Functions.cpp
    Created: 28 Nov 2021 8:45:10pm
    Author:  ryand

  ==============================================================================
*/

#include "Functions.h"

juce::StringArray chirp::Functions::splitString(const juce::String& str)
{
    if (!str.containsAnyOf("\n"))
    {
        return { str };
    }

    juce::StringArray result;

    int lastSplit = 0;
    for (auto i = 0; i < str.length(); i++)
    {
        if (str[i] == '\n')
        {
            result.add(str.substring(lastSplit, i + 1));
            lastSplit = i + 1;
        }
    }

    return result;
}