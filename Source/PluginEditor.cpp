/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
Lecture4_5_Delay_EffectAudioProcessorEditor::Lecture4_5_Delay_EffectAudioProcessorEditor (Lecture4_5_Delay_EffectAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (400, 300);
}

Lecture4_5_Delay_EffectAudioProcessorEditor::~Lecture4_5_Delay_EffectAudioProcessorEditor()
{
}

//==============================================================================
void Lecture4_5_Delay_EffectAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.setColour (juce::Colours::white);
    g.setFont (juce::FontOptions (15.0f));
    g.drawFittedText ("Hello World!", getLocalBounds(), juce::Justification::centred, 1);
}

void Lecture4_5_Delay_EffectAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
}
