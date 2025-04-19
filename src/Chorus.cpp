//**************************************************************************************
//BitCrusher Module for VCV Rack by Autodafe http://www.autodafe.net
//
//Based on code taken from the Fundamentals plugins by Andrew Belt http://www.vcvrack.com
//And part of code on musicdsp.org: http://musicdsp.org/showArchiveComment.php?ArchiveID=78
//**************************************************************************************


#include "plugin.hpp"
#include <stdlib.h>



#include "stk/include/Chorus.h"


using namespace stk;


struct ChorusFx : Module{


	
	enum ParamIds {
		PARAM_RATE,
		PARAM_FEEDBACK,
		PARAM_DEPTH,
			NUM_PARAMS
	};
	enum InputIds {
		RATE_CV_IN,
		DEPTH_CV_IN,
		INPUT,
		NUM_INPUTS
	};
	enum OutputIds {
		OUT,
		NUM_OUTPUTS
	};


	ChorusFx();

	  

	//Chorus *cho; 

	Chorus *cho = new Chorus(1000); // OK

	



	void process(const ProcessArgs &args);
};





ChorusFx::ChorusFx() {
config(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS);
configParam(ChorusFx::PARAM_RATE, 0, 1, 0, "");
configParam(ChorusFx::PARAM_DEPTH, 0, 1, 0, "");
	
	//params.resize(NUM_PARAMS);
	//inputs.resize(NUM_INPUTS);
	//outputs.resize(NUM_OUTPUTS);




}










void ChorusFx::process(const ProcessArgs &args) {

	
	StkFloat  rate = params[PARAM_RATE].getValue();
	
	StkFloat depth = params[PARAM_DEPTH].getValue();

	StkFloat  input = inputs[INPUT].getVoltage() / 5.0;


		cho->setModFrequency(rate);
		cho->setModDepth (depth);
	
	cho->tick(input,0);



	outputs[OUT].value= cho->lastOut(0) * 5;
	


}



struct ChorusFxWidget : ModuleWidget {
	ChorusFxWidget(ChorusFx *module);
};








	ChorusFxWidget::ChorusFxWidget(ChorusFx *module) {
		setModule(module);



	box.size = Vec(15 * 6, 380);

	{
		SvgPanel *panel = new SvgPanel();
		panel->box.size = box.size;
		
        panel->setBackground(APP->window->loadSvg(asset::plugin(pluginInstance, "res/Chorus.svg")));
		addChild(panel);
	}

	addChild(createWidget<ScrewSilver>(Vec(1, 0)));
	addChild(createWidget<ScrewSilver>(Vec(box.size.x - 20, 0)));
	addChild(createWidget<ScrewSilver>(Vec(1, 365)));
	addChild(createWidget<ScrewSilver>(Vec(box.size.x - 20, 365)));

		
	addParam(createParam<AutodafeKnobGreenBig>(Vec(20, 60), module, ChorusFx::PARAM_RATE));

	

	addParam(createParam<AutodafeKnobGreen>(Vec(27, 140), module, ChorusFx::PARAM_DEPTH));

	addInput(createInput<PJ301MPort>(Vec(10, 320), module, ChorusFx::INPUT));
	addOutput(createOutput<PJ301MPort>(Vec(48, 320), module, ChorusFx::OUT));
	
}




Model *modelChorusFx = createModel<ChorusFx, ChorusFxWidget>("ChorusFx");
