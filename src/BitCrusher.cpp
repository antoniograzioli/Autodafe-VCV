//**************************************************************************************
//BitCrusher Module for VCV Rack by Autodafe http://www.autodafe.net
//
//Based on code taken from the Fundamentals plugins by Andrew Belt http://www.vcvrack.com
//And part of code on musicdsp.org: http://musicdsp.org/showArchiveComment.php?ArchiveID=139
//**************************************************************************************

#include "plugin.hpp"

struct BitCrusher : Module {





	enum ParamIds {
		BITS_PARAM,
		RATE_PARAM,
		ATTEN_PARAM,
		NUM_PARAMS
	};
	enum InputIds {
		INPUT,
		CV_BITS,
		NUM_INPUTS
	};
	enum OutputIds {
		OUTPUT,
		NUM_OUTPUTS
	};


float y = 0, cnt = 0;
float decimate(float i, long int bits, float rate);

	BitCrusher();


	void process(const ProcessArgs &args);



};

BitCrusher::BitCrusher() {

config(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS);
	configParam(BitCrusher::BITS_PARAM, 0.2, 1.0, 1.0, "");
configParam(BitCrusher::RATE_PARAM, 0.2, 1.0,1.0, "");
configParam(BitCrusher::ATTEN_PARAM, -1.0, 1.0, 0.0, "");

	
	//params.resize(NUM_PARAMS);
	//inputs.resize(NUM_INPUTS);
	//outputs.resize(NUM_OUTPUTS);

	


}



float BitCrusher::decimate(float i, long int bits, float rate)
{



	long int m = 1 << (bits - 1);

	cnt += rate;
	if (cnt >= 1)
	{
		cnt -= 1;
		y = (long int)(i * m) / (float)m;
	}
	return y;
}



void BitCrusher::process(const ProcessArgs &args) {
	
	float in = inputs[INPUT].getVoltage() / 5.0;
	long int bits = params[BITS_PARAM].getValue() *16;
	float rate = params[RATE_PARAM].getValue() ;
	float coeff = inputs[CV_BITS].getVoltage()  * params[ATTEN_PARAM].getValue()  *8/ 5.0;
	
	outputs[OUTPUT].setVoltage(5.0* decimate(in, bits-coeff, rate));

}






struct BitCrusherWidget : ModuleWidget {
	BitCrusherWidget(BitCrusher *module);
};

	BitCrusherWidget::BitCrusherWidget(BitCrusher *module) {
		setModule(module);
	
	box.size = Vec(15 * 6, 380);

	{
		
		SvgPanel *panel = new SvgPanel();
		panel->box.size = box.size;
		
		

			panel->setBackground(APP->window->loadSvg(asset::plugin(pluginInstance, "res/BitCrusher.svg")));

		addChild(panel);
	}

	addChild(createWidget<ScrewSilver>(Vec(5, 0)));
	addChild(createWidget<ScrewSilver>(Vec(box.size.x - 20, 0)));
	addChild(createWidget<ScrewSilver>(Vec(5, 365)));
	addChild(createWidget<ScrewSilver>(Vec(box.size.x - 20, 365)));

	addParam(createParam<AutodafeKnobGreenBig>(Vec(20, 60), module, BitCrusher::BITS_PARAM));
	addParam(createParam<AutodafeKnobGreen>(Vec(27, 140), module, BitCrusher::RATE_PARAM));
	addParam(createParam<AutodafeKnobGreen>(Vec(27, 250), module, BitCrusher::ATTEN_PARAM));

	addInput(createInput<PJ301MPort>(Vec(32, 200), module, BitCrusher::CV_BITS));
	addInput(createInput<PJ301MPort>(Vec(10, 320), module, BitCrusher::INPUT));
	addOutput(createOutput<PJ301MPort>(Vec(48, 320), module, BitCrusher::OUTPUT));
	
}


Model *modelBitCrusher = createModel<BitCrusher, BitCrusherWidget>("BitCrusher");
