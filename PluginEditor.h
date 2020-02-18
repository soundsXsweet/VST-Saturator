
#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"

	//Most of this has to do with the slider interface, as well as initializing a multi-mode DSP filter

class SaturatorAudioProcessorEditor :
	public
	AudioProcessorEditor,
	private
	ComboBox::Listener,
	Slider::Listener
{
public:
	SaturatorAudioProcessorEditor(SaturatorAudioProcessor&);
	~SaturatorAudioProcessorEditor();

	void paint(Graphics&) override;
	void resized() override;

private:
	void comboBoxChanged(ComboBox* comboBoxThatHasChanged) override;
	void sliderValueChanged(Slider* sliderThatHasChanged) override;

	SaturatorAudioProcessor& processor;
	ComboBox disChoice;
	Slider Threshold;
	Slider Mix;

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(SaturatorAudioProcessorEditor)
};