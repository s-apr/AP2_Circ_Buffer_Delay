/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
Lecture4_5_Delay_EffectAudioProcessor::Lecture4_5_Delay_EffectAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       )
#endif
{
    addParameter(mDelayTime = new juce::AudioParameterFloat("delayTime",
        "Delay Time",
        0.0f, //min
        1.00f, //max
        0.5f)); //default
                                                                   
    addParameter(mMix = new juce::AudioParameterFloat("mix",
        "Mix",
        0.0f, //min
        1.00f, //max
        0.5f)); //default

    addParameter(mFeedback = new juce::AudioParameterFloat("feedback",
        "Feedback",
        0.0f, //min
        1.00f, //max
        0.0f)); //default
        
}

Lecture4_5_Delay_EffectAudioProcessor::~Lecture4_5_Delay_EffectAudioProcessor()
{
}

//==============================================================================
const juce::String Lecture4_5_Delay_EffectAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool Lecture4_5_Delay_EffectAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool Lecture4_5_Delay_EffectAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool Lecture4_5_Delay_EffectAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double Lecture4_5_Delay_EffectAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int Lecture4_5_Delay_EffectAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int Lecture4_5_Delay_EffectAudioProcessor::getCurrentProgram()
{
    return 0;
}

void Lecture4_5_Delay_EffectAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String Lecture4_5_Delay_EffectAudioProcessor::getProgramName (int index)
{
    return {};
}

void Lecture4_5_Delay_EffectAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void Lecture4_5_Delay_EffectAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..

    //store sample rate
    mSampleRate = sampleRate;

    //maximum delay
    mMaxDelaySamples = static_cast<int>(sampleRate * 2.0);

    //initialise a delay line for each input channel
    mDelayLines.clear();
    for (int i = 0; i << getTotalNumInputChannels(); i++)
    {
        //for each channel
            //create a 2 second buffer
                //with position 0
        mDelayLines.push_back(RingBuffer(mMaxDelaySamples, 0));
    }

}

void Lecture4_5_Delay_EffectAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.

    mDelayLines.clear();

}

#ifndef JucePlugin_PreferredChannelConfigurations
bool Lecture4_5_Delay_EffectAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void Lecture4_5_Delay_EffectAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    // In case we have more outputs than inputs, this code clears any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    // This is here to avoid people getting screaming feedback
    // when they first compile a plugin, but obviously you don't need to keep
    // this code if your algorithm always overwrites all the output channels.
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    // This is the place where you'd normally do the guts of your plugin's
    // audio processing...
    // Make sure to reset the state if your inner loop is processing
    // the samples and the outer loop is handling the channels.
    // Alternatively, you can process the samples with the channels
    // interleaved by keeping the same state.
    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
        auto* channelData = buffer.getWritePointer (channel);

        // ..do something to the data...
    }
}

//==============================================================================
bool Lecture4_5_Delay_EffectAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* Lecture4_5_Delay_EffectAudioProcessor::createEditor()
{
    return new juce::GenericAudioProcessorEditor (*this);
}

//==============================================================================
void Lecture4_5_Delay_EffectAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void Lecture4_5_Delay_EffectAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new Lecture4_5_Delay_EffectAudioProcessor();
}
