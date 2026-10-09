//**************************************************************************************
//FoldBack Distortion Module for VCV Rack by Autodafe http://www.autodafe.net
//
//Based on code taken from the Fundamentals plugins by Andrew Belt http://www.vcvrack.com
//And part of code on musicdsp.org: http://musicdsp.org/showArchiveComment.php?ArchiveID=203
//**************************************************************************************


#include "plugin.hpp"


struct FoldBack : Module {

	
	enum ParamIds {
		THRESHOLD_PARAM,
		ATTEN_PARAM,
		NUM_PARAMS
	};
	enum InputIds {
		
		INPUT,
		CV_THRESHOLD,
		NUM_INPUTS
	};
	enum OutputIds {
		OUTPUT,
		NUM_OUTPUTS
	};




	FoldBack();
	void process(const ProcessArgs &args);
};


FoldBack::FoldBack() {

	config(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS);

	configParam(FoldBack::THRESHOLD_PARAM, 0.1, 1.0, 1.0, "");
configParam(FoldBack::ATTEN_PARAM, -1.0, 1.0, 0.0, "");


	//params.resize(NUM_PARAMS);
	//inputs.resize(NUM_INPUTS);
	//outputs.resize(NUM_OUTPUTS);
}




float foldback(float in, float threshold)
{
	if (in>threshold || in<-threshold)
	{
		in = fabs(fabs(fmod(in - threshold, threshold * 4)) - threshold * 2) - threshold;
	}
	return in;
}





void FoldBack::process(const ProcessArgs &args) {
	
	float in = inputs[INPUT].getVoltage() / 5.0;
	float threshold = params[THRESHOLD_PARAM].getValue();
	float coeff = inputs[CV_THRESHOLD].getVoltage() * params[ATTEN_PARAM].getValue() / 5.0;



	outputs[OUTPUT].setVoltage(5.0* foldback(in, threshold+coeff));



	

}


struct FoldBackWidget : ModuleWidget {
	FoldBackWidget(FoldBack *module);
};

	FoldBackWidget::FoldBackWidget(FoldBack *module) {
		setModule(module);



	box.size = Vec(15 * 6, 380);

	{
		SvgPanel *panel = new SvgPanel();
		panel->box.size = box.size;
		
				panel->setBackground(APP->window->loadSvg(asset::plugin(pluginInstance, "res/FoldBack.svg")));
		addChild(panel);
	}

	addChild(createWidget<ScrewSilver>(Vec(5, 0)));
	addChild(createWidget<ScrewSilver>(Vec(box.size.x - 20, 0)));
	addChild(createWidget<ScrewSilver>(Vec(5, 365)));
	addChild(createWidget<ScrewSilver>(Vec(box.size.x - 20, 365)));

	addParam(createParam<AutodafeKnobGreenBig>(Vec(18, 61), module, FoldBack::THRESHOLD_PARAM));

	addInput(createInput<PJ301MPort>(Vec(32, 150), module, FoldBack::CV_THRESHOLD));

	addParam(createParam<AutodafeKnobGreen>(Vec(27, 190), module, FoldBack::ATTEN_PARAM));
		addInput(createInput<PJ301MPort>(Vec(10, 320), module, FoldBack::INPUT));

	addOutput(createOutput<PJ301MPort>(Vec(48, 320), module, FoldBack::OUTPUT));
	
}


Model *modelFoldBack = createModel<FoldBack, FoldBackWidget>("FoldBack");



