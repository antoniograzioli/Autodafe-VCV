//**************************************************************************************
//1x8 Multimple Module for VCV Rack by Autodafe http://www.autodafe.net
//
//**************************************************************************************

#include "plugin.hpp"

struct Multiple18 : Module{
	enum ParamIds {	
		NUM_PARAMS
	};
	enum InputIds {
		INPUT1,
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
		NUM_OUTPUTS
	};

	
	Multiple18();
	void process(const ProcessArgs &args);
};


Multiple18::Multiple18() {
	config(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS);
	//params.resize(NUM_PARAMS);
	//inputs.resize(NUM_INPUTS);
	//outputs.resize(NUM_OUTPUTS);
}


void Multiple18::process(const ProcessArgs &args) {
	
	float IN1 = inputs[INPUT1].getVoltage();
	

	// Set outputs
	if (outputs[OUT11].isConnected()) {
		outputs[OUT11].setVoltage(IN1);
	}
	
	if (outputs[OUT12].isConnected()) {
		outputs[OUT12].setVoltage(IN1);
	}

	if (outputs[OUT13].isConnected()) {
		outputs[OUT13].value= IN1;
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


	
}


struct Multiple18Widget : ModuleWidget {
	Multiple18Widget(Multiple18 *module);
};

	Multiple18Widget::Multiple18Widget(Multiple18 *module) {
		setModule(module);




	box.size = Vec(15*3, 380);

	{
		SvgPanel *panel = new SvgPanel();
		panel->box.size = box.size;
		panel->setBackground(APP->window->loadSvg(asset::plugin(pluginInstance, "res/Multiple18.svg")));
		addChild(panel);
	}

	addChild(createWidget<ScrewSilver>(Vec(1, 0)));
	addChild(createWidget<ScrewSilver>(Vec(1, 365)));
	
	addInput(createInput<PJ3410Port>(Vec(10, 20), module, Multiple18::INPUT1));
	
	addOutput(createOutput<PJ3410Port>(Vec(10, 60), module, Multiple18::OUT11));
	addOutput(createOutput<PJ3410Port>(Vec(10, 95), module, Multiple18::OUT12));
	addOutput(createOutput<PJ3410Port>(Vec(10, 130), module, Multiple18::OUT13));
	addOutput(createOutput<PJ3410Port>(Vec(10, 165), module, Multiple18::OUT14));
	addOutput(createOutput<PJ3410Port>(Vec(10, 200), module, Multiple18::OUT15));
	addOutput(createOutput<PJ3410Port>(Vec(10, 235), module, Multiple18::OUT16));
	addOutput(createOutput<PJ3410Port>(Vec(10, 270), module, Multiple18::OUT17));
	addOutput(createOutput<PJ3410Port>(Vec(10, 305), module, Multiple18::OUT18));

} 

Model *modelMultiple18 = createModel<Multiple18, Multiple18Widget>("Multiple18");



