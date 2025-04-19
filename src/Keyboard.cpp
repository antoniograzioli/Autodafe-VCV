//**************************************************************************************
//Waves Module for VCV Rack by Autodafe http://www.autodafe.net
//
//Based on code taken from the Fundamentals plugins by Andrew Belt http://www.vcvrack.com
//And part of code on musicdsp.org: http://musicdsp.org/showArchiveComment.php?ArchiveID=78
//**************************************************************************************


#include "plugin.hpp"
#include <stdlib.h>




#define FONT_FILE      asset::plugin(pluginInstance, "res/Segment7Standard.ttf")
 
 
 


struct KeyboardModel : Module{



	
	enum ParamIds {
	
		PARAM_C,
		PARAM_CC,
		PARAM_D,
		PARAM_DD,
		PARAM_E,

		PARAM_F,
		PARAM_FF,
		PARAM_G,
		PARAM_GG,
		PARAM_A,
		PARAM_AA,
		PARAM_B,
		PARAM_C2,
		BTNUP,
		BTNDWN,
		NUM_PARAMS
	};
	enum InputIds {
		
	
		NUM_INPUTS
	};
	enum OutputIds {
	
		GATE_OUT,

		CV_OUT,	

		NUM_OUTPUTS
	};
enum LightIds {
		
		
		NUM_LIGHTS
	};




	KeyboardModel();
	void process(const ProcessArgs &args);






dsp::SchmittTrigger C;
dsp::SchmittTrigger CC;
dsp::SchmittTrigger D;
dsp::SchmittTrigger DD;
dsp::SchmittTrigger E;
dsp::SchmittTrigger F;
dsp::SchmittTrigger FF;
dsp::SchmittTrigger G;
dsp::SchmittTrigger GG;
dsp::SchmittTrigger A;
dsp::SchmittTrigger AA;
dsp::SchmittTrigger B;
dsp::SchmittTrigger C2;


dsp::SchmittTrigger btnup;
dsp::SchmittTrigger btndwn;
int note;
int octave=3;
	



};
    




KeyboardModel::KeyboardModel()  {

config(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS, NUM_LIGHTS);


configParam(KeyboardModel::BTNUP, 0.0, 1.0, 0.0, "");
configParam(KeyboardModel::BTNDWN, 0.0, 1.0, 0.0, "");
configParam(KeyboardModel::PARAM_C, 0.0, 1.0, 0.0, "");
configParam(KeyboardModel::PARAM_D, 0.0, 1.0, 0.0, "");
configParam(KeyboardModel::PARAM_E, 0.0, 1.0, 0.0, "");
configParam(KeyboardModel::PARAM_F, 0.0, 1.0, 0.0, "");
configParam(KeyboardModel::PARAM_G, 0.0, 1.0, 0.0, "");
configParam(KeyboardModel::PARAM_A, 0.0, 1.0, 0.0, "");
configParam(KeyboardModel::PARAM_B, 0.0, 1.0, 0.0, "");
configParam(KeyboardModel::PARAM_C2, 0.0, 1.0, 0.0, "");
configParam(KeyboardModel::PARAM_CC, 0.0, 1.0, 0.0, "");
configParam(KeyboardModel::PARAM_DD, 0.0, 1.0, 0.0, "");
configParam(KeyboardModel::PARAM_FF, 0.0, 1.0, 0.0, "");
configParam(KeyboardModel::PARAM_GG, 0.0, 1.0, 0.0, "");
configParam(KeyboardModel::PARAM_AA, 0.0, 1.0, 0.0, "");


}







		
	









void KeyboardModel::process(const ProcessArgs &args) {
outputs[GATE_OUT].value=0.0;




  if (btnup.process(params[BTNUP].getValue()))
    { 
         if (octave<8) {
        octave++;  
         }
        else
        {
            octave=8;
        }
    }


if (btndwn.process(params[BTNDWN].getValue()))
    { 
         if (octave>0) {
        octave--;  
         }
        else
        {
            octave=0;
        }
    }



	
if(C.process(params[PARAM_C].getValue()))
	{
		outputs[GATE_OUT].value=10.0;
		note=0;

	}


if(CC.process(params[PARAM_CC].getValue()))
	{
		outputs[GATE_OUT].value=10.0;
		note=1;

	}



if(D.process(params[PARAM_D].getValue()))
	{
		outputs[GATE_OUT].value=10.0;
		note=2;

	}

	if(DD.process(params[PARAM_DD].getValue()))
	{
		outputs[GATE_OUT].value=10.0;
		note=3;

	}



if(E.process(params[PARAM_E].getValue()))
	{
		outputs[GATE_OUT].value=10.0;
		note=4;

	}



	if(F.process(params[PARAM_F].getValue()))
	{
		outputs[GATE_OUT].value=10.0;
		note=5;

	}

		if(FF.process(params[PARAM_FF].getValue()))
	{
		outputs[GATE_OUT].value=10.0;
		note=6;

	}



	if(G.process(params[PARAM_G].getValue()))
	{
		outputs[GATE_OUT].value=10.0;
		note=7;

	}
	if(GG.process(params[PARAM_GG].getValue()))
	{
		outputs[GATE_OUT].value=10.0;
		note=8;

	}


	if(A.process(params[PARAM_A].getValue()))
	{
		outputs[GATE_OUT].value=10.0;
		note=9;

	}

	if(AA.process(params[PARAM_AA].getValue()))
	{
		outputs[GATE_OUT].value=10.0;
		note=10;

	}

	if(B.process(params[PARAM_B].getValue()))
	{
		outputs[GATE_OUT].value=10.0;
		note=11;

	}


	if(C2.process(params[PARAM_C2].getValue()))
	{
		outputs[GATE_OUT].value=10.0;
		note=12;

	}




outputs[CV_OUT].setVoltage(((note+(octave*12) - 60)) / 12.0);


}
 






struct KeyboardModelDisplay : TransparentWidget {
  int *value;
  std::shared_ptr<Font> font;

  KeyboardModelDisplay() {
    font = APP->window->loadFont(FONT_FILE);
  }

  void draw(const DrawArgs &args) {
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

    nvgFontSize(args.vg, 36);
    nvgFontFaceId(args.vg, font->handle);
    nvgTextLetterSpacing(args.vg, 2.5);

    std::string to_display = std::to_string(*value);
    Vec textPos = Vec(7.0f, 35.0f);

    NVGcolor textColor = nvgRGB(0xdf, 0xd2, 0x2c);
    nvgFillColor(args.vg, nvgTransRGBA(textColor, 16));
    nvgText(args.vg, textPos.x, textPos.y, "~~~", NULL);

    textColor = nvgRGB(0xda, 0xe9, 0x29);
    nvgFillColor(args.vg, nvgTransRGBA(textColor, 16));
    nvgText(args.vg, textPos.x, textPos.y, "\\\\\\", NULL);

    textColor = nvgRGB(0xf0, 0x00, 0x00);
    nvgFillColor(args.vg, textColor);

   
   std::string z;
	if(to_display.length()==1){z="00"+to_display;}
		else {z="0"+to_display;}

    nvgText(args.vg, textPos.x, textPos.y, z.c_str(), NULL);
  }
};




struct OctaveDisplay : TransparentWidget {
  int *value;

  std::shared_ptr<Font> font;

  OctaveDisplay() {
    font = APP->window->loadFont(FONT_FILE);
  }

  void draw(const DrawArgs &args) {
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

    nvgFontSize(args.vg, 12);
    nvgFontFaceId(args.vg, font->handle);
    nvgTextLetterSpacing(args.vg, 2.5);

    std::string to_display = std::to_string(*value);
    Vec textPos = Vec(7.0f, 35.0f);

    NVGcolor textColor = nvgRGB(0xdf, 0xd2, 0x2c);
    nvgFillColor(args.vg, nvgTransRGBA(textColor, 16));
    nvgText(args.vg, textPos.x, textPos.y-20, "~~~", NULL);

    textColor = nvgRGB(0xda, 0xe9, 0x29);
    nvgFillColor(args.vg, nvgTransRGBA(textColor, 16));
    nvgText(args.vg, textPos.x, textPos.y-20, "\\\\\\", NULL);

    textColor = nvgRGB(0xf0, 0x00, 0x00);
    nvgFillColor(args.vg, textColor);
	
	//ADD LEADING ZEROS
	std::string z;
	if(to_display.length()==1){z="00"+to_display;}
		else {z="0"+to_display;}

    nvgText(args.vg, textPos.x, textPos.y-20, z.c_str(), NULL);
  }
};



struct KeyboardModelWidget : ModuleWidget {
	KeyboardModelWidget(KeyboardModel *module);
};

	KeyboardModelWidget::KeyboardModelWidget(KeyboardModel *module) {
		setModule(module);




	box.size = Vec(15 * 23 ,380); 

	{
		SvgPanel *panel = new SvgPanel();
		panel->box.size = box.size;
		
        panel->setBackground(APP->window->loadSvg(asset::plugin(pluginInstance, "res/Keyboard.svg")));
		addChild(panel);
 
	} 




	
if (module != NULL)

{
    OctaveDisplay *octavedisplay = new OctaveDisplay();
    octavedisplay->box.pos = Vec(25,310);
    octavedisplay->box.size = Vec(41, 21);
    octavedisplay->value = &module->octave;
    addChild(octavedisplay);
  }
addParam(createParam<BtnUp>(Vec(40, 297), module, KeyboardModel::BTNUP));
addParam(createParam<BtnDwn>(Vec(40, 331), module, KeyboardModel::BTNDWN));
  
	addChild(createWidget<ScrewSilver>(Vec(1, 0)));
	addChild(createWidget<ScrewSilver>(Vec(box.size.x - 20, 0)));
	addChild(createWidget<ScrewSilver>(Vec(1, 365)));
	addChild(createWidget<ScrewSilver>(Vec(box.size.x - 20, 365)));


	


	
  
addParam(createParam<WhiteKey>(Vec(10, 100), module, KeyboardModel::PARAM_C));
addParam(createParam<WhiteKey>(Vec(50, 100), module, KeyboardModel::PARAM_D));
addParam(createParam<WhiteKey>(Vec(90, 100), module, KeyboardModel::PARAM_E));
addParam(createParam<WhiteKey>(Vec(130, 100), module, KeyboardModel::PARAM_F));
addParam(createParam<WhiteKey>(Vec(170, 100), module, KeyboardModel::PARAM_G));
addParam(createParam<WhiteKey>(Vec(210, 100), module, KeyboardModel::PARAM_A));
addParam(createParam<WhiteKey>(Vec(250, 100), module, KeyboardModel::PARAM_B));
addParam(createParam<WhiteKey>(Vec(290, 100), module, KeyboardModel::PARAM_C2));

addParam(createParam<BlackKey>(Vec(40, 100), module, KeyboardModel::PARAM_CC));
addParam(createParam<BlackKey>(Vec(80, 100), module, KeyboardModel::PARAM_DD));
addParam(createParam<BlackKey>(Vec(160, 100), module, KeyboardModel::PARAM_FF));
addParam(createParam<BlackKey>(Vec(200, 100), module, KeyboardModel::PARAM_GG));
addParam(createParam<BlackKey>(Vec(240, 100), module, KeyboardModel::PARAM_AA));




addOutput(createOutput<PJ301MPort>(Vec(270, 310), module, KeyboardModel::GATE_OUT));

addOutput(createOutput<PJ301MPort>(Vec(300, 310), module, KeyboardModel::CV_OUT));


}





Model *modelKeyboardModel = createModel<KeyboardModel, KeyboardModelWidget>("Keyboard");

