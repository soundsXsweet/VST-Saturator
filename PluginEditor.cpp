#include "PluginProcessor.h"
#include "PluginEditor.h"

SaturatorAudioProcessorEditor::SaturatorAudioProcessorEditor(SaturatorAudioProcessor& p)
	: AudioProcessorEditor(&p), processor(p) {


	//Setting our UI Bounds, as well as making sure it always starts up on a blank selection
	setSize(350, 350);

	addAndMakeVisible(&disChoice);
	disChoice.addItem(" ", 1);
	disChoice.addItem("Saturation", 2);
	disChoice.addItem("Half-Wave Rect", 3);
	disChoice.setSelectedId(1);
	disChoice.addListener(this);

	addAndMakeVisible(&Threshold);
	Threshold.setRange(0.0f, 1.0f, 0.001);
	Threshold.addListener(this);

	addAndMakeVisible(&Mix);
	Mix.setRange(0.0f, 1.0f, 0.001);
	Mix.addListener(this);
}

SaturatorAudioProcessorEditor::~SaturatorAudioProcessorEditor() {
}

void SaturatorAudioProcessorEditor::paint(Graphics& g) {
	g.fillAll(getLookAndFeel().findColour(ResizableWindow::backgroundColourId));
}

void SaturatorAudioProcessorEditor::resized(){
	disChoice.setBounds(50, 50, 200, 50);
	Threshold.setBounds(50, 100, 200, 50);
	Mix.setBounds(50, 150, 200, 50);
}

void SaturatorAudioProcessorEditor::comboBoxChanged(ComboBox* comboBoxThatWasChanged) {
	processor.menuChoice = comboBoxThatWasChanged->getSelectedId();
}


void SaturatorAudioProcessorEditor::sliderValueChanged(Slider* slider) {
	if (&Mix == slider) {
		processor.mix = Mix.getValue();
	}

	if (&Threshold == slider) {
		processor.thresh = Threshold.getValue();
	}
}

