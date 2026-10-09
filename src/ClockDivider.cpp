#include "plugin.hpp"

struct AutodafeClockDivider : Module {
	enum ParamIds {
		RESET_PARAM,
		NUM_PARAMS
	};
	enum InputIds {
		CLOCK_INPUT,
		RESET_INPUT,
		NUM_INPUTS
	};
	enum OutputIds {
		OUT1,
		OUT2,
		OUT4,
		OUT8,
		OUT16,
		OUT32,
		NUM_OUTPUTS
	};
	enum LightIds {
		LIGHT1,
		LIGHT2,
		LIGHT3,
		LIGHT4,
		LIGHT5,
		NUM_LIGHTS
	};

	float phase = 0.0;
	float blinkPhase = 0.0;

	int clock2Count = 0;
	int clock4Count = 0;
	int clock8Count = 0;
	int clock16Count = 0;
	int clock32Count = 0;

	dsp::SchmittTrigger trigger2;
	dsp::SchmittTrigger trigger4;
	dsp::SchmittTrigger trigger8;
	dsp::SchmittTrigger trigger16;
	dsp::SchmittTrigger trigger32;
	dsp::SchmittTrigger reset_trig;

	void reset() {}

	AutodafeClockDivider() {
		config(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS, NUM_LIGHTS);
		configParam(AutodafeClockDivider::RESET_PARAM, 0.0, 1.0, 0.0, "");
		//params.resize(NUM_PARAMS);
		//inputs.resize(NUM_INPUTS);
		//outputs.resize(NUM_OUTPUTS);
	};
	void process(const ProcessArgs &args) {
		int divider2 = 2, divider4 = 4, divider8 = 8, divider16 = 16, divider32 = 32;
		bool reset = false;
		float deltaTime = 1.0 / args.sampleRate;
		blinkPhase += deltaTime;

		if (blinkPhase >= 1.0)
			blinkPhase -= 1.0;

		if (reset_trig.process(params[RESET_PARAM].getValue())) {
			clock2Count = 0;
			clock4Count = 0;
			clock8Count = 0;
			clock16Count = 0;
			clock32Count = 0;
			reset = true;
		}

		if ((clock2Count >= divider2) || (reset_trig.process(inputs[RESET_INPUT].getVoltage()))) {
			clock2Count = 0;
			reset = true;
		}

		if ((clock4Count >= divider4) || (reset_trig.process(inputs[RESET_INPUT].getVoltage()))) {
			clock4Count = 0;
			reset = true;
		}

		if ((clock8Count >= divider8) || (reset_trig.process(inputs[RESET_INPUT].getVoltage()))) {
			clock8Count = 0;
			reset = true;
		}

		if ((clock16Count >= divider16) || (reset_trig.process(inputs[RESET_INPUT].getVoltage()))) {
			clock16Count = 0;
			reset = true;
		}

		if ((clock32Count >= divider32) || (reset_trig.process(inputs[RESET_INPUT].getVoltage()))) {
			clock32Count = 0;
			reset = true;
		}

		if (clock2Count < divider2 / 2) {
			outputs[OUT2].setVoltage(10.0);
			if (clock2Count == 0) {
				lights[LIGHT1].setBrightness(1.0);
			} else {
				lights[LIGHT1].setBrightness((blinkPhase < 0.5)?1.0:0.0);
			}

		} else {
			outputs[OUT2].setVoltage(0.0);
			lights[LIGHT1].setBrightness(0.0);
		}

		if (clock4Count < divider4 / 2) {
			outputs[OUT4].setVoltage(10.0);
			if (clock4Count == 0) {
				lights[LIGHT2].setBrightness(1.0);
			} else {
				lights[LIGHT2].setBrightness((blinkPhase < 0.5)?1.0:0.0);
			}

		} else {
			outputs[OUT4].setVoltage(0.0);
			lights[LIGHT2].setBrightness(0.0);
		}

		if (clock8Count < divider8 / 2) {
			outputs[OUT8].setVoltage(10.0);
			if (clock8Count == 0) {
				lights[LIGHT3].setBrightness(1.0);
			} else {
				lights[LIGHT3].setBrightness((blinkPhase < 0.5)?1.0:0.0);
			}

		} else {
			outputs[OUT8].setVoltage(0.0);
			lights[LIGHT3].setBrightness(0.0);
		}

		if (clock16Count < divider16 / 2) {
			outputs[OUT16].setVoltage(10.0);
			if (clock16Count == 0) {
				lights[LIGHT4].setBrightness(1.0);
			} else {
				lights[LIGHT4].setBrightness((blinkPhase < 0.5)?1.0:0.0);
			}

		} else {
			outputs[OUT16].setVoltage(0.0);
			lights[LIGHT4].setBrightness(0.0);
		}

		if (clock32Count < divider32 / 2) {
			outputs[OUT32].setVoltage(10.0);
			if (clock16Count == 0) {
				lights[LIGHT5].setBrightness(1.0);
			} else {
				lights[LIGHT5].setBrightness((blinkPhase < 0.5)?1.0:0.0);
			}

		} else {
			outputs[OUT32].setVoltage(0.0);
			lights[LIGHT5].setBrightness(0.0);

		}

		if (reset == false) {
			if (trigger2.process(inputs[CLOCK_INPUT].getVoltage()) && clock2Count <= divider2) {
				clock2Count++;

			}

		}

		if (reset == false) {
			if (trigger4.process(inputs[CLOCK_INPUT].getVoltage()) && clock4Count <= divider4) {
				clock4Count++;

			}

		}

		if (reset == false) {
			if (trigger8.process(inputs[CLOCK_INPUT].getVoltage()) && clock8Count <= divider8) {
				clock8Count++;

			}

		}

		if (reset == false) {
			if (trigger16.process(inputs[CLOCK_INPUT].getVoltage()) && clock16Count <= divider16) {
				clock16Count++;

			}

		}

		if (reset == false) {
			if (trigger32.process(inputs[CLOCK_INPUT].getVoltage()) && clock32Count <= divider32) {
				clock32Count++;

			}

		}
	}
};

struct AutodafeClockDividerWidget : ModuleWidget {
	AutodafeClockDividerWidget(AutodafeClockDivider *module) {
		setModule(module);

		box.size = Vec(60, 380);

{
		SvgPanel *panel = new SvgPanel();
		panel->box.size = box.size;
		
        panel->setBackground(APP->window->loadSvg(asset::plugin(pluginInstance, "res/ClockDivider.svg")));
		addChild(panel);
	}



		

		//screw
		addChild(createWidget<ScrewSilver>(Vec(1, 0)));
		addChild(createWidget<ScrewSilver>(Vec(1, 365)));
		//port in
		addInput(createInput<PJ3410Port>(Vec(2, 20), module, AutodafeClockDivider::CLOCK_INPUT));
		addInput(createInput<PJ3410Port>(Vec(2, 60), module, AutodafeClockDivider::RESET_INPUT));
		addParam(createParam<LEDButton>(Vec(38, 67), module, AutodafeClockDivider::RESET_PARAM));
		//port out
		addOutput(createOutput<PJ3410Port>(Vec(2, 120), module, AutodafeClockDivider::OUT2));
		addOutput(createOutput<PJ3410Port>(Vec(2, 160), module, AutodafeClockDivider::OUT4));
		addOutput(createOutput<PJ3410Port>(Vec(2, 200), module, AutodafeClockDivider::OUT8));
		addOutput(createOutput<PJ3410Port>(Vec(2, 240), module, AutodafeClockDivider::OUT16));
		addOutput(createOutput<PJ3410Port>(Vec(2, 280), module, AutodafeClockDivider::OUT32));
		//light
		addChild(createLight<SmallLight<RedLight>>(Vec(38, 125), module, AutodafeClockDivider::LIGHT1));
		addChild(createLight<SmallLight<RedLight>>(Vec(38, 165), module, AutodafeClockDivider::LIGHT2));
		addChild(createLight<SmallLight<RedLight>>(Vec(38, 205), module, AutodafeClockDivider::LIGHT3));
		addChild(createLight<SmallLight<RedLight>>(Vec(38, 245), module, AutodafeClockDivider::LIGHT4));
		addChild(createLight<SmallLight<RedLight>>(Vec(38, 285), module, AutodafeClockDivider::LIGHT5));
	}
};

Model *modelAutodafeClockDivider = createModel<AutodafeClockDivider, AutodafeClockDividerWidget>("ClockDivider");