/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
Guitar_ampAudioProcessor::Guitar_ampAudioProcessor()
    : parameters(*this, nullptr, juce::Identifier("GuitarAmp"),
        {
            //put parameters that require automation here
        })
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
    Input.referTo(parameters.state.getPropertyAsValue("Input", nullptr, true));
    Master.referTo(parameters.state.getPropertyAsValue("Master", nullptr, true));
    Bass.referTo(parameters.state.getPropertyAsValue("Bass", nullptr, true));
    Mid.referTo(parameters.state.getPropertyAsValue("Mid", nullptr, true));
    Treble.referTo(parameters.state.getPropertyAsValue("Treble", nullptr, true));
    Bias.referTo(parameters.state.getPropertyAsValue("Bias", nullptr, true));
    Ampli.referTo(parameters.state.getPropertyAsValue("Ampli", nullptr, true));
    AmpState.referTo(parameters.state.getPropertyAsValue("AmpState", nullptr, true));
    CabState.referTo(parameters.state.getPropertyAsValue("CabState", nullptr, true));
    FilterState.referTo(parameters.state.getPropertyAsValue("FilterState", nullptr, true));
    TubeState.referTo(parameters.state.getPropertyAsValue("TubeState", nullptr, true));

}

Guitar_ampAudioProcessor::~Guitar_ampAudioProcessor()
{
}

//==============================================================================
const juce::String Guitar_ampAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool Guitar_ampAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool Guitar_ampAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool Guitar_ampAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double Guitar_ampAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int Guitar_ampAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int Guitar_ampAudioProcessor::getCurrentProgram()
{
    return 0;
}

void Guitar_ampAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String Guitar_ampAudioProcessor::getProgramName (int index)
{
    return {};
}

void Guitar_ampAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void Guitar_ampAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
}

void Guitar_ampAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool Guitar_ampAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
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

void Guitar_ampAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;

    // mono channel
    auto* inputData = buffer.getReadPointer(0);
    auto* outputData = buffer.getWritePointer(0);

    for (int sample = 0; sample < buffer.getNumSamples(); sample++)
    {
        outputData[sample] = ampSim.processing(inputData[sample]);
    }
}

//==============================================================================
bool Guitar_ampAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* Guitar_ampAudioProcessor::createEditor()
{
    return new Guitar_ampAudioProcessorEditor (*this);
}

//==============================================================================
void Guitar_ampAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
    auto state = parameters.copyState();
    std::unique_ptr<juce::XmlElement> xml(state.createXml());
    copyXmlToBinary(*xml, destData);
}

void Guitar_ampAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
    std::unique_ptr<juce::XmlElement> xmlState(getXmlFromBinary(data, sizeInBytes));

    if (xmlState != nullptr && xmlState->hasTagName(parameters.state.getType()))
    {
        parameters.replaceState(juce::ValueTree::fromXml(*xmlState));

        // Powi¹zanie w³aœciwoœci po przywróceniu drzewa
        Input.referTo(parameters.state.getPropertyAsValue("Input", nullptr, true));
        Master.referTo(parameters.state.getPropertyAsValue("Master", nullptr, true));
        Bass.referTo(parameters.state.getPropertyAsValue("Bass", nullptr, true));
        Mid.referTo(parameters.state.getPropertyAsValue("Mid", nullptr, true));
        Treble.referTo(parameters.state.getPropertyAsValue("Treble", nullptr, true));
        Bias.referTo(parameters.state.getPropertyAsValue("Bias", nullptr, true));
        Ampli.referTo(parameters.state.getPropertyAsValue("Ampli", nullptr, true));
        AmpState.referTo(parameters.state.getPropertyAsValue("AmpState", nullptr, true));
        CabState.referTo(parameters.state.getPropertyAsValue("CabState", nullptr, true));
        FilterState.referTo(parameters.state.getPropertyAsValue("FilterState", nullptr, true));
        TubeState.referTo(parameters.state.getPropertyAsValue("TubeState", nullptr, true));

        // Odczytanie œcie¿ki z ValueTree
        if (Input.toString().isNotEmpty())
            ampSim.setInputVolume(static_cast<float>(Input.getValue()));

        if (Master.toString().isNotEmpty())
            ampSim.setMasterVolume(static_cast<float>(Master.getValue()));

        if (Bass.toString().isNotEmpty())
            ampSim.setBassVolume(static_cast<float>(Bass.getValue()));

        if (Mid.toString().isNotEmpty())
            ampSim.setMidVolume(static_cast<float>(Mid.getValue()));

        if (Treble.toString().isNotEmpty())
            ampSim.setTrebleVolume(static_cast<float>(Treble.getValue()));

        if (Bias.toString().isNotEmpty())
            ampSim.setBias(static_cast<float>(Bias.getValue()));

        if (Ampli.toString().isNotEmpty())
            ampSim.setAmp(static_cast<float>(Ampli.getValue()));

        if (AmpState.toString().isNotEmpty())
            ampSim.setAmpState(static_cast<int>(AmpState.getValue()));

        if (CabState.toString().isNotEmpty())
            ampSim.setCabState(static_cast<int>(CabState.getValue()));

        if (FilterState.toString().isNotEmpty())
            ampSim.setFilterState(static_cast<int>(FilterState.getValue()));

        if (TubeState.toString().isNotEmpty())
            ampSim.setTubeState(static_cast<int>(TubeState.getValue()));
    }
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new Guitar_ampAudioProcessor();
}
