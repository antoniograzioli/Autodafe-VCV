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
#include "stk/include/BeeThree.h"
#include "stk/include/Wurley.h"
#include "stk/include/Rhodey.h"
#include "stk/include/FMVoices.h"
#include "stk/include/HevyMetl.h"
#include "stk/include/PercFlut.h"
#include "stk/include/TubeBell.h"
#include "stk/include/FileLoop.h"

#define FONT_FILE      assetPlugin(plugin, "res/Segment7Standard.ttf")
 
 
  
 
using namespace stk;


struct OPERATORModel : Module{
	enum ParamIds {
	
		PARAM_FREQ,
		PARAM_FINE,
		PARAM_FREQ_CV,
		PARAM_VOL,
		PARAM_TAB,
		PARAM_FM_SELECTOR,
		BTNUP, BTNDWN,

		
		NUM_PARAMS
	};
	enum InputIds {
		INPUT_FREQ_CV,
	
		NUM_INPUTS
	};
	enum OutputIds {
	
		OUT_FM,
	

		NUM_OUTPUTS
	};





	OPERATORModel();


float gSampleRate;
float oldSampleRate;
float h;
int fmselector=1;


SchmittTrigger btnup;
SchmittTrigger btndwn;


char names[7] = {'b','c','d','e','f','g'};
	

BlitSquare *waveSquare =new BlitSquare; //ONLY TO SET SAMPLERATE



	BeeThree *waveB3 = new BeeThree();  
	Wurley *waveWurley = new Wurley();  
	Rhodey *waveRhodey = new Rhodey();  
	FMVoices *waveFmVoices= new FMVoices();
	HevyMetl *wavesMetal = new HevyMetl();
	PercFlut *wavesPercFlut = new PercFlut();
	TubeBell *wavesTubeBell = new TubeBell();
SchmittTrigger trigger;

	void step();
};
    




OPERATORModel::OPERATORModel() {
	params.resize(NUM_PARAMS);
	inputs.resize(NUM_INPUTS);
	outputs.resize(NUM_OUTPUTS);




}










void OPERATORModel::step() {



	




  if (btnup.process(params[BTNUP].value))
    { 
         if (fmselector<7) {
        fmselector++;
            
         }
        else
        {
            fmselector=7;
        }
    }


      if (btndwn.process(params[BTNDWN].value))
    { 
         if (fmselector>1) {
        fmselector--;
            
         }
        else
        {
            fmselector=1;
        }
    }




 gSampleRate=engineGetSampleRate();


if (gSampleRate!=oldSampleRate){waveSquare->setSampleRate(engineGetSampleRate());}

	float pitchFine = 3.0 * quadraticBipolar(params[PARAM_FINE].value);
	float pitchCv = 12.0 * inputs[INPUT_FREQ_CV].value * params[PARAM_FREQ_CV].value;

  
	
	StkFloat   freq = params[PARAM_FREQ].value+ pitchCv+pitchFine;
	freq = 261.626 * powf(2.0, freq / 12.0);

if((int)fmselector==1){waveB3->noteOn(freq, 1); outputs[OUT_FM].value= waveB3->tick(0);}
if((int)fmselector==2){waveWurley->noteOn(freq, 1);outputs[OUT_FM].value= waveWurley->tick(0);}
if((int)fmselector==3){waveRhodey->noteOn(freq, 1);outputs[OUT_FM].value= waveRhodey->tick(0);}
if((int)fmselector==4){waveFmVoices->noteOn(freq, 1);;outputs[OUT_FM].value= waveFmVoices->tick(0);}
if((int)fmselector==5){wavesMetal ->noteOn(freq, 1);outputs[OUT_FM].value= wavesMetal->tick(0);}
if((int)fmselector==6){wavesPercFlut->noteOn(freq, 1);outputs[OUT_FM].value= wavesPercFlut->tick(0);}
if((int)fmselector==7){wavesTubeBell ->noteOn(freq, 1);outputs[OUT_FM].value= wavesTubeBell->tick(0);}



outputs[OUT_FM].value*=params[PARAM_VOL].value*1.5*5;

oldSampleRate=engineGetSampleRate();


}
 






struct OPERATORModelDisplay : TransparentWidget {
  int *value;
  std::shared_ptr<Font> font;

  OPERATORModelDisplay() {
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
    Vec textPos = Vec(7.0f, 35.0f);

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






OPERATORModelWidget::OPERATORModelWidget() {
	OPERATORModel *module = new OPERATORModel();
	setModule(module);
	box.size = Vec(15 * 10 ,380); 

	{
		SVGPanel *panel = new SVGPanel();
		panel->box.size = box.size;
		
        panel->setBackground(SVG::load(assetPlugin(plugin, "res/OPERATORVCO.svg")));
		addChild(panel);
 
	} 

{
    OPERATORModelDisplay *display = new OPERATORModelDisplay();
    display->box.pos = Vec(35, 300);
    display->box.size = Vec(82, 42);
 
 

    display->value = &module->fmselector;
    addChild(display);
  }


  
	addChild(createScrew<ScrewSilver>(Vec(1, 0)));
	addChild(createScrew<ScrewSilver>(Vec(box.size.x - 20, 0)));
	addChild(createScrew<ScrewSilver>(Vec(1, 365)));
	addChild(createScrew<ScrewSilver>(Vec(box.size.x - 20, 365)));


	addParam(createParam<AutodafeKnobRedBig>(Vec(18, 50), module, OPERATORModel::PARAM_FREQ, -60.0, 30.0, -15.0));
	addParam(createParam<AutodafeKnobRed>(Vec(25, 120), module, OPERATORModel::PARAM_FINE, -1.0, 1.0, 0.0));


	addParam(createParam<AutodafeKnobRed>(Vec(25, 190), module, OPERATORModel::PARAM_FREQ_CV, -1, 1, 0));
	addInput(createInput<PJ301MPort>(Vec(90, 195), module, OPERATORModel::INPUT_FREQ_CV));


	//addParam(createParam<AutodafeKnobRed>(Vec(25, 260), module, OPERATORModel::PARAM_FM_SELECTOR, 1, 7.0, 1.0));
 //addParam(createParam<LEDButton>(Vec(70, 270), module, OPERATORModel::PARAM_FM_SELECTOR, 0.0, 1.0, 0.0));
    


	addParam(createParam<AutodafeKnobRed>(Vec(85, 120 ), module, OPERATORModel::PARAM_VOL, 0.0, 1, 1));
   
	addOutput(createOutput<PJ301MPort>(Vec(90, 65), module, OPERATORModel::OUT_FM));
	
  
addParam(createParam<BtnUp>(Vec(120, 305), module, OPERATORModel::BTNUP, 0.0, 1.0, 0.0));
addParam(createParam<BtnDwn>(Vec(120, 323), module, OPERATORModel::BTNDWN, 0.0, 1.0, 0.0));

}
