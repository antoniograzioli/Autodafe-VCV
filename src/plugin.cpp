#include "plugin.hpp"
#include <math.h>








Plugin *pluginInstance;

void init(rack::Plugin *p) {
	pluginInstance = p;
	
	
	

p->addModel(modelMultiple18);

p->addModel(modelMultiple28);

p->addModel(modelLFO);

p->addModel(modelKeyboardModel);

p->addModel(modelBPMClock);

p->addModel(modelAutodafeClockDivider);

p->addModel(modelSEQ8);

p->addModel(modelSEQ16);

p->addModel(modelTriggerSeq);

p->addModel(modelFixedFilter);

p->addModel(modelMultiModeFilter);

p->addModel(modelFormantFilter);

p->addModel(modelFoldBack);

p->addModel(modelBitCrusher);

p->addModel(modelPhaserFx);

p->addModel(modelChorusFx);

p->addModel(modelReverbFx);


	

	}


