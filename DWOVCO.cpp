//**************************************************************************************
//Waves Module for VCV Rack by Autodafe http://www.autodafe.net
//
//Based on code taken from the Fundamentals plugins by Andrew Belt http://www.vcvrack.com
//And part of code on musicdsp.org: http://musicdsp.org/showArchirack::Vecomment.php?ArchiveID=78
//**************************************************************************************


#include "Autodafe.hpp"
#include <stdlib.h>
#include "dsp/digital.hpp"



#include "Gamma/AudioApp.h"
#include "Gamma/Gamma/Oscillator.h"
#include "Gamma/Gamma/rnd.h"

#define FONT_FILE      assetPlugin(plugin, "res/Segment7Standard.ttf")
 
 
  

using namespace gam;


struct DWOVCOModel : Module{
	enum ParamIds {
	
		PARAM_FREQ,
		PARAM_FINE,
		PARAM_FREQ_CV,
		PARAM_VOL,
		
		BTNUP, BTNDWN,

		
		NUM_PARAMS
	};
	enum InputIds {
		INPUT_FREQ_CV,
	
		NUM_INPUTS
	};
	enum OutputIds {
	
		OUT_DWO,
	

		NUM_OUTPUTS
	};





	DWOVCOModel();


float gSampleRate;
float oldSampleRate;
float h;
int modSelector=1;


SchmittTrigger btnup;
SchmittTrigger btndwn;



	
Sine<> sin;  

LFO<> mod; 
DWO<> dwo;	




float freq ;
 float phase=0.0;

 float sz=0;


	void step();
};
    




DWOVCOModel::DWOVCOModel() {
	params.resize(NUM_PARAMS);
	inputs.resize(NUM_INPUTS);
	outputs.resize(NUM_OUTPUTS);




}










void DWOVCOModel::step() {



	




  if (btnup.process(params[BTNUP].value))
    { 
         if (modSelector<6) {
        modSelector++;
            
         }
        else
        {
            modSelector=6;
        }
    }


      if (btndwn.process(params[BTNDWN].value))
    { 
         if (modSelector>1) {
        modSelector--;
            
         }
        else
        {
            modSelector=1;
        }
    }





 gSampleRate=engineGetSampleRate();



	float pitchFine = params[PARAM_FINE].value;
	float pitchCv = 12.0 * inputs[INPUT_FREQ_CV].value * params[PARAM_FREQ_CV].value;
  //freq = params[PARAM_FREQ].value+ pitchCv+pitchFine;
	//freq = 261.626 * powf(2.0, freq / 12.0);



 freq = params[PARAM_FREQ].value;

  freq = 261.626/4 * pow(2, freq  / 12.0);



//SINE WAVE


//sin.freq(freq);    
//sin.phase(phase);


float freqDwo = params[PARAM_FREQ].value/gSampleRate *2000;
freqDwo = freqDwo + pitchFine + pitchCv;


float deltaPhase = clampf(freq *1 /gSampleRate, 1e-6, 0.5);


phase += deltaPhase;
phase = eucmodf(phase, 1.0);



dwo.mod(0.2);
dwo.freq(freqDwo);
dwo.phase(phase);








if(modSelector==1) {outputs[OUT_DWO].value=dwo.up();}
if(modSelector==2) {outputs[OUT_DWO].value=dwo.down();}
if(modSelector==3) {outputs[OUT_DWO].value=dwo.sqr();}
if(modSelector==4) {outputs[OUT_DWO].value=dwo.pulse();}
if(modSelector==5) {outputs[OUT_DWO].value=dwo.tri()*1.5;}
if(modSelector==6) {outputs[OUT_DWO].value=dwo.para()*1.5;}



outputs[OUT_DWO].value*=params[PARAM_VOL].value*5;
}
 






struct DWOVCOModelDisplay : TransparentWidget {
  int *value;
  std::shared_ptr<Font> font;

  DWOVCOModelDisplay() {
    font = Font::load(FONT_FILE);
  }

  void draw(NVGcontext *vg) {
    // Background
    NVGcolor backgroundColor = nvgRGB(0x20, 0x20, 0x20);
    NVGcolor borderColor = nvgRGB(0x10, 0x10, 0x10);
    nvgBeginPath(vg);
    nvgRoundedRect(vg, 0.0, 0.0, box.size.x, box.size.y, 5.0);
    nvgFillColor(vg, backgroundColor);
    nvgFill(vg);
    nvgStrokeWidth(vg, 1.0);
    nvgStrokeColor(vg, borderColor);
    nvgStroke(vg);

    nvgFontSize(vg, 36);
    nvgFontFaceId(vg, font->handle);
    nvgTextLetterSpacing(vg, 2.5);

    std::string to_display = std::to_string(*value);
    rack::Vec textPos = rack::Vec(7.0f, 35.0f);

    NVGcolor textColor = nvgRGB(0xdf, 0xd2, 0x2c);
    nvgFillColor(vg, nvgTransRGBA(textColor, 16));
    nvgText(vg, textPos.x, textPos.y, "~~~", NULL);

    textColor = nvgRGB(0xda, 0xe9, 0x29);
    nvgFillColor(vg, nvgTransRGBA(textColor, 16));
    nvgText(vg, textPos.x, textPos.y, "\\\\\\", NULL);

    textColor = nvgRGB(0xf0, 0x00, 0x00);
    nvgFillColor(vg, textColor);

   
   std::string z;
	if(to_display.length()==1){z="00"+to_display;}
		else {z="0"+to_display;}

    nvgText(vg, textPos.x, textPos.y, z.c_str(), NULL);
  }
};






DWOVCOModelWidget::DWOVCOModelWidget() {
	DWOVCOModel *module = new DWOVCOModel();
	setModule(module);
	box.size = rack::Vec(15 * 10 ,380); 

	{
		SVGPanel *panel = new SVGPanel();
		panel->box.size = box.size;
		
        panel->setBackground(SVG::load(assetPlugin(plugin, "res/DWOVCO.svg")));
		addChild(panel);
 
	} 

{
    DWOVCOModelDisplay *display = new DWOVCOModelDisplay();
    display->box.pos = rack::Vec(35, 300);
    display->box.size = rack::Vec(82, 42);
 
 

    display->value = &module->modSelector;
    addChild(display);
  }


  
	addChild(createScrew<ScrewSilver>(rack::Vec(1, 0)));
	addChild(createScrew<ScrewSilver>(rack::Vec(box.size.x - 20, 0)));
	addChild(createScrew<ScrewSilver>(rack::Vec(1, 365)));
	addChild(createScrew<ScrewSilver>(rack::Vec(box.size.x - 20, 365)));


	addParam(createParam<AutodafeKnobRedBig>(rack::Vec(18, 50), module, DWOVCOModel::PARAM_FREQ, 0.1, 9.9, 5));
	addParam(createParam<AutodafeKnobRed>(rack::Vec(25, 120), module, DWOVCOModel::PARAM_FINE, -1.0, 1.0, 0.0));


	addParam(createParam<AutodafeKnobRed>(rack::Vec(25, 190), module, DWOVCOModel::PARAM_FREQ_CV, -1, 1, 0));
	addInput(createInput<PJ301MPort>(rack::Vec(90, 195), module, DWOVCOModel::INPUT_FREQ_CV));


	//addParam(createParam<AutodafeKnobRed>(rack::Vec(25, 260), module, DWOVCOModel::PARAM_FM_SELECTOR, 1, 7.0, 1.0));
 //addParam(createParam<LEDButton>(rack::Vec(70, 270), module, DWOVCOModel::PARAM_FM_SELECTOR, 0.0, 1.0, 0.0));
    


	addParam(createParam<AutodafeKnobRed>(rack::Vec(85, 120 ), module, DWOVCOModel::PARAM_VOL, 0.0, 1, 1));
   
	addOutput(createOutput<PJ301MPort>(rack::Vec(90, 65), module, DWOVCOModel::OUT_DWO));
	
  
addParam(createParam<BtnUp>(rack::Vec(120, 305), module, DWOVCOModel::BTNUP, 0.0, 1.0, 0.0));
addParam(createParam<BtnDwn>(rack::Vec(120, 323), module, DWOVCOModel::BTNDWN, 0.0, 1.0, 0.0));

}
