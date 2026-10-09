

#include "plugin.hpp"
#include <stdlib.h>





struct MultiModeFilter : Module{





	enum ParamIds {
		FREQ_PARAM,
		Q_PARAM,
		RES_PARAM,
		FREQ_CV_PARAM,
		FREQ_CV_PARAM2,
		DRIVE_PARAM,
		NUM_PARAMS
	};
	enum InputIds {
		FREQ_INPUT,
		FREQ_INPUT2,
		RES_INPUT,
		DRIVE_INPUT,
		INPUT,
		NUM_INPUTS
	};
	enum OutputIds {
		OUTLPF,
		OUTHPF,
		OUTBPF,
		OUTNPF,
		NUM_OUTPUTS
	};





	MultiModeFilter();
VAStateVariableFilter lpFilter;
VAStateVariableFilter hpFilter;
VAStateVariableFilter bpFilter;
VAStateVariableFilter npFilter;


	void process(const ProcessArgs &args);
};









float minfreq = 15.0f;
float maxfreq = 12000.0f;



MultiModeFilter::MultiModeFilter() {
config(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS);


		configParam(MultiModeFilter::FREQ_PARAM, minfreq, maxfreq, maxfreq, "");
configParam(MultiModeFilter::RES_PARAM, 0.0, 0.99, 0.0, "");
configParam(MultiModeFilter::FREQ_CV_PARAM, -1.0, 1.0, 0.0, "");
configParam(MultiModeFilter::FREQ_CV_PARAM2, -1.0, 1.0, 0.0, "");
configParam(MultiModeFilter::DRIVE_PARAM, 0.0, 1.0, 0.0, "");



}

float outLP=0.0f;;
float outHP=0.0f;;
float outBP=0.0f;;
float outNP=0.0f;;










void MultiModeFilter::process(const ProcessArgs &args) {
	
	

	

	float input = inputs[INPUT].getVoltage() / 5.0f;

	float drive = params[DRIVE_PARAM].getValue() + inputs[DRIVE_INPUT].getVoltage() / 10.0f;
	float gain = powf(100.0f, drive);
	input *= gain;
	// Add -60dB noise to bootstrap self-oscillation
	input += 1.0e-6 * (2.0f*random::uniform() - 1.0f)*1000.0f;

	// Set resonance
	float res = clamp(params[RES_PARAM].getValue() + clamp(inputs[RES_INPUT].getVoltage(), 0.0f,1.0f), 0.0f,1.0f);

	

	float cutoffcv =  400.0f*params[FREQ_CV_PARAM].getValue() * inputs[FREQ_INPUT].getVoltage()+ 400.0f*inputs[FREQ_INPUT2].getVoltage() *params[FREQ_CV_PARAM2].getValue() ;
	
	float cutoff = params[FREQ_PARAM].getValue() + cutoffcv;

	cutoff = clamp(cutoff, minfreq, maxfreq);
	

 

	lpFilter.setFilterType(0);
	hpFilter.setFilterType(2);
	bpFilter.setFilterType(1);
	npFilter.setFilterType(5);

	
lpFilter.setCutoffFreq(cutoff);
hpFilter.setCutoffFreq(cutoff); 
bpFilter.setCutoffFreq(cutoff);
npFilter.setCutoffFreq(cutoff);


lpFilter.setResonance(res);
hpFilter.setResonance(res);
bpFilter.setResonance(res);
npFilter.setResonance(res);





lpFilter.setSampleRate(44100.0f);
hpFilter.setSampleRate(44100.0f);
bpFilter.setSampleRate(44100.0f);
npFilter.setSampleRate(44100.0f);





outLP = lpFilter.processAudioSample(input,1.0f);
outHP = hpFilter.processAudioSample(input,1.0f);
outBP = bpFilter.processAudioSample(input,1.0f);
outNP = npFilter.processAudioSample(input,1.0f);




	outputs[OUTLPF].setVoltage(outLP*5.0f);
	outputs[OUTHPF].setVoltage(outHP*5.0f);
	outputs[OUTBPF].setVoltage(outBP*5.0f);
	outputs[OUTNPF].setVoltage(outNP*5.0f);

	



}

struct MultiModeFilterWidget : ModuleWidget {
	MultiModeFilterWidget(MultiModeFilter *module);
};

	MultiModeFilterWidget::MultiModeFilterWidget(MultiModeFilter *module) {
		setModule(module);




	box.size = Vec(15 * 13, 380);

	{
		SvgPanel *panel = new SvgPanel();
		panel->box.size = box.size;
		panel->setBackground(APP->window->loadSvg(asset::plugin(pluginInstance, "res/MultiModeFilter.svg")));


		addChild(panel);
	}

	addChild(createWidget<ScrewSilver>(Vec(15, 0)));
	addChild(createWidget<ScrewSilver>(Vec(box.size.x - 30, 0)));
	addChild(createWidget<ScrewSilver>(Vec(15, 365)));
	addChild(createWidget<ScrewSilver>(Vec(box.size.x - 30, 365)));

	addParam(createParam<AutodafeKnobBlueBig>(Vec(68, 61), module, MultiModeFilter::FREQ_PARAM));
	
	addParam(createParam<AutodafeKnobBlue>(Vec(111, 143), module, MultiModeFilter::RES_PARAM));
	addParam(createParam<AutodafeKnobBlue>(Vec(43, 143), module, MultiModeFilter::FREQ_CV_PARAM));

	addParam(createParam<AutodafeKnobBlue>(Vec(43, 208), module, MultiModeFilter::FREQ_CV_PARAM2));


	addParam(createParam<AutodafeKnobBlue>(Vec(111, 208), module, MultiModeFilter::DRIVE_PARAM));





	addInput(createInput<PJ301MPort>(Vec(10, 276), module, MultiModeFilter::FREQ_INPUT));
	addInput(createInput<PJ301MPort>(Vec(121, 276), module, MultiModeFilter::FREQ_INPUT2));
	addInput(createInput<PJ301MPort>(Vec(48, 276), module, MultiModeFilter::RES_INPUT));
	addInput(createInput<PJ301MPort>(Vec(85, 276), module, MultiModeFilter::DRIVE_INPUT));

	addInput(createInput<PJ301MPort>(Vec(10, 320), module, MultiModeFilter::INPUT));

	addOutput(createOutput<PJ301MPort>(Vec(48, 320),module, MultiModeFilter::OUTLPF));
	addOutput(createOutput<PJ301MPort>(Vec(85, 320),module, MultiModeFilter::OUTHPF));
	addOutput(createOutput<PJ301MPort>(Vec(122, 320),module, MultiModeFilter::OUTBPF));
	addOutput(createOutput<PJ301MPort>(Vec(159, 320),module, MultiModeFilter::OUTNPF));

}

Model *modelMultiModeFilter = createModel<MultiModeFilter, MultiModeFilterWidget>("MultiModeFilter");



