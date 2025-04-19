//**************************************************************************************
//2x8 Multimple Module for VCV Rack by Autodafe http://www.autodafe.net
//
//**************************************************************************************

#include "plugin.hpp"


struct Multiple28 : Module{
	enum ParamIds {
		
		NUM_PARAMS
	};
	enum InputIds {
		INPUT1,
		INPUT2,
		NUM_INPUTS
	};
	enum OutputIds {
		OUT11,
		OUT12,
		OUT13,
		OUT14,
		OUT15,
		OUT16,
		OUT17,
		OUT18,
		OUT21,
		OUT22,
		OUT23,
		OUT24,
		OUT25,
		OUT26,
		OUT27,
		OUT28,
		NUM_OUTPUTS
	};

	

	Multiple28();
	void process(const ProcessArgs &args);
};


Multiple28::Multiple28() {
config(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS);

	//params.resize(NUM_PARAMS);
	//inputs.resize(NUM_INPUTS);
	//outputs.resize(NUM_OUTPUTS);
}


void Multiple28::process(const ProcessArgs &args) {
	
	float IN1 = inputs[INPUT1].getVoltage();
	float IN2 = inputs[INPUT2].getVoltage();

	// Set outputs
	//first column
	if (outputs[OUT11].isConnected()) {
		outputs[OUT11].setVoltage(IN1);
	}
	
	if (outputs[OUT12].isConnected()) {
		outputs[OUT12].setVoltage(IN1);
	}

	if (outputs[OUT13].isConnected()) {
		outputs[OUT13].setVoltage(IN1);
	}

	if (outputs[OUT14].isConnected()) {
		outputs[OUT14].setVoltage(IN1);
	}

	if (outputs[OUT15].isConnected()) {
		outputs[OUT15].setVoltage(IN1);
	}

	if (outputs[OUT16].isConnected()) {
		outputs[OUT16].setVoltage(IN1);
	}

	if (outputs[OUT17].isConnected()) {
		outputs[OUT17].setVoltage(IN1);
	}

	if (outputs[OUT18].isConnected()) {
		outputs[OUT18].setVoltage(IN1);
	}


	//SECOND COLUMN
	if (outputs[OUT21].isConnected()) {
		outputs[OUT21].setVoltage(IN2);
	}

	if (outputs[OUT22].isConnected()) {
		outputs[OUT22].setVoltage(IN2);
	}

	if (outputs[OUT23].isConnected()) {
		outputs[OUT23].setVoltage(IN2);
	}

	if (outputs[OUT24].isConnected()) {
		outputs[OUT24].setVoltage(IN2);
	}

	if (outputs[OUT25].isConnected()) {
		outputs[OUT25].setVoltage(IN2);
	}

	if (outputs[OUT26].isConnected()) {
		outputs[OUT26].setVoltage(IN2);
	}

	if (outputs[OUT27].isConnected()) {
		outputs[OUT27].setVoltage(IN2);
	}

	if (outputs[OUT28].isConnected()) {
		outputs[OUT28].setVoltage(IN2);
	}

	



	
}


struct Multiple28Widget : ModuleWidget {
	Multiple28Widget(Multiple28 *module);
};

	Multiple28Widget::Multiple28Widget(Multiple28 *module) {
		setModule(module);
	box.size = Vec(15*6, 380);

	{
		SvgPanel *panel = new SvgPanel();
		panel->box.size = box.size;
		panel->setBackground(APP->window->loadSvg(asset::plugin(pluginInstance, "res/Multiple28.svg")));
		addChild(panel);
	}

	addChild(createWidget<ScrewSilver>(Vec(5, 0)));
	addChild(createWidget<ScrewSilver>(Vec(5, 365)));
	addChild(createWidget<ScrewSilver>(Vec(70, 0)));
	addChild(createWidget<ScrewSilver>(Vec(70, 365)));

	

	addInput(createInput<PJ3410Port>(Vec(10, 20), module, Multiple28::INPUT1));
	addInput(createInput<PJ3410Port>(Vec(50, 20), module, Multiple28::INPUT2));
	
	addOutput(createOutput<PJ3410Port>(Vec(10, 60), module, Multiple28::OUT11));
	addOutput(createOutput<PJ3410Port>(Vec(10, 95), module, Multiple28::OUT12));
	addOutput(createOutput<PJ3410Port>(Vec(10, 130), module, Multiple28::OUT13));
	addOutput(createOutput<PJ3410Port>(Vec(10, 165), module, Multiple28::OUT14));
	addOutput(createOutput<PJ3410Port>(Vec(10, 200), module, Multiple28::OUT15));
	addOutput(createOutput<PJ3410Port>(Vec(10, 235), module, Multiple28::OUT16));
	addOutput(createOutput<PJ3410Port>(Vec(10, 270), module, Multiple28::OUT17));
	addOutput(createOutput<PJ3410Port>(Vec(10, 305), module, Multiple28::OUT18));

	addOutput(createOutput<PJ3410Port>(Vec(50, 60), module, Multiple28::OUT21));
	addOutput(createOutput<PJ3410Port>(Vec(50, 95), module, Multiple28::OUT22));
	addOutput(createOutput<PJ3410Port>(Vec(50, 130), module, Multiple28::OUT23));
	addOutput(createOutput<PJ3410Port>(Vec(50, 165), module, Multiple28::OUT24));
	addOutput(createOutput<PJ3410Port>(Vec(50, 200), module, Multiple28::OUT25));
	addOutput(createOutput<PJ3410Port>(Vec(50, 235), module, Multiple28::OUT26));
	addOutput(createOutput<PJ3410Port>(Vec(50, 270), module, Multiple28::OUT27));
	addOutput(createOutput<PJ3410Port>(Vec(50, 305), module, Multiple28::OUT28));

	
}

Model *modelMultiple28 = createModel<Multiple28, Multiple28Widget>("Multiple28");

