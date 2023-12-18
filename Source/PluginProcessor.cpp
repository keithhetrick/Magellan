/*
 ==============================================================================
 
 PluginProcessor.cpp
 Created: 17 Dec 2023 11:59:07am
 Author:  Keith Hetrick
 
 ==============================================================================
 */

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
/**
 */
ExploraditoAudioProcessor::ExploraditoAudioProcessor()
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
}

ExploraditoAudioProcessor::~ExploraditoAudioProcessor()
{
}

//==============================================================================
const juce::String ExploraditoAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool ExploraditoAudioProcessor::acceptsMidi() const
{
#if JucePlugin_WantsMidiInput
    return true;
#else
    return false;
#endif
}

bool ExploraditoAudioProcessor::producesMidi() const
{
#if JucePlugin_ProducesMidiOutput
    return true;
#else
    return false;
#endif
}

bool ExploraditoAudioProcessor::isMidiEffect() const
{
#if JucePlugin_IsMidiEffect
    return true;
#else
    return false;
#endif
}

double ExploraditoAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int ExploraditoAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
    // so this should be at least 1, even if you're not really implementing programs.
}

int ExploraditoAudioProcessor::getCurrentProgram()
{
    return 0;
}

void ExploraditoAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String ExploraditoAudioProcessor::getProgramName (int index)
{
    return {};
}

void ExploraditoAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void ExploraditoAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
}

void ExploraditoAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool ExploraditoAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
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

void ExploraditoAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
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
        //        auto* channelData = buffer.getWritePointer (channel);
        
        // ..do something to the data...
    }
}

//==============================================================================
bool ExploraditoAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* ExploraditoAudioProcessor::createEditor()
{
    return new MagellanAudioProcessorEditor (*this);
}

//==============================================================================
void ExploraditoAudioProcessor::getStateInformation (juce::MemoryBlock& destData) {
    // Create an Xml element to save your data
    auto state = std::make_unique<juce::XmlElement>("MYPLUGINSETTINGS");
    
    // Store the size of the plugin window
    if (auto* editor = dynamic_cast<MagellanAudioProcessorEditor*>(getActiveEditor())) {
        state->setAttribute("UIWidth", editor->getWidth());
        state->setAttribute("UIHeight", editor->getHeight());
    }
    
    // ... Your existing code to store other parameters ...
    
    // Use this helper function to convert the Xml element into a binary blob
    copyXmlToBinary(*state, destData);
}

void ExploraditoAudioProcessor::setStateInformation (const void* data, int sizeInBytes) {
    // Use this helper function to retrieve the Xml element from the binary blob
    std::unique_ptr<juce::XmlElement> xmlState(getXmlFromBinary(data, sizeInBytes));
    
    if (xmlState.get() != nullptr) {
        // If we've got valid XML, use it to restore the plugin's state
        // ...
        
        // Restore the size of the plugin window
        if (xmlState->hasAttribute("UIWidth") && xmlState->hasAttribute("UIHeight")) {
            const int width = xmlState->getIntAttribute("UIWidth", 400); // Default width
            const int height = xmlState->getIntAttribute("UIHeight", 300); // Default height
            
            if (auto* editor = dynamic_cast<MagellanAudioProcessorEditor*>(getActiveEditor())) {
                editor->setSize(width, height);
            }
        }
    }
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new ExploraditoAudioProcessor();
}

