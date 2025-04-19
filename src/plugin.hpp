#include "rack.hpp"
#include "Biquad.h"
#include "VAStateVariableFilter.h"





using namespace rack;



////////////////////
// module widgets
////////////////////

extern Plugin *pluginInstance;


 

/////////////////////////////
// CUSTOM KNOBS & GRAPHICS //
/////////////////////////////


struct AutodafeKnobRed : app::SvgKnob {
    AutodafeKnobRed() {
        box.size = Vec(20, 20);
        minAngle = -0.75*M_PI;
        maxAngle = 0.75*M_PI;
        setSvg(APP->window->loadSvg(asset::plugin(pluginInstance, "res/AutodafeKnobRed.svg")));
    }
};




struct AutodafeKnobRedBig : app::SvgKnob {
    AutodafeKnobRedBig() {
        box.size = Vec(35, 35);
        minAngle = -0.75*M_PI;
        maxAngle = 0.75*M_PI;
        setSvg(APP->window->loadSvg(asset::plugin(pluginInstance, "res/AutodafeKnobRedBig.svg")));
    }
};



struct AutodafeKnobBlue : app::SvgKnob {
	AutodafeKnobBlue() {
		box.size = Vec(20, 20);
		minAngle = -0.75*M_PI;
		maxAngle = 0.75*M_PI;
		setSvg(APP->window->loadSvg(asset::plugin(pluginInstance, "res/AutodafeKnobBlue.svg")));
	}
};


struct AutodafeKnobBlueBig : app::SvgKnob {
	AutodafeKnobBlueBig() {
		box.size = Vec(35, 35);
		minAngle = -0.75*M_PI;
		maxAngle = 0.75*M_PI;
		setSvg(APP->window->loadSvg(asset::plugin(pluginInstance, "res/AutodafeKnobBlueBig.svg")));
	}
};



struct AutodafeKnobGreen : app::SvgKnob {
	AutodafeKnobGreen() {
		box.size = Vec(20, 20);
		minAngle = -0.75*M_PI;
		maxAngle = 0.75*M_PI;
		setSvg(APP->window->loadSvg(asset::plugin(pluginInstance, "res/AutodafeKnobGreen.svg")));
	}
};


struct AutodafeKnobGreenBig : app::SvgKnob {
	AutodafeKnobGreenBig() {
		box.size = Vec(35, 35);
		minAngle = -0.75*M_PI;
		maxAngle = 0.75*M_PI;
		setSvg(APP->window->loadSvg(asset::plugin(pluginInstance, "res/AutodafeKnobGreenBig.svg")));
	}
};



struct AutodafeKnobPurple : app::SvgKnob {
	AutodafeKnobPurple() {
		box.size = Vec(20, 20);
		minAngle = -0.75*M_PI;
		maxAngle = 0.75*M_PI;
		setSvg(APP->window->loadSvg(asset::plugin(pluginInstance, "res/AutodafeKnobPurple.svg")));
	}
};


struct AutodafeKnobPurpleSmall : app::SvgKnob {
	AutodafeKnobPurpleSmall() {
		box.size = Vec(15, 15);
		minAngle = -0.75*M_PI;
		maxAngle = 0.75*M_PI;
		setSvg(APP->window->loadSvg(asset::plugin(pluginInstance, "res/AutodafeKnobPurpleSmall.svg")));
	}
};


struct AutodafeKnobPurpleBig : app::SvgKnob {
	AutodafeKnobPurpleBig() {
		box.size = Vec(35, 35);
		minAngle = -0.75*M_PI;
		maxAngle = 0.75*M_PI;
		setSvg(APP->window->loadSvg(asset::plugin(pluginInstance, "res/AutodafeKnobPurpleBig.svg")));
	}
};


struct AutodafeKnobWhite : app::SvgKnob {
	AutodafeKnobWhite() {
		box.size = Vec(20, 20);
		minAngle = -0.75*M_PI;
		maxAngle = 0.75*M_PI;
		setSvg(APP->window->loadSvg(asset::plugin(pluginInstance, "res/AutodafeKnobWhite.svg")));
	}
};



struct AutodafeKnobWhiteBig : app::SvgKnob {
	AutodafeKnobWhiteBig() {
		box.size = Vec(35, 35);
		minAngle = -0.75*M_PI;
		maxAngle = 0.75*M_PI;
		setSvg(APP->window->loadSvg(asset::plugin(pluginInstance, "res/AutodafeKnobWhiteBig.svg")));
	}
};

struct AutodafeKnobBrown : app::SvgKnob {
	AutodafeKnobBrown() {
		box.size = Vec(20, 20);
		minAngle = -0.75*M_PI;
		maxAngle = 0.75*M_PI;
		setSvg(APP->window->loadSvg(asset::plugin(pluginInstance, "res/AutodafeKnobBrown.svg")));
	}
};




struct AutodafeKnobBrownBig : app::SvgKnob {
	AutodafeKnobBrownBig() {
		box.size = Vec(35, 35);
		minAngle = -0.75*M_PI;
		maxAngle = 0.75*M_PI;
		setSvg(APP->window->loadSvg(asset::plugin(pluginInstance, "res/AutodafeKnobBrownBig.svg")));
	}
};

struct AutodafeKnobBlack : app::SvgKnob {
	AutodafeKnobBlack() {
		box.size = Vec(20, 20);
		minAngle = -0.75*M_PI;
		maxAngle = 0.75*M_PI;
		setSvg(APP->window->loadSvg(asset::plugin(pluginInstance, "res/AutodafeKnobBlack.svg")));
	}

};



struct AutodafeKnobBlackSmall : app::SvgKnob {
	AutodafeKnobBlackSmall() {
		box.size = Vec(15, 15);
		minAngle = -0.75*M_PI;
		maxAngle = 0.75*M_PI;
		setSvg(APP->window->loadSvg(asset::plugin(pluginInstance, "res/AutodafeKnobBlackSmall.svg")));
	}

};


struct AutodafeKnobBlackBig : app::SvgKnob {
	AutodafeKnobBlackBig() {
		box.size = Vec(35, 35);
		minAngle = -0.75*M_PI;
		maxAngle = 0.75*M_PI;
		setSvg(APP->window->loadSvg(asset::plugin(pluginInstance, "res/AutodafeKnobBlackBig.svg")));
	}
};

struct AutodafeKnobOrange : app::SvgKnob {
	AutodafeKnobOrange() {
		box.size = Vec(20, 20);
		minAngle = -0.75*M_PI;
		maxAngle = 0.75*M_PI;
		setSvg(APP->window->loadSvg(asset::plugin(pluginInstance, "res/AutodafeKnobOrange.svg")));
	}
};



struct AutodafeKnobOrangeBig : app::SvgKnob {
	AutodafeKnobOrangeBig() {
		box.size = Vec(35, 35);
		minAngle = -0.75*M_PI;
		maxAngle = 0.75*M_PI;
		setSvg(APP->window->loadSvg(asset::plugin(pluginInstance, "res/AutodafeKnobOrangeBig.svg")));
	}
};



struct AutodafeKnobYellow : app::SvgKnob {
	AutodafeKnobYellow() {
		box.size = Vec(20, 20);
		minAngle = -0.75*M_PI;
		maxAngle = 0.75*M_PI;
		setSvg(APP->window->loadSvg(asset::plugin(pluginInstance, "res/AutodafeKnobYellow.svg")));
		
	}
};




struct AutodafeKnobYellowBig : app::SvgKnob {
	AutodafeKnobYellowBig() {
		box.size = Vec(35, 35);
		minAngle = -0.75*M_PI;
		maxAngle = 0.75*M_PI;
		setSvg(APP->window->loadSvg(asset::plugin(pluginInstance, "res/AutodafeKnobYellowBig.svg")));
		
	}
};







struct AutodafeButton : SvgSwitch {


    AutodafeButton() {momentary = true;

    	addFrame(APP->window->loadSvg(asset::plugin(pluginInstance, "res/AutodafeButton.svg")));
        //APP->window->loadSvg("res/AutodafeButton.svg");
		
		box.size = Vec(20,20);
		
      
    } 
};   





struct BtnUp : SvgSwitch {
	
	BtnUp() {momentary = true;
		addFrame(APP->window->loadSvg(asset::plugin(pluginInstance, "res/BtnUp.svg")));
		sw->wrap();
		box.size = sw->box.size;
		
	}
};




struct BtnDwn : SvgSwitch {
	BtnDwn() {
		momentary = true;
		addFrame(APP->window->loadSvg(asset::plugin(pluginInstance, "res/BtnDwn.svg")));
		sw->wrap();
		box.size = sw->box.size;
		
	}
};








struct BtnTrigSequencer : SvgSwitch {
	BtnTrigSequencer() {
		momentary = true;
		addFrame(APP->window->loadSvg(asset::plugin(pluginInstance, "res/BtnTrigSequencer.svg")));
		sw->wrap();
		box.size = sw->box.size;
		
	}
};
 
struct BtnTrigSequencerSmall : SvgSwitch {
	BtnTrigSequencerSmall() {
		momentary = true;
		addFrame(APP->window->loadSvg(asset::plugin(pluginInstance, "res/BtnTrigSequencerSmall.svg")));
		sw->wrap();
		box.size = sw->box.size;
		
	}
};





struct WhiteKey : SvgSwitch {
	WhiteKey() {
		momentary = true;
		addFrame(APP->window->loadSvg(asset::plugin(pluginInstance, "res/WhiteKey.svg")));
		sw->wrap();
		box.size = sw->box.size;
		
	}
};



struct BlackKey : SvgSwitch {
	BlackKey() {
		momentary = true;
		addFrame(APP->window->loadSvg(asset::plugin(pluginInstance, "res/BlackKey.svg")));
		sw->wrap();
		box.size = sw->box.size;
		
	}
};



///////////////////////////////////
///      WIDGETS                ///
///////////////////////////////////



//UTILITY
extern Model *modelLFO;

extern Model *modelBPMClock;

extern Model *modelMultiple18;

extern Model *modelMultiple28;

extern Model *modelAutodafeClockDivider;

//SEQUENCERS

extern Model *modelSEQ8;

extern Model *modelSEQ16;

extern Model *modelTriggerSeq;

//FILTERS

extern Model *modelFormantFilter;

extern Model *modelMultiModeFilter;

extern Model *modelFixedFilter;

//// EFFECTS
extern Model *modelFoldBack;

extern Model *modelBitCrusher;

extern Model *modelPhaserFx;

extern Model *modelChorusFx;

extern Model *modelReverbFx;



///OSCILLATORS














extern Model *modelKeyboardModel;












