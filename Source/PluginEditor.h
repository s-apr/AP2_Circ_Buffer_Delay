/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class Lecture4_5_Delay_EffectAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    Lecture4_5_Delay_EffectAudioProcessorEditor (Lecture4_5_Delay_EffectAudioProcessor&);
    ~Lecture4_5_Delay_EffectAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    Lecture4_5_Delay_EffectAudioProcessor& audioProcessor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Lecture4_5_Delay_EffectAudioProcessorEditor)
};
