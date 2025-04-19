//**************************************************************************************
//BitCrusher Module for VCV Rack by Autodafe http://www.autodafe.net
//
//Based on code taken from the Fundamentals plugins by Andrew Belt http://www.vcvrack.com
//And part of code on musicdsp.org: http://musicdsp.org/showArchiveComment.php?ArchiveID=78
//**************************************************************************************


#include "plugin.hpp"
#include <stdlib.h>



#define SR (44100.f)  //sample rate
#define F_PI (3.14159f)

class Phaser{
public:
    Phaser()  //initialise to some usefull defaults...
        : _fb( .7f )
        , _lfoPhase( 0.f )
        , _depth( 1.f )
        , _zm1( 0.f )
    {
        Range( 440.f, 1600.f );
        Rate( .5f );
    }

    void Range( float fMin, float fMax ){ // Hz
        _dmin = fMin / (SR/2.f);
        _dmax = fMax / (SR/2.f);
    }

    void Rate( float rate ){ // cps
        _lfoInc = 2.f * F_PI * (rate / SR);
    }

    void Feedback( float fb ){ // 0 -> <1.
        _fb = fb;
    }

    void Depth( float depth ){  // 0 -> 1.
        _depth = depth;
    }

    float Update( float inSamp ){
        //calculate and update phaser sweep lfo...
        float d  = _dmin + (_dmax-_dmin) * ((sin( _lfoPhase ) + 
1.f)/2.f);
        _lfoPhase += _lfoInc;
        if( _lfoPhase >= F_PI * 2.f )
            _lfoPhase -= F_PI * 2.f;

        //update filter coeffs
        for( int i=0; i<6; i++ )
            _alps[i].Delay( d );

        //calculate output
        float y =   _alps[0].Update(
                     _alps[1].Update(
                      _alps[2].Update(
                       _alps[3].Update(
                        _alps[4].Update(
                         _alps[5].Update( inSamp + _zm1 * _fb ))))));
        _zm1 = y;

        return inSamp + y * _depth;
    }
private:
    class AllpassDelay{
    public:
        AllpassDelay()
            : _a1( 0.f )
            , _zm1( 0.f )
            {}

        void Delay( float delay ){ //sample delay time
            _a1 = (1.f - delay) / (1.f + delay);
        }

        float Update( float inSamp ){
            float y = inSamp * -_a1 + _zm1;
            _zm1 = y * _a1 + inSamp;

            return y;
        }
    private:
        float _a1, _zm1;
    };

    AllpassDelay _alps[6];

    float _dmin, _dmax; //range
    float _fb; //feedback
    float _lfoPhase;
    float _lfoInc;
    float _depth;

    float _zm1;
};





struct PhaserFx : Module{




	enum ParamIds {
		PARAM_RATE,
		PARAM_FEEDBACK,
		PARAM_DEPTH,
			NUM_PARAMS
	};
	enum InputIds {
		
		INPUT,
		NUM_INPUTS
	};
	enum OutputIds {
		OUT,
		NUM_OUTPUTS
	};


	PhaserFx();


float rate ;
    float feedback;
    float depth;

    float input;

    float out;


Phaser *pha = new Phaser();





	void process(const ProcessArgs &args);



};





PhaserFx::PhaserFx() {

config(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS);

    configParam(PhaserFx::PARAM_RATE, 0, 1, 0, "");
configParam(PhaserFx::PARAM_RATE, 0, 1, 0, "");
configParam(PhaserFx::PARAM_FEEDBACK, 0, 0.95, 0, "");
configParam(PhaserFx::PARAM_FEEDBACK, 0, 0.95, 0, "");
configParam(PhaserFx::PARAM_DEPTH, 0, 1, 0, "");
configParam(PhaserFx::PARAM_DEPTH, 0, 1, 0, "");



	//params.resize(NUM_PARAMS);
	//inputs.resize(NUM_INPUTS);
	//outputs.resize(NUM_OUTPUTS);



}








void PhaserFx::process(const ProcessArgs &args) {


	
	 rate = params[PARAM_RATE].getValue();
	 feedback = params[PARAM_FEEDBACK].getValue();
	 depth = params[PARAM_DEPTH].getValue();

	 input = inputs[INPUT].getVoltage() / 5.0;

		pha->Rate(rate);
		pha->Feedback(feedback);
		pha->Depth (depth);
	
	 out = pha->Update(input);



	outputs[OUT].value= out * 5;
	





}



 struct PhaserFxWidget : ModuleWidget {
    PhaserFxWidget(PhaserFx *module);
};

    PhaserFxWidget::PhaserFxWidget(PhaserFx *module) {
		setModule(module);



	box.size = Vec(15 * 6, 380);

	{
		SvgPanel *panel = new SvgPanel();
		panel->box.size = box.size;
		
        panel->setBackground(APP->window->loadSvg(asset::plugin(pluginInstance, "res/Phaser.svg")));
		addChild(panel); 
	}

	addChild(createWidget<ScrewSilver>(Vec(1, 0)));
	addChild(createWidget<ScrewSilver>(Vec(box.size.x - 20, 0)));
	addChild(createWidget<ScrewSilver>(Vec(1, 365)));
	addChild(createWidget<ScrewSilver>(Vec(box.size.x - 20, 365)));
      
	addParam(createParam<AutodafeKnobGreen>(Vec(25, 51), module, PhaserFx::PARAM_RATE));
    //addParam(createParam<AutodafeKnob>(Vec(25, 51), module, PhaserFx::PARAM_RATE));

	addParam(createParam<AutodafeKnobGreen>(Vec(25, 111), module, PhaserFx::PARAM_FEEDBACK));
    //addParam(createParam<AutodafeKnob>(Vec(25, 111), module, PhaserFx::PARAM_FEEDBACK));

	addParam(createParam<AutodafeKnobGreen>(Vec(25, 171), module, PhaserFx::PARAM_DEPTH));
    //addParam(createParam<AutodafeKnob>(Vec(25, 171), module, PhaserFx::PARAM_DEPTH));

	addInput(createInput<PJ301MPort>(Vec(10, 320), module, PhaserFx::INPUT));
	addOutput(createOutput<PJ301MPort>(Vec(48, 320), module, PhaserFx::OUT));
 
}
Model *modelPhaserFx = createModel<PhaserFx, PhaserFxWidget>("PhaserFx");




