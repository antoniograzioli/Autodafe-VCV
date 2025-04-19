//**************************************************************************************
//Waves Module for VCV Rack by Autodafe http://www.autodafe.net
//
//Based on code taken from the Fundamentals plugins by Andrew Belt http://www.vcvrack.com
//And part of code on musicdsp.org: http://musicdsp.org/showArchiveComment.php?ArchiveID=78
//**************************************************************************************


#include "Autodafe.hpp"
#include <stdlib.h>
#include "dsp/digital.hpp"
#include "dsp/functions.hpp"

#include "stk/include/BlitSquare.h"







using namespace stk;


struct SquareVCOModel : Module{
	enum ParamIds {
	
		PARAM_FREQ,
		PARAM_FINE,
		PARAM_FREQ_CV,
		PARAM_SQUARE_HARM,
		PARAM_VOL,
		PARAM_TAB,

		
			NUM_PARAMS
	};
	enum InputIds {
		INPUT_FREQ_CV,
		INPUT_HARM_CV,
	
		NUM_INPUTS
	};
	enum OutputIds {
	
		OUT_SQUARE,
	

		NUM_OUTPUTS
	};





	SquareVCOModel();


float gSampleRate;
float oldSampleRate;
float h;
int harmonics;

	


	BlitSquare *waveSquare = new BlitSquare(5.0);
	








 

	void step();
};
    




SquareVCOModel::SquareVCOModel() {
	params.resize(NUM_PARAMS);
	inputs.resize(NUM_INPUTS);
	outputs.resize(NUM_OUTPUTS);




}










void SquareVCOModel::step() {

 gSampleRate=engineGetSampleRate();

	float pitchFine = 3.0 * quadraticBipolar(params[PARAM_FINE].value);
	float pitchCv = 12.0 * inputs[INPUT_FREQ_CV].value * params[PARAM_FREQ_CV].value;





if (!inputs[INPUT_HARM_CV].active){ harmonics = params[PARAM_SQUARE_HARM].value;}

else {harmonics = (inputs[INPUT_HARM_CV].value+1)* 3.3;}
	

	
	StkFloat   freq = params[PARAM_FREQ].value+ pitchCv+pitchFine;
	freq = 261.626 * powf(2.0, freq / 12.0);


if (gSampleRate!=oldSampleRate){waveSquare->setSampleRate(engineGetSampleRate());}
//waveSquare->setSampleRate(engineGetSampleRate());
	waveSquare->setFrequency(freq);
	waveSquare->setHarmonics(harmonics);



	waveSquare->tick();



	


outputs[OUT_SQUARE].value= waveSquare->lastOut() ;

outputs[OUT_SQUARE].value*=params[PARAM_VOL].value*1.5*5;

oldSampleRate=engineGetSampleRate();


}

 


SquareVCOModelWidget::SquareVCOModelWidget() {
	SquareVCOModel *module = new SquareVCOModel();
	setModule(module);
	box.size = Vec(15 * 10 ,380); 

	{
		SVGPanel *panel = new SVGPanel();
		panel->box.size = box.size;
		
        panel->setBackground(SVG::load(assetPlugin(plugin, "res/SQUAREVCO.svg")));
		addChild(panel);
 
	} 
 
	addChild(createScrew<ScrewSilver>(Vec(1, 0)));
	addChild(createScrew<ScrewSilver>(Vec(box.size.x - 20, 0)));
	addChild(createScrew<ScrewSilver>(Vec(1, 365)));
	addChild(createScrew<ScrewSilver>(Vec(box.size.x - 20, 365)));



	addParam(createParam<AutodafeKnobRedBig>(Vec(18, 50), module, SquareVCOModel::PARAM_FREQ, -50.0, 0.0, -25.0));
	addParam(createParam<AutodafeKnobRed>(Vec(25, 120), module, SquareVCOModel::PARAM_FINE, -1.0, 1.0, 0.0));


	addParam(createParam<AutodafeKnobRed>(Vec(25, 190), module, SquareVCOModel::PARAM_FREQ_CV, -1, 1, 0));
	addInput(createInput<PJ301MPort>(Vec(90, 195), module, SquareVCOModel::INPUT_FREQ_CV));


	addParam(createParam<AutodafeKnobRed>(Vec(25, 260), module, SquareVCOModel::PARAM_SQUARE_HARM, 1, 33.0, 33.0));
	addInput(createInput<PJ301MPort>(Vec(90, 265), module, SquareVCOModel::INPUT_HARM_CV));

	addParam(createParam<AutodafeKnobRed>(Vec(85, 120 ), module, SquareVCOModel::PARAM_VOL, 0.0, 1, 1));
   
	addOutput(createOutput<PJ301MPort>(Vec(90, 65), module, SquareVCOModel::OUT_SQUARE));
	
}
