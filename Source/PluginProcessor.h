/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/**
*/
class RingBuffer {
public:
    RingBuffer(int size, int write) {
        mBuffer = std::vector<double>(size, 0);
        mPos = write;
    }
    double read(int delay) {
        delay = std::min(delay, (int)(mBuffer.size() - 1));
        int index = mPos - delay;
        if (index < 0)index += mBuffer.size();
        return mBuffer[index];
    }

    void write(double val) {
        mBuffer[mPos] = val;
        mPos = (mPos + 1) % mBuffer.size();
    }

    void reset(int size, int pos) {
        mBuffer = std::vector<double>(size, 0);
        mPos = pos;
    }

private:
    std::vector<double> mBuffer;
    int mPos;
};

class Lecture4_5_Delay_EffectAudioProcessor  : public juce::AudioProcessor
{
public:
    //==============================================================================
    Lecture4_5_Delay_EffectAudioProcessor();
    ~Lecture4_5_Delay_EffectAudioProcessor() override;

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    //==============================================================================
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;

    //==============================================================================
    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

private:

    juce::AudioParameterFloat* mDelayTime;
    juce::AudioParameterFloat* mMix;
    juce::AudioParameterFloat* mFeedback;

    std::vector<RingBuffer> mDelayLines;
    double mSampleRate = 44100.0;
    int mMaxDelaySamples = 0;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Lecture4_5_Delay_EffectAudioProcessor)
};
