#include "plugin.hpp"





#define FONT_FILE      asset::plugin(pluginInstance, "res/Segment7Standard.ttf")


struct BPMClock : Module {


	
	enum ParamIds {
		BPM,BTNUP, BTNDWN,
		BTNUPDEC, BTNDWNDEC,
		NUM_PARAMS
	};
	enum InputIds {
		NUM_INPUTS
	};
	enum OutputIds {

		OUT_1,
		OUT_2,
		OUT_3,
		OUT_4,
		OUT_8,
		OUT_12,
		OUT_16,
		OUT_24,



		OUT_1_1,
		OUT_1_2,
		OUT_1_3,
		OUT_1_4,
		OUT_1_8,
		OUT_1_12,
		OUT_1_16,
		OUT_1_24,
		NUM_OUTPUTS
	};

	enum LightIds {
		CLOCK_LIGHT,
		
		NUM_LIGHTS
	};

	BPMClock() {




		
		config(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS, NUM_LIGHTS);


		
configParam(BPMClock::BTNUP, 0.0, 1.0, 0.0, "");
configParam(BPMClock::BTNDWN, 0.0, 1.0, 0.0, "");
configParam(BPMClock::BTNUPDEC, 0.0, 1.0, 0.0, "");
configParam(BPMClock::BTNDWNDEC, 0.0, 1.0, 0.0, "");
configParam(BPMClock::BPM, 30.0, 240.0, 120.0, "");




	}
	void process(const ProcessArgs &args) override;

json_t *dataToJson() override {
		json_t *rootJ = json_object();

		json_t *bpmintJ = json_integer((int) bpmint);
		json_object_set_new(rootJ, "bpmint", bpmintJ);

		json_t *bpmdecJ = json_integer((int) bpmdec);
		json_object_set_new(rootJ, "bpmdec", bpmdecJ);


	
		
		return rootJ;
	}

	void dataFromJson(json_t *rootJ) override {
		// running
		json_t *bpmintJ = json_object_get(rootJ, "bpmint");
		if (bpmintJ)
			bpmint= json_integer_value(bpmintJ);
		json_t *bpmdecJ = json_object_get(rootJ, "bpmdec");
		if (bpmdecJ)
			bpmdec= json_integer_value(bpmdecJ);
		
	}

	void onReset() override {
		bpmint=120;
		bpmdec=0;
		clockLight = 0.0f;
	}

	void onRandomize() override {
		
	}




 float bpm;
 int bpmint=120;
 int bpmdec=0;


dsp::SchmittTrigger btnup;
dsp::SchmittTrigger btndwn;
dsp::SchmittTrigger btnupdec;
dsp::SchmittTrigger btndwndec;

	double clock_phase = 0.0;
	float clockLight = 0.0f;
	uint32_t tick = UINT32_MAX;



};


void BPMClock::process(const ProcessArgs &args) {




  if (btnup.process(params[BTNUP].getValue()))
    { 
         if (bpmint<240.0) {
        bpmint+=1;
            
         }
        else
        {
            bpmint=0;
        }
    }



     if (btndwn.process(params[BTNDWN].getValue()))
    { 
         if (bpmint>0) {
        bpmint-=1;
            
         }
        else
        {
            bpmint=240.0;
        }
    }






if (btnupdec.process(params[BTNUPDEC].getValue()))
    { 
         if (bpmdec<9) {
        bpmdec+=1;
            
         }
        else
        {
            bpmdec=0;
            bpmint+=1;
        }
    }



     if (btndwndec.process(params[BTNDWNDEC].getValue()))
    { 
         if (bpmdec>0) {
        bpmdec-=1;
            
         }
        else
        {
            bpmdec=9;
            bpmint-=1;
        }
    }


bpm=bpmint+bpmdec*0.1;

	// Clock outputs are one-sample pulses. Clear every output before
	// generating the next pulse so no output can remain latched high.
	for (int outputId = OUT_1; outputId < NUM_OUTPUTS; outputId++)
		outputs[outputId].setVoltage(0.0f);










	//const float bpm = params[BPM].getValue();





	if (args.sampleRate > 0.0 && bpm > 0.0f)
		clock_phase += static_cast<double>(bpm) * 48.0 /
			(60.0 * static_cast<double>(args.sampleRate));

	bool ticked = false;

	while (clock_phase >= 1.0) {
		ticked = true;
		if (tick >= 1151u)
			tick = 0u;
		else
			++tick;
		clock_phase -= 1.0;
	}

	// Trigger outputs are intentionally one-sample pulses. Keep the LED visible
	// for a short visual decay without affecting generated clock timing.
	clockLight *= std::exp(-args.sampleTime / 0.02f);
	if (ticked)
		clockLight = 1.0f;
	lights[CLOCK_LIGHT].setBrightness(clockLight);

	if(ticked) {
		


		//DIVIDER
		outputs[OUT_1].setVoltage(!(tick % 48u)*5);
		outputs[OUT_2].setVoltage(!(tick % 96u)*5);
		outputs[OUT_3].setVoltage(!(tick % 144u)*5);
		outputs[OUT_4].setVoltage(!(tick % 192u)*5);
		outputs[OUT_8].setVoltage(!(tick % 384u)*5);
		outputs[OUT_12].setVoltage(!(tick % 576u)*5);
		outputs[OUT_16].setVoltage(!(tick % 768u)*5);
		outputs[OUT_24].setVoltage(!(tick % 1152u)*5);

		



		//MULTIPLIER
		outputs[OUT_1_1].setVoltage(!(tick % 48u)*5);
		outputs[OUT_1_2].setVoltage(!(tick % 24u)*5);
		outputs[OUT_1_3].setVoltage(!(tick % 16u)*5);
		outputs[OUT_1_4].setVoltage(!(tick % 12u)*5);
		outputs[OUT_1_8].setVoltage(!(tick % 6u)*5);
		outputs[OUT_1_12].setVoltage(!(tick % 4u)*5);
		outputs[OUT_1_16].setVoltage(!(tick % 3u)*5);
		outputs[OUT_1_24].setVoltage(!(tick % 2u)*5);






	} else {
		//DIVIDER
		outputs[OUT_1].setVoltage(0.f);
		outputs[OUT_2].setVoltage(0.f);
		outputs[OUT_4].setVoltage(0.f);
		outputs[OUT_8].setVoltage(0.f);
		outputs[OUT_12].setVoltage(0.f);
		outputs[OUT_16].setVoltage(0.f);
		outputs[OUT_24].setVoltage(0.f);





		//MULTIPLIER
		outputs[OUT_1_1].setVoltage(0.f);
		outputs[OUT_1_2].setVoltage(0.f);
		outputs[OUT_1_4].setVoltage(0.f);
		outputs[OUT_1_8].setVoltage(0.f);
		outputs[OUT_1_12].setVoltage(0.f);
		outputs[OUT_1_16].setVoltage(0.f);
		outputs[OUT_1_24].setVoltage(0.f);
	}




}











struct BPMClockModelDisplay : TransparentWidget {
  int *valueint;
  int *valuedec;
  std::shared_ptr<Font> font;

  BPMClockModelDisplay() {
    font = APP->window->loadFont(FONT_FILE);
  }

  void draw(const DrawArgs &args) override{
    // Background
    NVGcolor backgroundColor = nvgRGB(0x20, 0x20, 0x20);
    NVGcolor borderColor = nvgRGB(0x10, 0x10, 0x10);
    nvgBeginPath(args.vg);
    nvgRoundedRect(args.vg, 0.0, 0.0, box.size.x, box.size.y, 5.0);
    nvgFillColor(args.vg, backgroundColor);
    nvgFill(args.vg);
    nvgStrokeWidth(args.vg, 1.0);
    nvgStrokeColor(args.vg, borderColor);
    nvgStroke(args.vg);

    nvgFontSize(args.vg, 24);
    nvgFontFaceId(args.vg, font->handle);
    nvgTextLetterSpacing(args.vg, 2.5);

    std::string to_displayint = std::to_string(*valueint);
    std::string to_displaydec = std::to_string(*valuedec);
    std::string to_display = to_displayint +to_displaydec;
    Vec textPos = Vec(5.0f, 27.0f);

    NVGcolor textColor = nvgRGB(0xdf, 0xd2, 0x2c);
    nvgFillColor(args.vg, nvgTransRGBA(textColor, 16));
    nvgText(args.vg, textPos.x, textPos.y, "~~~~", NULL);

    textColor = nvgRGB(0xda, 0xe9, 0x29);
    nvgFillColor(args.vg, nvgTransRGBA(textColor, 16));
    nvgText(args.vg, textPos.x, textPos.y, "\\\\\\\\", NULL);

    textColor = nvgRGB(0xf0, 0x00, 0x00);
    nvgFillColor(args.vg, textColor);

   
   std::string z;
	if(to_displayint.length()==1){z="00"+to_displayint+to_displaydec;}
	else if(to_displayint.length()==2){z="0"+to_displayint+to_displaydec;}
		else  {z=to_displayint+to_displaydec;}

    nvgText(args.vg, textPos.x, textPos.y, z.c_str(), NULL);
    //nvgText(args.vg, textPos.x, textPos.y, to_display.c_str(), NULL);

nvgText(args.vg, 41, textPos.y, ".", NULL);
  }
};





struct BPMClockWidget : ModuleWidget {
	BPMClockWidget(BPMClock *module);
};



	


	BPMClockWidget::BPMClockWidget(BPMClock *module) {
		setModule(module);

	box.size = Vec(150, 380);

	{
		SvgPanel *panel = new SvgPanel();
		panel->box.size = box.size;
		panel->setBackground(APP->window->loadSvg(asset::plugin(pluginInstance, "res/BPMClock.svg")));
		addChild(panel);
	}




	addChild(createWidget<ScrewSilver>(Vec(15, 0)));
	addChild(createWidget<ScrewSilver>(Vec(box.size.x-30, 0)));
	addChild(createWidget<ScrewSilver>(Vec(15, 365)));
	addChild(createWidget<ScrewSilver>(Vec(box.size.x-30, 365)));



if (module != NULL)
	{
    BPMClockModelDisplay *display = new BPMClockModelDisplay();
    display->box.pos = Vec(35, 65);
    display->box.size = Vec(78, 36);
 
 

    display->valueint = &module->bpmint;
    display->valuedec = &module->bpmdec;
    addChild(display);
  }



addChild(createLight<MediumLight<RedLight>>(Vec(70, 105), module, BPMClock::CLOCK_LIGHT));



addParam(createParam<BtnUp>(Vec(15, 70), module, BPMClock::BTNUP));
addParam(createParam<BtnDwn>(Vec(15, 88), module, BPMClock::BTNDWN));


addParam(createParam<BtnUp>(Vec(120, 70), module, BPMClock::BTNUPDEC));
addParam(createParam<BtnDwn>(Vec(120, 88), module, BPMClock::BTNDWNDEC));





	//addParam(createParam<Davies1900hBlackKnob>(Vec(27, 80), module, BPMClock::BPM));

addOutput(createOutput<PJ301MPort>(Vec(30, 115),module, BPMClock::OUT_1));
	addOutput(createOutput<PJ301MPort>(Vec(30, 145),module, BPMClock::OUT_2));
	addOutput(createOutput<PJ301MPort>(Vec(30, 175),module, BPMClock::OUT_3));
	addOutput(createOutput<PJ301MPort>(Vec(30, 205),module, BPMClock::OUT_4));
	addOutput(createOutput<PJ301MPort>(Vec(30, 235),module, BPMClock::OUT_8));
	addOutput(createOutput<PJ301MPort>(Vec(30, 265),module, BPMClock::OUT_12));
	addOutput(createOutput<PJ301MPort>(Vec(30, 295),module, BPMClock::OUT_16));
	addOutput(createOutput<PJ301MPort>(Vec(30, 325),module, BPMClock::OUT_24));





	addOutput(createOutput<PJ301MPort>(Vec(90, 115),module, BPMClock::OUT_1_1));
	addOutput(createOutput<PJ301MPort>(Vec(90, 145),module, BPMClock::OUT_1_2));
	addOutput(createOutput<PJ301MPort>(Vec(90, 175),module, BPMClock::OUT_1_3));
	addOutput(createOutput<PJ301MPort>(Vec(90, 205),module, BPMClock::OUT_1_4));
	addOutput(createOutput<PJ301MPort>(Vec(90, 235),module, BPMClock::OUT_1_8));
	addOutput(createOutput<PJ301MPort>(Vec(90, 265),module, BPMClock::OUT_1_12));
	addOutput(createOutput<PJ301MPort>(Vec(90, 295),module, BPMClock::OUT_1_16));
	addOutput(createOutput<PJ301MPort>(Vec(90, 325),module, BPMClock::OUT_1_24));
}



Model *modelBPMClock = createModel<BPMClock, BPMClockWidget>("BPMClock");

