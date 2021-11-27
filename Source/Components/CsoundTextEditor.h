/*
  ==============================================================================

    CsoundTextEditor.h
    Created: 27 Nov 2021 2:52:34pm
    Author:  ryand

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

#include "LF.h"

namespace chirp
{
    namespace Components
    {
        class CsoundTextEditor : public juce::TextEditor
        {
        public:
            CsoundTextEditor();
        };
    }
}
