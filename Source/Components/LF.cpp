/*
  ==============================================================================

    LF.cpp
    Created: 27 Nov 2021 12:27:07am
    Author:  ryand

  ==============================================================================
*/

#include "LF.h"

juce::Typeface::Ptr LF::s_CourierTypeface;
juce::Typeface::Ptr LF::s_CutiveTypeface;
juce::Typeface::Ptr LF::s_JetbrainsMonoTypeface;
juce::Typeface::Ptr LF::s_SpaceMonoTypeface;

bool LF::s_ResourcesAcquired;

juce::Font LF::getCutive(float height)
{
    if (!s_ResourcesAcquired)
    {
        acquireResources();
    }

    return juce::Font(s_CutiveTypeface).withHeight(height);
}

juce::Font LF::getCourier(float height)
{
    if (!s_ResourcesAcquired)
    {
        acquireResources();
    }

    return juce::Font(s_CourierTypeface).withHeight(height);
}

juce::Font LF::getCourierBold(float height)
{
    if (!s_ResourcesAcquired)
    {
        acquireResources();
    }

    return juce::Font(s_CourierTypeface).withHeight(height);
}

juce::Font LF::getCourierItalic(float height)
{
    if (!s_ResourcesAcquired)
    {
        acquireResources();
    }

    return juce::Font(s_CourierTypeface).withHeight(height);
}

juce::Font LF::getCourierBoldItalic(float height)
{
    if (!s_ResourcesAcquired)
    {
        acquireResources();
    }

    return juce::Font(s_CourierTypeface).withHeight(height);
}

juce::Font LF::getJetBrainsMono(float height)
{
    if (!s_ResourcesAcquired)
    {
        acquireResources();
    }

    return juce::Font(s_JetbrainsMonoTypeface).withHeight(height);
}

juce::Font LF::getSpaceMono(float height)
{
    if (!s_ResourcesAcquired)
    {
        acquireResources();
    }

    return juce::Font(s_SpaceMonoTypeface).withHeight(height);
}

void LF::acquireResources()
{
    s_CourierTypeface = juce::Typeface::createSystemTypefaceFor(BinaryData::CourierPrimeRegular_ttf, BinaryData::CourierPrimeRegular_ttfSize);
    s_CutiveTypeface = juce::Typeface::createSystemTypefaceFor(BinaryData::CutiveMonoRegular_ttf, BinaryData::CutiveMonoRegular_ttfSize);
    s_JetbrainsMonoTypeface = juce::Typeface::createSystemTypefaceFor(BinaryData::JetBrainsMonoRegular_ttf, BinaryData::JetBrainsMonoRegular_ttfSize);
    s_SpaceMonoTypeface = juce::Typeface::createSystemTypefaceFor(BinaryData::SpaceMonoRegular_ttf, BinaryData::SpaceMonoRegular_ttfSize);
}

void LF::releaseResources()
{
    s_CourierTypeface.reset();
    s_CutiveTypeface.reset();
    s_JetbrainsMonoTypeface.reset();
    s_SpaceMonoTypeface.reset();
}
