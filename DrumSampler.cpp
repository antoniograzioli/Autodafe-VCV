#include "Autodafe.hpp"
#include "dsp/digital.hpp"
#include "../ext/osdialog/osdialog.h"
#include "AudioFile.h"
#include <vector>
#include "cmath"

using namespace std;


struct DrumSampler : Module {
	enum ParamIds {
		PARAM_PATH1,
		PARAM_PATH2,
		PARAM_PATH3,
		PARAM_PATH4,
		PARAM_PATH5,
		PARAM_PATH6,
		PARAM_PATH7,
		PARAM_PATH8,

		PARAM_VOL1, 
		PARAM_VOL2, 
		PARAM_VOL3, 
		PARAM_VOL4, 
		PARAM_VOL5, 
		PARAM_VOL6, 
		PARAM_VOL7, 
		PARAM_VOL8, 

/*
		PARAM_PITCH1,
		PARAM_PITCH2,
		PARAM_PITCH3,
		PARAM_PITCH4,
		PARAM_PITCH5,
		PARAM_PITCH6,
		PARAM_PITCH7,
		PARAM_PITCH8,

		*/


		PARAM_VOLMIX, 


		NUM_PARAMS 
	};
	enum InputIds {
		TRIG_INPUT1,
		TRIG_INPUT2,
		TRIG_INPUT3,
		TRIG_INPUT4,
		TRIG_INPUT5,
		TRIG_INPUT6,
		TRIG_INPUT7,
		TRIG_INPUT8,

		NUM_INPUTS
	};
	enum OutputIds {
		OUT_OUTPUT,
		OUT1, OUT2, OUT3, OUT4, OUT5, OUT6, OUT7, OUT8,
		NUM_OUTPUTS
	};
	enum LightIds {

		LIGHT,
		

		NUM_LIGHTS=LIGHT+8
	};
	
	

	string lastPath[8];
	string lastGlobalPath;
	string lastPathReload[8];
	AudioFile<double> audioFile[8][4];
	

	int samplePos[8][4];


	float outvalue[8][4];

	char loadpath [8];

int oldSampleRate;


int index1=1;
int index2=1;
int index3=1;
int index4=1;
int index5=1;
int index6=1;
int index7=1;
int index8=1;


float trig01;
float trig02;
float trig03;
float trig04;
float trig05;
float trig06;
float trig07;
float trig08;


float out1, out2, out3, out4, out5, out6, out7, out8;


	
	string fileDesc;
	bool fileLoaded[8];

	

	DrumSampler() : Module(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS, NUM_LIGHTS) 




	{ 



	}

	void step() override;
	
	void loadSample(std::string path, int index);



	void reset() {
		
		


		}



	
	// persistence
	
	json_t *toJson() override {
		json_t *rootJ = json_object();
		// lastPath
		json_object_set_new(rootJ, "lastPath0", json_string(lastPath[0].c_str()));
		json_object_set_new(rootJ, "lastPath1", json_string(lastPath[1].c_str()));	
		json_object_set_new(rootJ, "lastPath2", json_string(lastPath[2].c_str()));	
		json_object_set_new(rootJ, "lastPath3", json_string(lastPath[3].c_str()));	
		json_object_set_new(rootJ, "lastPath4", json_string(lastPath[4].c_str()));	
		json_object_set_new(rootJ, "lastPath5", json_string(lastPath[5].c_str()));	
		json_object_set_new(rootJ, "lastPath6", json_string(lastPath[6].c_str()));	
		json_object_set_new(rootJ, "lastPath7", json_string(lastPath[7].c_str()));	

		return rootJ;
	}

	void fromJson(json_t *rootJ) override {
		// lastPath
		json_t *lastPathJ0 = json_object_get(rootJ, "lastPath0");
		if (lastPathJ0) {
			lastPath[0] = json_string_value(lastPathJ0);
			loadSample(lastPath[0],0);
		}

json_t *lastPathJ1 = json_object_get(rootJ, "lastPath1");
		if (lastPathJ1) {
			lastPath[1] = json_string_value(lastPathJ1);
			loadSample(lastPath[1],1);
		}


		json_t *lastPathJ2 = json_object_get(rootJ, "lastPath2");
		if (lastPathJ2) {
			lastPath[2] = json_string_value(lastPathJ2);
			loadSample(lastPath[2],2);
		}


		json_t *lastPathJ3 = json_object_get(rootJ, "lastPath3");
		if (lastPathJ3) {
			lastPath[3] = json_string_value(lastPathJ3);
			loadSample(lastPath[3],3);
		}



		json_t *lastPathJ4 = json_object_get(rootJ, "lastPath4");
		if (lastPathJ4) {
			lastPath[4] = json_string_value(lastPathJ4);
			loadSample(lastPath[4],4);
		}



		json_t *lastPathJ5 = json_object_get(rootJ, "lastPath5");
		if (lastPathJ5) {
			lastPath[5] = json_string_value(lastPathJ5);
			loadSample(lastPath[5],5);
		}


		json_t *lastPathJ6 = json_object_get(rootJ, "lastPath6");
		if (lastPathJ6) {
			lastPath[6] = json_string_value(lastPathJ6);
			loadSample(lastPath[6],6);
		}


		json_t *lastPathJ7 = json_object_get(rootJ, "lastPath7");
		if (lastPathJ7) {
			lastPath[7] = json_string_value(lastPathJ7);
			loadSample(lastPath[7],7);
		}







	}
};

void DrumSampler::loadSample(std::string path, int index) {

for (int z = 0; z < 4; z++) {

	if (audioFile[index][z].load (path.c_str())) {
		audioFile[index][z].setSampleRate(engineGetSampleRate());
		fileLoaded[index] = true;
		lights[LIGHT+index].value=1;

		
		
	}
	else {
		fileLoaded[index] = false;
	}

}
}


void DrumSampler::step() {
 	





//change samplerate?
 if (engineGetSampleRate()!=oldSampleRate)

 {
for (int i = 0; i < 8; i++) {

	for (int z = 0; z < 4; z++) 
	{
loadSample(lastPath[i], i);
		audioFile[i][z].setSampleRate(engineGetSampleRate());
		
	}

}

}







	
if(inputs[TRIG_INPUT1].active){

if (inputs[TRIG_INPUT1].value>trig01) {
if (index1<3){index1++;}else{index1=0;}
		samplePos[0][index1]= 0;
		
	}
}

if(inputs[TRIG_INPUT2].active){
if (inputs[TRIG_INPUT2].value>trig02) {
if (index2<3){index2++;}else{index2=0;}
		samplePos[1][index2]= 0;
		
	}

}


if(inputs[TRIG_INPUT3].active){
if (inputs[TRIG_INPUT3].value>trig03) {
if (index3<3){index3++;}else{index3=0;}
		samplePos[2][index3] = 0;
	}
}



if(inputs[TRIG_INPUT4].active){
if (inputs[TRIG_INPUT4].value>trig04) {
if (index4<3){index4++;}else{index4=0;}
		samplePos[3][index4] = 0;
	}

}


if(inputs[TRIG_INPUT5].active){

	if (inputs[TRIG_INPUT5].value>trig05) {
if (index5<3){index5++;}else{index5=0;}
		samplePos[4][index5] = 0;
	}

}




if(inputs[TRIG_INPUT6].active){

	if (inputs[TRIG_INPUT6].value>trig06) {
if (index6<3){index6++;}else{index6=0;}
		samplePos[5][index6] = 0;
	}



}





if(inputs[TRIG_INPUT7].active){

	if (inputs[TRIG_INPUT7].value>trig07) {
	if (index7<3){index7++;}else{index7=0;}
		samplePos[6][index7] = 0;
	}


}





if(inputs[TRIG_INPUT8].active){

	if (inputs[TRIG_INPUT8].value>trig08) {
if (index8<3){index8++;}else{index8=0;}
		samplePos[7][index8] = 0;
	}
}




/*

for (int i = 0; i < numSamples; i++) {

	
	if ((play[i][index1]) && (samplePos[i][index1] < audioFile[i][index1].getNumSamplesPerChannel())) {
		if (audioFile[i][index1].getNumChannels() == 1)
			//outputs[OUT_OUTPUT].value = 5 * audioFile[i].samples[0][samplePos[i]]; 
			outvalue[i][index1] = 5 * audioFile[i][index1].samples[0][samplePos[i][index1]]; 
		else if (audioFile[i][index1].getNumChannels() ==2)
			//outputs[OUT_OUTPUT].value = 5 * (audioFile[i].samples[0][samplePos[i]] + audioFile[i].samples[2][samplePos[i]]) / 2; 
			outvalue[i][index1] = 5 * (audioFile[i][index1].samples[0][samplePos[i][index1]] + audioFile[i][index1].samples[2][samplePos[i][index1]]) / 2; 
		samplePos[i][index1]++;
	}
	else if (samplePos[i][index1] == audioFile[i][index1].getNumSamplesPerChannel())
	{ 
		play[i][index1] = false;
	}

	
}
*/



if (samplePos[0][index1] < audioFile[0][index1].getNumSamplesPerChannel()) {
		if (audioFile[0][index1].getNumChannels() == 1)
			//outputs[OUT_OUTPUT].value = 5 * audioFile[0].samples[0][samplePos[0]]; 
			outvalue[0][index1] = 5 * audioFile[0][index1].samples[0][samplePos[0][index1]]; 
		else if (audioFile[0][index1].getNumChannels() ==2)
			//outputs[OUT_OUTPUT].value = 5 * (audioFile[0].samples[0][samplePos[0]] + audioFile[0].samples[2][samplePos[0]]) / 2; 
			outvalue[0][index1] = 5 * (audioFile[0][index1].samples[0][samplePos[0][index1]] + audioFile[0][index1].samples[2][samplePos[0][index1]]) / 2; 
		samplePos[0][index1]++;

	}
	





if (samplePos[1][index2] < audioFile[1][index2].getNumSamplesPerChannel()) {
		if (audioFile[1][index2].getNumChannels() == 1)
			//outputs[OUT_OUTPUT].value = 5 * audioFile[1].samples[1][samplePos[1]]; 
			outvalue[1][index2] = 5 * audioFile[1][index2].samples[0][samplePos[1][index2]]; 
		else if (audioFile[1][index2].getNumChannels() ==2)
			//outputs[OUT_OUTPUT].value = 5 * (audioFile[1].samples[1][samplePos[1]] + audioFile[1].samples[1][samplePos[1]]) / 2; 
			outvalue[1][index2] = 5 * (audioFile[1][index2].samples[0][samplePos[1][index2]] + audioFile[1][index2].samples[1][samplePos[1][index2]]) / 2; 
		samplePos[1][index2]++;
	}
	



if (samplePos[2][index3] < audioFile[2][index3].getNumSamplesPerChannel()) {
		if (audioFile[2][index3].getNumChannels() == 1)
			//outputs[OUT_OUTPUT].value = 5 * audioFile[2].samples[1][samplePos[2]]; 
			outvalue[2][index3] = 5 * audioFile[2][index3].samples[0][samplePos[2][index3]]; 
		else if (audioFile[2][index3].getNumChannels() ==2)
			//outputs[OUT_OUTPUT].value = 5 * (audioFile[2].samples[1][samplePos[2]] + audioFile[2].samples[1][samplePos[2]]) / 2; 
			outvalue[2][index3] = 5 * (audioFile[2][index3].samples[0][samplePos[2][index3]] + audioFile[2][index3].samples[1][samplePos[2][index3]]) / 2; 
		samplePos[2][index3]++;
	}





if (samplePos[3][index4] < audioFile[3][index4].getNumSamplesPerChannel()) {
		if (audioFile[3][index4].getNumChannels() == 1)
			//outputs[OUT_OUTPUT].value = 5 * audioFile[3].samples[1][samplePos[3]]; 
			outvalue[3][index4] = 5 * audioFile[3][index4].samples[0][samplePos[3][index4]]; 
		else if (audioFile[3][index4].getNumChannels() ==2)
			//outputs[OUT_OUTPUT].value = 5 * (audioFile[3].samples[1][samplePos[3]] + audioFile[3].samples[1][samplePos[3]]) / 2; 
			outvalue[3][index4] = 5 * (audioFile[3][index4].samples[0][samplePos[3][index4]] + audioFile[3][index4].samples[1][samplePos[3][index4]]) / 2; 
		samplePos[3][index4]++;
	}


	




if (samplePos[4][index5] < audioFile[4][index5].getNumSamplesPerChannel()) {
		if (audioFile[4][index5].getNumChannels() == 1)
			//outputs[OUT_OUTPUT].value = 5 * audioFile[4].samples[1][samplePos[4]]; 
			outvalue[4][index5] = 5 * audioFile[4][index5].samples[0][samplePos[4][index5]]; 
		else if (audioFile[4][index5].getNumChannels() ==2)
			//outputs[OUT_OUTPUT].value = 5 * (audioFile[4].samples[1][samplePos[4]] + audioFile[4].samples[1][samplePos[4]]) / 2; 
			outvalue[4][index5] = 5 * (audioFile[4][index5].samples[0][samplePos[4][index5]] + audioFile[4][index5].samples[1][samplePos[4][index5]]) / 2; 
		samplePos[4][index5]++;
	}




if (samplePos[5][index6] < audioFile[5][index6].getNumSamplesPerChannel()) {
		if (audioFile[5][index6].getNumChannels() == 1)
			//outputs[OUT_OUTPUT].value = 5 * audioFile[5].samples[1][samplePos[5]]; 
			outvalue[5][index6] = 5 * audioFile[5][index6].samples[0][samplePos[5][index6]]; 
		else if (audioFile[5][index6].getNumChannels() ==2)
			//outputs[OUT_OUTPUT].value = 5 * (audioFile[5].samples[1][samplePos[5]] + audioFile[5].samples[1][samplePos[5]]) / 2; 
			outvalue[5][index6] = 5 * (audioFile[5][index6].samples[0][samplePos[5][index6]] + audioFile[5][index6].samples[1][samplePos[5][index6]]) / 2; 
		samplePos[5][index6]++;
	}




	if (samplePos[6][index7] < audioFile[6][index7].getNumSamplesPerChannel()) {
		if (audioFile[6][index7].getNumChannels() == 1)
			//outputs[OUT_OUTPUT].value = 5 * audioFile[6].samples[1][samplePos[6]]; 
			outvalue[6][index7] = 5 * audioFile[6][index7].samples[0][samplePos[6][index7]]; 
		else if (audioFile[6][index7].getNumChannels() ==2)
			//outputs[OUT_OUTPUT].value = 5 * (audioFile[6].samples[1][samplePos[6]] + audioFile[6].samples[1][samplePos[6]]) / 2; 
			outvalue[6][index7] = 5 * (audioFile[6][index7].samples[0][samplePos[6][index7]] + audioFile[6][index7].samples[1][samplePos[6][index7]]) / 2; 
		samplePos[6][index7]++;
	}





if (samplePos[7][index8] < audioFile[7][index8].getNumSamplesPerChannel()) {
		if (audioFile[7][index8].getNumChannels() == 1)
			//outputs[OUT_OUTPUT].value = 5 * audioFile[7].samples[1][samplePos[7]]; 
			outvalue[7][index8] = 5 * audioFile[7][index8].samples[0][samplePos[7][index8]]; 
		else if (audioFile[7][index8].getNumChannels() ==2)
			//outputs[OUT_OUTPUT].value = 5 * (audioFile[7].samples[1][samplePos[7]] + audioFile[7].samples[1][samplePos[7]]) / 2; 
			outvalue[7][index8] = 5 * (audioFile[7][index8].samples[0][samplePos[7][index8]] + audioFile[7][index8].samples[1][samplePos[7][index8]]) / 2; 
		samplePos[7][index8]++;
	}



if(inputs[TRIG_INPUT1].active){out1=outvalue[0][index1];} else {out1=0;}
if(inputs[TRIG_INPUT2].active){out2=outvalue[1][index2];} else {out2=0;}
if(inputs[TRIG_INPUT3].active){out3=outvalue[2][index3];} else {out3=0;}
if(inputs[TRIG_INPUT4].active){out4=outvalue[3][index4];} else {out4=0;}
if(inputs[TRIG_INPUT5].active){out5=outvalue[4][index5];} else {out5=0;}
if(inputs[TRIG_INPUT6].active){out6=outvalue[5][index6];} else {out6=0;}
if(inputs[TRIG_INPUT7].active){out7=outvalue[6][index7];} else {out7=0;}
if(inputs[TRIG_INPUT8].active){out8=outvalue[7][index8];} else {out8=0;}



		outputs[OUT_OUTPUT].value=params[PARAM_VOLMIX].value*(out1*params[PARAM_VOL1].value+out2*params[PARAM_VOL2].value+out3*params[PARAM_VOL3].value+out4*params[PARAM_VOL4].value+out5*params[PARAM_VOL5].value+out6*params[PARAM_VOL6].value+out7*params[PARAM_VOL7].value+out8*params[PARAM_VOL8].value);

		outputs[OUT1].value=out1*params[PARAM_VOL1].value;
		outputs[OUT2].value=out2*params[PARAM_VOL2].value;
		outputs[OUT3].value=out3*params[PARAM_VOL3].value;
		outputs[OUT4].value=out4*params[PARAM_VOL4].value;
		outputs[OUT5].value=out5*params[PARAM_VOL5].value;
		outputs[OUT6].value=out6*params[PARAM_VOL6].value;
		outputs[OUT7].value=out7*params[PARAM_VOL7].value;
		outputs[OUT8].value=out8*params[PARAM_VOL8].value;




	 trig01=inputs[TRIG_INPUT1].value;
	 trig02=inputs[TRIG_INPUT2].value;
	 trig03=inputs[TRIG_INPUT3].value;
	 trig04=inputs[TRIG_INPUT4].value;
	 trig05=inputs[TRIG_INPUT5].value;
	 trig06=inputs[TRIG_INPUT6].value;
	 trig07=inputs[TRIG_INPUT7].value;
	 trig08=inputs[TRIG_INPUT8].value;

oldSampleRate= engineGetSampleRate();


	}















DrumSamplerWidget::DrumSamplerWidget() {
	DrumSampler *module = new DrumSampler();
	setModule(module);
	box.size = Vec(15*22, 380);

	{
		SVGPanel *panel = new SVGPanel();
		panel->box.size = box.size;
		panel->setBackground(SVG::load(assetPlugin(plugin, "res/DrumSampler.svg")));
		addChild(panel);
	}

	addChild(createScrew<ScrewSilver>(Vec(15, 0)));
	addChild(createScrew<ScrewSilver>(Vec(box.size.x-30, 0)));
	addChild(createScrew<ScrewSilver>(Vec(15, 365)));
	addChild(createScrew<ScrewSilver>(Vec(box.size.x-30, 365)));
	
	
		
	
		
	addInput(createInput<PJ301MPort>(Vec(50, 50), module, DrumSampler::TRIG_INPUT1));
	addInput(createInput<PJ301MPort>(Vec(50, 90), module, DrumSampler::TRIG_INPUT2));
	addInput(createInput<PJ301MPort>(Vec(50, 130), module, DrumSampler::TRIG_INPUT3));
	addInput(createInput<PJ301MPort>(Vec(50, 170), module, DrumSampler::TRIG_INPUT4));
	addInput(createInput<PJ301MPort>(Vec(50, 210), module, DrumSampler::TRIG_INPUT5));
	addInput(createInput<PJ301MPort>(Vec(50, 250), module, DrumSampler::TRIG_INPUT6));
	addInput(createInput<PJ301MPort>(Vec(50, 290), module, DrumSampler::TRIG_INPUT7));
	addInput(createInput<PJ301MPort>(Vec(50, 330), module, DrumSampler::TRIG_INPUT8));
	


	addParam(createParam<AutodafeKnobRed>(Vec(115, 45),  module, DrumSampler::PARAM_VOL1, 0, 1, 1));
	addParam(createParam<AutodafeKnobRed>(Vec(115, 85),  module, DrumSampler::PARAM_VOL2, 0, 1, 1));
	addParam(createParam<AutodafeKnobRed>(Vec(115, 125), module, DrumSampler::PARAM_VOL3, 0, 1, 1));
	addParam(createParam<AutodafeKnobRed>(Vec(115, 165), module, DrumSampler::PARAM_VOL4, 0, 1, 1));
	addParam(createParam<AutodafeKnobRed>(Vec(115, 205), module, DrumSampler::PARAM_VOL5, 0, 1, 1));
	addParam(createParam<AutodafeKnobRed>(Vec(115, 245), module, DrumSampler::PARAM_VOL6, 0, 1, 1));
	addParam(createParam<AutodafeKnobRed>(Vec(115, 285), module, DrumSampler::PARAM_VOL7, 0, 1, 1));
	addParam(createParam<AutodafeKnobRed>(Vec(115, 325), module, DrumSampler::PARAM_VOL8, 0, 1, 1));





addChild(createLight<MediumLight<RedLight>>(Vec(165, 55), module, DrumSampler::LIGHT+0));
addChild(createLight<MediumLight<RedLight>>(Vec(165, 95), module, DrumSampler::LIGHT+1));
addChild(createLight<MediumLight<RedLight>>(Vec(165, 135), module, DrumSampler::LIGHT+2));
addChild(createLight<MediumLight<RedLight>>(Vec(165, 175), module, DrumSampler::LIGHT+3));
addChild(createLight<MediumLight<RedLight>>(Vec(165, 215), module, DrumSampler::LIGHT+4));
addChild(createLight<MediumLight<RedLight>>(Vec(165, 255), module, DrumSampler::LIGHT+5));
addChild(createLight<MediumLight<RedLight>>(Vec(165, 295), module, DrumSampler::LIGHT+6));
addChild(createLight<MediumLight<RedLight>>(Vec(165, 335), module, DrumSampler::LIGHT+7));


	addOutput(createOutput<PJ301MPort>(Vec(200, 50), module, DrumSampler::OUT1));
	addOutput(createOutput<PJ301MPort>(Vec(200, 90), module, DrumSampler::OUT2));
	addOutput(createOutput<PJ301MPort>(Vec(200, 130), module, DrumSampler::OUT3)); 
	addOutput(createOutput<PJ301MPort>(Vec(200, 170), module, DrumSampler::OUT4));
	addOutput(createOutput<PJ301MPort>(Vec(200, 210), module, DrumSampler::OUT5));
	addOutput(createOutput<PJ301MPort>(Vec(200, 250), module, DrumSampler::OUT6));
	addOutput(createOutput<PJ301MPort>(Vec(200, 290), module, DrumSampler::OUT7)); 
	addOutput(createOutput<PJ301MPort>(Vec(200, 330), module, DrumSampler::OUT8));



	addParam(createParam<AutodafeKnobRedBig>(Vec(240, 130), module, DrumSampler::PARAM_VOLMIX, 0, 1, 1));
	addOutput(createOutput<PJ301MPort>(Vec(250, 190), module, DrumSampler::OUT_OUTPUT));
}




struct DrumSamplerItem0 : MenuItem {
	DrumSampler *DrumSampler0;
	void onAction(EventAction &e) override {

	std::string dir;	
if (DrumSampler0->lastPath[0].empty() && DrumSampler0->lastGlobalPath.empty() )
				{
			
					std::string dir =assetLocal("");
				}
			else if (DrumSampler0->lastPath[0].empty())
				{

					std::string dir=extractDirectory(DrumSampler0->lastGlobalPath);
				}
			else if (DrumSampler0->lastGlobalPath.empty())
			{	
				std::string dir=extractDirectory(DrumSampler0->lastPath[0]);
			}



		//std::string dir = DrumSampler0->lastPath[0].empty() ? assetLocal("") : extractDirectory(DrumSampler0->lastPath[0]);
		char *path = osdialog_file(OSDIALOG_OPEN, dir.c_str(), NULL, NULL);
		if (path) {
			
			DrumSampler0->loadSample(path, 0);
			DrumSampler0->lastPathReload[0]=path;
			for (int z = 0; z < 4; z++) {DrumSampler0->samplePos[0][z]= 0;}
			DrumSampler0->lastPath[0] = path;
			DrumSampler0->lastGlobalPath = path;

			free(path);
		}
	}
};

struct DrumSamplerItem1 : MenuItem {
	DrumSampler *DrumSampler1;
	void onAction(EventAction &e) override {
		
std::string dir;

if (DrumSampler1->lastPath[1].empty() && DrumSampler1->lastGlobalPath.empty() )
				{
			
					std::string dir =assetLocal("");
				}
			else if (DrumSampler1->lastPath[1].empty())
				{

					std::string dir=extractDirectory(DrumSampler1->lastGlobalPath);
				}
			else if (DrumSampler1->lastGlobalPath.empty())
			{	
				std::string dir=extractDirectory(DrumSampler1->lastPath[1]);
			}




		//std::string dir = DrumSampler1->lastPath[1].empty() ? assetLocal("") : extractDirectory(DrumSampler1->lastPath[1]);
		char *path = osdialog_file(OSDIALOG_OPEN, dir.c_str(), NULL, NULL);
		if (path) {
			
			DrumSampler1->loadSample(path, 1);
			for (int z = 0; z < 4; z++) {DrumSampler1->samplePos[1][z] = 0;}
			DrumSampler1->lastPath[1] = path;
		DrumSampler1->lastGlobalPath = path;
			free(path);
		}
	}
};



struct DrumSamplerItem2 : MenuItem {
	DrumSampler *DrumSampler2;
	void onAction(EventAction &e) override {


std::string dir;

if (DrumSampler2->lastPath[2].empty() && DrumSampler2->lastGlobalPath.empty() )
				{
			
					std::string dir =assetLocal("");
				}
			else if (DrumSampler2->lastPath[2].empty())
				{

					std::string dir=extractDirectory(DrumSampler2->lastGlobalPath);
				}
			else if (DrumSampler2->lastGlobalPath.empty())
			{	
				std::string dir=extractDirectory(DrumSampler2->lastPath[2]);
			}


		
		//std::string dir = DrumSampler2->lastPath[2].empty() ? assetLocal("") : extractDirectory(DrumSampler2->lastPath[2]);
		char *path = osdialog_file(OSDIALOG_OPEN, dir.c_str(), NULL, NULL);
		if (path) {
			
			DrumSampler2->loadSample(path, 2);
			for (int z = 0; z < 4; z++) {DrumSampler2->samplePos[2][z] = 0;}
			DrumSampler2->lastPath[2] = path;
		DrumSampler2->lastGlobalPath = path;
			free(path);
		}
	}
};






struct DrumSamplerItem3 : MenuItem {
	DrumSampler *DrumSampler3;
	void onAction(EventAction &e) override {



		std::string dir;

if (DrumSampler3->lastPath[3].empty() && DrumSampler3->lastGlobalPath.empty() )
				{
			
					std::string dir =assetLocal("");
				}
			else if (DrumSampler3->lastPath[3].empty())
				{

					std::string dir=extractDirectory(DrumSampler3->lastGlobalPath);
				}
			else if (DrumSampler3->lastGlobalPath.empty())
			{	
				std::string dir=extractDirectory(DrumSampler3->lastPath[3]);
			}
		
		//std::string dir = DrumSampler3->lastPath[3].empty() ? assetLocal("") : extractDirectory(DrumSampler3->lastPath[3]);
		char *path = osdialog_file(OSDIALOG_OPEN, dir.c_str(), NULL, NULL);
		if (path) {
			
			DrumSampler3->loadSample(path, 3);
			for (int z = 0; z < 4; z++) {DrumSampler3->samplePos[4][z] = 0;}
			DrumSampler3->lastPath[3] = path;
		DrumSampler3->lastGlobalPath = path;
			free(path);
		}
	}
};




struct DrumSamplerItem4 : MenuItem {
	DrumSampler *DrumSampler4;
	void onAction(EventAction &e) override {



		std::string dir;

if (DrumSampler4->lastPath[4].empty() && DrumSampler4->lastGlobalPath.empty() )
				{
			
					std::string dir =assetLocal("");
				}
			else if (DrumSampler4->lastPath[4].empty())
				{

					std::string dir=extractDirectory(DrumSampler4->lastGlobalPath);
				}
			else if (DrumSampler4->lastGlobalPath.empty())
			{	
				std::string dir=extractDirectory(DrumSampler4->lastPath[4]);
			}
		
		//std::string dir = DrumSampler4->lastPath[4].empty() ? assetLocal("") : extractDirectory(DrumSampler4->lastPath[4]);
		char *path = osdialog_file(OSDIALOG_OPEN, dir.c_str(), NULL, NULL);
		if (path) {
			
			DrumSampler4->loadSample(path, 4);
			for (int z = 0; z < 4; z++) {DrumSampler4->samplePos[4][z] = 0;}
			DrumSampler4->lastPath[4] = path;
		DrumSampler4->lastGlobalPath = path;
			free(path);
		}
	}
};



struct DrumSamplerItem5 : MenuItem {
	DrumSampler *DrumSampler5;
	void onAction(EventAction &e) override {

std::string dir;

if (DrumSampler5->lastPath[5].empty() && DrumSampler5->lastGlobalPath.empty() )
				{
			
					std::string dir =assetLocal("");
				}
			else if (DrumSampler5->lastPath[5].empty())
				{

					std::string dir=extractDirectory(DrumSampler5->lastGlobalPath);
				}
			else if (DrumSampler5->lastGlobalPath.empty())
			{	
				std::string dir=extractDirectory(DrumSampler5->lastPath[5]);
			}


		
		//std::string dir = DrumSampler5->lastPath[5].empty() ? assetLocal("") : extractDirectory(DrumSampler5->lastPath[5]);
		char *path = osdialog_file(OSDIALOG_OPEN, dir.c_str(), NULL, NULL);
		if (path) {
			
			DrumSampler5->loadSample(path, 5);
			for (int z = 0; z < 4; z++) {DrumSampler5->samplePos[5][z]= 0;}
			DrumSampler5->lastPath[5] = path;
		DrumSampler5->lastGlobalPath = path;
			free(path);
		}
	}
};



struct DrumSamplerItem6 : MenuItem {
	DrumSampler *DrumSampler6;
	void onAction(EventAction &e) override {
		
		std::string dir;

if (DrumSampler6->lastPath[6].empty() && DrumSampler6->lastGlobalPath.empty() )
				{
			
					std::string dir =assetLocal("");
				}
			else if (DrumSampler6->lastPath[6].empty())
				{

					std::string dir=extractDirectory(DrumSampler6->lastGlobalPath);
				}
			else if (DrumSampler6->lastGlobalPath.empty())
			{	
				std::string dir=extractDirectory(DrumSampler6->lastPath[6]);
			}



		//std::string dir = DrumSampler6->lastPath[6].empty() ? assetLocal("") : extractDirectory(DrumSampler6->lastPath[6]);
		char *path = osdialog_file(OSDIALOG_OPEN, dir.c_str(), NULL, NULL);
		if (path) {
			
			DrumSampler6->loadSample(path, 6);
			for (int z = 0; z < 4; z++) {DrumSampler6->samplePos[6][z] = 0;}
			DrumSampler6->lastPath[6] = path;
		DrumSampler6->lastGlobalPath = path;
			free(path);
		}
	}
};




struct DrumSamplerItem7 : MenuItem {
	DrumSampler *DrumSampler7;
	void onAction(EventAction &e) override {
		
		std::string dir;

if (DrumSampler7->lastPath[7].empty() && DrumSampler7->lastGlobalPath.empty() )
				{
			
					std::string dir =assetLocal("");
				}
			else if (DrumSampler7->lastPath[7].empty())
				{

					std::string dir=extractDirectory(DrumSampler7->lastGlobalPath);
				}
			else if (DrumSampler7->lastGlobalPath.empty())
			{	
				std::string dir=extractDirectory(DrumSampler7->lastPath[7]);
			}


		//std::string dir = DrumSampler7->lastPath[7].empty() ? assetLocal("") : extractDirectory(DrumSampler7->lastPath[7]);
		char *path = osdialog_file(OSDIALOG_OPEN, dir.c_str(), NULL, NULL);
		if (path) {
			
			DrumSampler7->loadSample(path, 7);
			for (int z = 0; z < 4; z++) {DrumSampler7->samplePos[7][z] = 0;}
			DrumSampler7->lastPath[7] = path;
		DrumSampler7->lastGlobalPath = path;
			free(path);
		}
	}
};






















Menu *DrumSamplerWidget::createContextMenu() {
	Menu *menu = ModuleWidget::createContextMenu();

	MenuLabel *spacerLabel = new MenuLabel();
	menu->pushChild(spacerLabel);

	DrumSampler *DrumSampler = dynamic_cast<struct DrumSampler*>(module);
	assert(DrumSampler);

	DrumSamplerItem0 *sampleItem0 = new DrumSamplerItem0();
	sampleItem0->text = "Load sample 01";
	sampleItem0->rightText += (DrumSampler->fileLoaded[0] == true) ? "✔" : "";
	sampleItem0->DrumSampler0 = DrumSampler;
	menu->pushChild(sampleItem0);


	DrumSamplerItem1 *sampleItem1 = new DrumSamplerItem1();
	sampleItem1->text = "Load sample 02";
	sampleItem1->rightText += (DrumSampler->fileLoaded[1] == true) ? "✔" : "";
	sampleItem1->DrumSampler1 = DrumSampler;
	menu->pushChild(sampleItem1);


	DrumSamplerItem2 *sampleItem2 = new DrumSamplerItem2();
	sampleItem2->text = "Load sample 03";
	sampleItem2->rightText += (DrumSampler->fileLoaded[2] == true) ? "✔" : "";
	sampleItem2->DrumSampler2 = DrumSampler;
	menu->pushChild(sampleItem2);


	DrumSamplerItem3 *sampleItem3 = new DrumSamplerItem3();
	sampleItem3->text = "Load sample 04";
	sampleItem3->rightText += (DrumSampler->fileLoaded[3] == true) ? "✔" : "";
	sampleItem3->DrumSampler3 = DrumSampler;
	menu->pushChild(sampleItem3);


	DrumSamplerItem4 *sampleItem4 = new DrumSamplerItem4();
	sampleItem4->text = "Load sample 05";
	sampleItem4->rightText += (DrumSampler->fileLoaded[4] == true) ? "✔" : "";
	sampleItem4->DrumSampler4 = DrumSampler;
	menu->pushChild(sampleItem4);


	DrumSamplerItem5 *sampleItem5 = new DrumSamplerItem5();
	sampleItem5->text = "Load sample 06";
	sampleItem5->rightText += (DrumSampler->fileLoaded[5] == true) ? "✔" : "";
	sampleItem5->DrumSampler5 = DrumSampler;
	menu->pushChild(sampleItem5);


	DrumSamplerItem6 *sampleItem6 = new DrumSamplerItem6();
	sampleItem6->text = "Load sample 07";
	sampleItem6->rightText += (DrumSampler->fileLoaded[6] == true) ? "✔" : "";
	sampleItem6->DrumSampler6 = DrumSampler;
	menu->pushChild(sampleItem6);


	DrumSamplerItem7 *sampleItem7 = new DrumSamplerItem7();
	sampleItem7->text = "Load sample 08";
	sampleItem7->rightText += (DrumSampler->fileLoaded[7] == true) ? "✔" : "";
	sampleItem7->DrumSampler7 = DrumSampler;
	menu->pushChild(sampleItem7);




	return menu;
}
