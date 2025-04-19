//**************************************************************************************
//Reverb Module for VCV Rack by Autodafe http://www.autodafe.net
//
//Based on code taken from the Fundamentals plugins by Andrew Belt http://www.vcvrack.com
//And part of code on musicdsp.org: http://musicdsp.org/showArchiveComment.php?ArchiveID=78
//**************************************************************************************


#include "plugin.hpp"
#include <stdlib.h>



#include "stk/include/NRev.h"


using namespace stk;


struct ReverbFx : Module{




	enum ParamIds {
		PARAM_TIME,
		PARAM_DRY_WET,
		
			NUM_PARAMS
	};
	enum InputIds {
		
		INPUT,
		NUM_INPUTS
	};
	enum OutputIds {
		OUT,
		
		NUM_OUTPUTS
	};


	ReverbFx();

	  

	//Reverb *cho; 

	NRev *reverb = new NRev(); // OK

	



	void process(const ProcessArgs &args);
};





ReverbFx::ReverbFx() {

	config(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS);

		configParam(ReverbFx::PARAM_TIME, 0.01, 10, 0.01, "");
configParam(ReverbFx::PARAM_DRY_WET, 0, 1, 0, "");


	//params.resize(NUM_PARAMS);
	//inputs.resize(NUM_INPUTS);
	//outputs.resize(NUM_OUTPUTS);




}










void ReverbFx::process(const ProcessArgs &args) {

	
	StkFloat  time = params[PARAM_TIME].getValue();
	
	

	StkFloat  input = inputs[INPUT].getVoltage() / 5.0;


		reverb->setT60(time);
	
	
	reverb->tick(input, 0);
	//reverb->tick(input, 1);



	outputs[OUT].value= (input + reverb->lastOut(0)*params[PARAM_DRY_WET].getValue())* 5;
	//outputs[OUTR].value= (input +reverb->lastOut(1) *params[PARAM_DRY_WET].getValue())* 5;
	


}

struct ReverbFxWidget : ModuleWidget {
	ReverbFxWidget(ReverbFx *module);
};

	ReverbFxWidget::ReverbFxWidget(ReverbFx *module) {
		setModule(module);




	box.size = Vec(15 * 6, 380);

	{
		SvgPanel *panel = new SvgPanel();
		panel->box.size = box.size;
		
        panel->setBackground(APP->window->loadSvg(asset::plugin(pluginInstance, "res/Reverb.svg")));
		addChild(panel);
	}

	addChild(createWidget<ScrewSilver>(Vec(1, 0)));
	addChild(createWidget<ScrewSilver>(Vec(box.size.x - 20, 0)));
	addChild(createWidget<ScrewSilver>(Vec(1, 365)));
	addChild(createWidget<ScrewSilver>(Vec(box.size.x - 20, 365)));

		
	addParam(createParam<AutodafeKnobGreenBig>(Vec(20, 60), module, ReverbFx::PARAM_TIME));

	addParam(createParam<AutodafeKnobGreen>(Vec(27, 140), module, ReverbFx::PARAM_DRY_WET));

	

	addInput(createInput<PJ301MPort>(Vec(10, 320), module, ReverbFx::INPUT));
	addOutput(createOutput<PJ301MPort>(Vec(48, 320), module, ReverbFx::OUT));
	//addOutput(createOutput<PJ301MPort>(Vec(78, 320), module, ReverbFx::OUTR));
	
}

Model *modelReverbFx = createModel<ReverbFx, ReverbFxWidget>("ReverbFx");



