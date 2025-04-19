//**************************************************************************************
//Clock Divider Module for VCV Rack by Autodafe http://www.autodafe.net
//
//  Based on code created by Created by Nigel Redmon 
//  EarLevel Engineering: earlevel.com
//  Copyright 2012 Nigel Redmon
//  http://www.earlevel.com/main/2012/11/26/biquad-c-source-code/
//**************************************************************************************

#include "plugin.hpp"
#include <stdlib.h>




struct FixedFilter : Module{

	
	enum ParamIds {
		EQ1,
		EQ2,
		EQ3,
		EQ4,
		EQ5,
		EQ6,
		EQ7,
		EQ8,

		NUM_PARAMS
	};
	enum InputIds {
		DRIVE_INPUT,
		INPUT,
		NUM_INPUTS
	};
	enum OutputIds {
		OUT,
		NUM_OUTPUTS
	};


	FixedFilter();

Biquad *bq1 = new Biquad();
Biquad *bq2 = new Biquad();
Biquad *bq3 = new Biquad();
Biquad *bq4 = new Biquad();
Biquad *bq5 = new Biquad();
Biquad *bq6 = new Biquad();
Biquad *bq7 = new Biquad();
Biquad *bq8 = new Biquad();

	
	void process(const ProcessArgs &args);
};









FixedFilter::FixedFilter() {

config(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS);
configParam(FixedFilter::EQ1, -12, 12.0, 0, "");
configParam(FixedFilter::EQ2, -12, 12.0, 0.0, "");
configParam(FixedFilter::EQ3, -12, 12.0, 0.0, "");
configParam(FixedFilter::EQ4, -12, 12.0, 0.0, "");
configParam(FixedFilter::EQ5, -12, 12.0, 0.0, "");
configParam(FixedFilter::EQ6, -12, 12.0, 0.0, "");
configParam(FixedFilter::EQ7, -12, 12.0, 0.0, "");
configParam(FixedFilter::EQ8, -12, 12.0, 0.0, "");



	//params.resize(NUM_PARAMS);
	//inputs.resize(NUM_INPUTS);
	//outputs.resize(NUM_OUTPUTS);
}

float out;








void FixedFilter::process(const ProcessArgs &args) {
	
	

	float input = inputs[INPUT].getVoltage() / 5.0;
	


	bq1->setBiquad(bq_type_peak, 75.0 / args.sampleRate, 5, params[EQ1].getValue());
	bq2->setBiquad(bq_type_peak, 125.0 / args.sampleRate, 5, params[EQ2].getValue());
	bq3->setBiquad(bq_type_peak, 250.0 / args.sampleRate, 5, params[EQ3].getValue());
	bq4->setBiquad(bq_type_peak, 500.0 / args.sampleRate, 5, params[EQ4].getValue());
	bq5->setBiquad(bq_type_peak, 1000.0 / args.sampleRate, 5, params[EQ5].getValue());
	bq6->setBiquad(bq_type_peak, 2000.0 / args.sampleRate, 5, params[EQ6].getValue());
	bq7->setBiquad(bq_type_peak, 4000.0 / args.sampleRate, 5, params[EQ7].getValue());
	bq8->setBiquad(bq_type_peak, 8000.0 / args.sampleRate, 5, params[EQ8].getValue());

	
	
	
	out = bq1->process(input);
	out = bq2->process(out);
	out = bq3->process(out);
	out = bq4->process(out);
	out = bq5->process(out);
	out = bq6->process(out);
	out = bq7->process(out);
	out = bq8->process(out);



	outputs[OUT].value= out*5;
	}




	struct FixedFilterWidget : ModuleWidget {
	FixedFilterWidget(FixedFilter *module);
};

	FixedFilterWidget::FixedFilterWidget(FixedFilter *module) {
		setModule(module);


	box.size = Vec(15 * 9, 380);

	{
		SvgPanel *panel = new SvgPanel();
		panel->box.size = box.size;

		panel->setBackground(APP->window->loadSvg(asset::plugin(pluginInstance, "res/FixedFilterBank.svg")));
		addChild(panel);
	}
	
	addChild(createWidget<ScrewSilver>(Vec(5, 0)));
	addChild(createWidget<ScrewSilver>(Vec(box.size.x - 20, 0)));
	addChild(createWidget<ScrewSilver>(Vec(5, 365))); 
	addChild(createWidget<ScrewSilver>(Vec(box.size.x - 20, 365)));


	addParam(createParam<AutodafeKnobBlue>(Vec(20, 50), module, FixedFilter::EQ1));
	addParam(createParam<AutodafeKnobBlue>(Vec(20, 110), module, FixedFilter::EQ2));
	addParam(createParam<AutodafeKnobBlue>(Vec(20, 170), module, FixedFilter::EQ3));
	addParam(createParam<AutodafeKnobBlue>(Vec(20, 230), module, FixedFilter::EQ4));
	 

	addParam(createParam<AutodafeKnobBlue>(Vec(80, 50), module, FixedFilter::EQ5));
	addParam(createParam<AutodafeKnobBlue>(Vec(80, 110), module, FixedFilter::EQ6));
	addParam(createParam<AutodafeKnobBlue>(Vec(80, 170), module, FixedFilter::EQ7));
	addParam(createParam<AutodafeKnobBlue>(Vec(80, 230), module, FixedFilter::EQ8));

		addInput(createInput<PJ301MPort>(Vec(25, 320), module, FixedFilter::INPUT));
	
		addOutput(createOutput<PJ301MPort>(Vec(85, 320), module, FixedFilter::OUT));

}
Model *modelFixedFilter = createModel<FixedFilter, FixedFilterWidget>("FixedFilter");



