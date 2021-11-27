/*
  ==============================================================================

    LF.h
    Created: 27 Nov 2021 12:11:18am
    Author:  ryand

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class LF : public juce::LookAndFeel_V4
{
public:

    static juce::Font getCutive(float height);
    static juce::Font getCourier(float height);
    static juce::Font getCourierBold(float height);
    static juce::Font getCourierItalic(float height);
    static juce::Font getCourierBoldItalic(float height);
    static juce::Font getJetBrainsMono(float height);
    static juce::Font getSpaceMono(float height);

    static void releaseResources();

private:

    static void acquireResources();

    static juce::Typeface::Ptr s_CourierTypeface, s_CutiveTypeface, s_JetbrainsMonoTypeface, s_SpaceMonoTypeface;
    static bool s_ResourcesAcquired;    
};
