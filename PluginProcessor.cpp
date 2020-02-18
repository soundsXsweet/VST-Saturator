#include "PluginProcessor.h"
#include "PluginEditor.h"

SaturatorAudioProcessor::SaturatorAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
    : AudioProcessor(BusesProperties()
#if ! JucePlugin_IsMidiEffect
#if ! JucePlugin_IsSynth

        //VST3 I/O initialization

        .withInput("Input", AudioChannelSet::stereo(), true)
#endif
        .withOutput("Output", AudioChannelSet::stereo(), true)
#endif
    )
#endif 
{
}

SaturatorAudioProcessor::~SaturatorAudioProcessor() {
}

const String SaturatorAudioProcessor::getName() const {
    return JucePlugin_Name;
}

bool SaturatorAudioProcessor::acceptsMidi() const {
#if JucePlugin_WantsMidiInput
    return true;
#else
    return false;
#endif
}

bool SaturatorAudioProcessor::producesMidi() const {
#if JucePlugin_ProducesMidiOutput
    return true;
#else
    return false;
#endif
}

bool SaturatorAudioProcessor::isMidiEffect() const {
#if JucePlugin_IsMidiEffect
    return true;
#else
    return false;
#endif
}

double SaturatorAudioProcessor::getTailLengthSeconds() const {
    return 0.0;
}

int SaturatorAudioProcessor::getNumPrograms() {
    return 1;
}

int SaturatorAudioProcessor::getCurrentProgram() {
    return 0;
}

void SaturatorAudioProcessor::setCurrentProgram(int index) {
}

const String SaturatorAudioProcessor::getProgramName(int index) {
    return {
    };
}

void SaturatorAudioProcessor::changeProgramName(int index, const String& newName) {
}

void SaturatorAudioProcessor::prepareToPlay(double sampleRate, int samplesPerBlock) {
}

void SaturatorAudioProcessor::releaseResources() {
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool SaturatorAudioProcessor::isBusesLayoutSupported(const BusesLayout& layouts) const {
#if JucePlugin_IsMidiEffect
    ignoreUnused(layouts);
    return true;
#else
    if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
        && layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
        return false;

#if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
#endif

    return true;
#endif
}
#endif

void SaturatorAudioProcessor::processBlock(AudioBuffer<float>& buffer, MidiBuffer& midiMessages) {
    for (int channel = 0; channel < buffer.getNumChannels(); ++channel) {
        auto* channelData = buffer.getWritePointer(channel);

        for (int i = 0; i < buffer.getNumSamples(); ++i) {
            auto input = channelData[i];
            auto cleanOut = channelData[i];

                //Having a default blank slot requires having some kind of 
                //processing, even if it will not be used. This is an example
                //of a crude clipping distortion. This style of plugin is not
                //very desirable, hence why it's being used as a placeholder 
                //here.
                if (menuChoice == 1){
                    if (input > thresh) {
                    input = thresh;
                    }
                else if (input < -thresh) {
                    input = -thresh;
                    }
                else {
                    input = input;
                    }
                }

                //Saturation Algorithm
                if (menuChoice == 2) {
                    if (input > thresh) {
                    input = 1.0f - expf(-input);
                    }
                else {
                    input = -1.0f + expf(input);
                    }
                }

                //Half-Wave Digital Diode Recitfier
            if (menuChoice == 3) {
                if (input > thresh) {
                    input = input;
                    }
                else {
                    input = 0;
                    }
                }
                channelData[i] = ((1 - mix) * cleanOut) + (mix * input);
            }
    }
}

bool SaturatorAudioProcessor::hasEditor() const {
    return true;
}

AudioProcessorEditor* SaturatorAudioProcessor::createEditor() {
    return new SaturatorAudioProcessorEditor(*this);
}

void SaturatorAudioProcessor::getStateInformation(MemoryBlock& destData) {
}

void SaturatorAudioProcessor::setStateInformation(const void* data, int sizeInBytes) {
}

AudioProcessor* JUCE_CALLTYPE createPluginFilter() {
    return new SaturatorAudioProcessor();
}