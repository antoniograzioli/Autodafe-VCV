//**************************************************************************************
//Waves Module for VCV Rack by Autodafe http://www.autodafe.net
//
//Based on code taken from the Fundamentals plugins by Andrew Belt http://www.vcvrack.com
//And part of code on musicdsp.org: http://musicdsp.org/showArchiveComment.php?ArchiveID=78
//**************************************************************************************


#include "Autodafe.hpp"
#include <stdlib.h>
#include "dsp/digital.hpp"
#include "dsp/decimator.hpp"


 

#include "stk/include/BlitSquare.h"

#include "stk/include/FileLoop.h"

#define FONT_FILE      assetPlugin(plugin, "res/Segment7Standard.ttf")
  

double CosineInterpolateWaves(
   double y1,double y2,
   double mu)
{
   double mu2;

   mu2 = (1-cos(mu*M_PI))/2;
   return(y1*(1-mu2)+y2*mu2);
}



using namespace stk;


struct WavesModel : Module{
	enum ParamIds {
		BANKNUM,
		PARAM_FREQ,
		PARAM_FINE,
		PARAM_FREQ_CV,
		PARAM_VOL,
		PARAM_TAB,

		TABUP,
		TABDWN,

		BANKUP,
		BANKDWN,



		
			NUM_PARAMS
	};
	enum InputIds {
		INPUT_FREQ_CV,
		INPUT_TAB_CV,
		NUM_INPUTS
	};
	enum OutputIds {
		

OUT_WAVEFILE,
		NUM_OUTPUTS
	};


	SchmittTrigger bankSelector;

float lastPlayed;

float gSampleRate;
float oldSampleRate;

int table=0;



int bank=1;
int tableSelector=0;


int paramtableSelector;
int oldtableSelector=0;
int tableincrement=0;
int inc =0;


int banks=17;



SchmittTrigger trigUp;
SchmittTrigger trigDwn;

SchmittTrigger bankUp;
SchmittTrigger bankDwn;


	WavesModel();

	
	BlitSquare *waveSquare = new BlitSquare(5.0);
Biquad *bq = new Biquad();






 

//BANK1

	FileLoop *waveFile0= new FileLoop("plugins/Autodafe/samples/table1/00.wav", true);
	FileLoop *waveFile1= new FileLoop("plugins/Autodafe/samples/table1/01.wav", true );
	FileLoop *waveFile2= new FileLoop("plugins/Autodafe/samples/table1/02.wav", true );
FileLoop *waveFile3= new FileLoop("plugins/Autodafe/samples/table1/03.wav", true );
FileLoop *waveFile4= new FileLoop("plugins/Autodafe/samples/table1/04.wav", true );
FileLoop *waveFile5= new FileLoop("plugins/Autodafe/samples/table1/05.wav", true );
FileLoop *waveFile6= new FileLoop("plugins/Autodafe/samples/table1/06.wav", true );
FileLoop *waveFile7= new FileLoop("plugins/Autodafe/samples/table1/07.wav", true );
FileLoop *waveFile8= new FileLoop("plugins/Autodafe/samples/table1/08.wav", true );
FileLoop *waveFile9= new FileLoop("plugins/Autodafe/samples/table1/09.wav", true );
FileLoop *waveFile10= new FileLoop("plugins/Autodafe/samples/table1/10.wav", true );
FileLoop *waveFile11= new FileLoop("plugins/Autodafe/samples/table1/11.wav", true );
FileLoop *waveFile12= new FileLoop("plugins/Autodafe/samples/table1/12.wav", true );
FileLoop *waveFile13= new FileLoop("plugins/Autodafe/samples/table1/13.wav", true );
FileLoop *waveFile14= new FileLoop("plugins/Autodafe/samples/table1/14.wav", true );
FileLoop *waveFile15= new FileLoop("plugins/Autodafe/samples/table1/15.wav", true );
FileLoop *waveFile16= new FileLoop("plugins/Autodafe/samples/table1/16.wav", true );
FileLoop *waveFile17= new FileLoop("plugins/Autodafe/samples/table1/17.wav", true );
FileLoop *waveFile18= new FileLoop("plugins/Autodafe/samples/table1/18.wav", true );
FileLoop *waveFile19= new FileLoop("plugins/Autodafe/samples/table1/19.wav", true );
FileLoop *waveFile20= new FileLoop("plugins/Autodafe/samples/table1/20.wav", true );
FileLoop *waveFile21= new FileLoop("plugins/Autodafe/samples/table1/21.wav", true );
FileLoop *waveFile22= new FileLoop("plugins/Autodafe/samples/table1/22.wav", true );
FileLoop *waveFile23= new FileLoop("plugins/Autodafe/samples/table1/23.wav", true );
FileLoop *waveFile24= new FileLoop("plugins/Autodafe/samples/table1/24.wav", true );
FileLoop *waveFile25= new FileLoop("plugins/Autodafe/samples/table1/25.wav", true );
FileLoop *waveFile26= new FileLoop("plugins/Autodafe/samples/table1/26.wav", true );
FileLoop *waveFile27= new FileLoop("plugins/Autodafe/samples/table1/27.wav", true );
FileLoop *waveFile28= new FileLoop("plugins/Autodafe/samples/table1/28.wav", true );
FileLoop *waveFile29= new FileLoop("plugins/Autodafe/samples/table1/29.wav", true );
FileLoop *waveFile30= new FileLoop("plugins/Autodafe/samples/table1/30.wav", true );
FileLoop *waveFile31= new FileLoop("plugins/Autodafe/samples/table1/31.wav", true );
FileLoop *waveFile32= new FileLoop("plugins/Autodafe/samples/table1/32.wav", true );
FileLoop *waveFile33= new FileLoop("plugins/Autodafe/samples/table1/33.wav", true );
FileLoop *waveFile34= new FileLoop("plugins/Autodafe/samples/table1/34.wav", true );
FileLoop *waveFile35= new FileLoop("plugins/Autodafe/samples/table1/35.wav", true );
FileLoop *waveFile36= new FileLoop("plugins/Autodafe/samples/table1/36.wav", true );
FileLoop *waveFile37= new FileLoop("plugins/Autodafe/samples/table1/37.wav", true );
FileLoop *waveFile38= new FileLoop("plugins/Autodafe/samples/table1/38.wav", true );
FileLoop *waveFile39= new FileLoop("plugins/Autodafe/samples/table1/39.wav", true );
FileLoop *waveFile40= new FileLoop("plugins/Autodafe/samples/table1/40.wav", true );
FileLoop *waveFile41= new FileLoop("plugins/Autodafe/samples/table1/41.wav", true );
FileLoop *waveFile42= new FileLoop("plugins/Autodafe/samples/table1/42.wav", true );
FileLoop *waveFile43= new FileLoop("plugins/Autodafe/samples/table1/43.wav", true );
FileLoop *waveFile44= new FileLoop("plugins/Autodafe/samples/table1/44.wav", true );
FileLoop *waveFile45= new FileLoop("plugins/Autodafe/samples/table1/45.wav", true );
FileLoop *waveFile46= new FileLoop("plugins/Autodafe/samples/table1/46.wav", true );
FileLoop *waveFile47= new FileLoop("plugins/Autodafe/samples/table1/47.wav", true );
FileLoop *waveFile48= new FileLoop("plugins/Autodafe/samples/table1/48.wav", true );
FileLoop *waveFile49= new FileLoop("plugins/Autodafe/samples/table1/49.wav", true );
FileLoop *waveFile50= new FileLoop("plugins/Autodafe/samples/table1/50.wav", true );
FileLoop *waveFile51= new FileLoop("plugins/Autodafe/samples/table1/51.wav", true );
FileLoop *waveFile52= new FileLoop("plugins/Autodafe/samples/table1/52.wav", true );
FileLoop *waveFile53= new FileLoop("plugins/Autodafe/samples/table1/53.wav", true );
FileLoop *waveFile54= new FileLoop("plugins/Autodafe/samples/table1/54.wav", true );
FileLoop *waveFile55= new FileLoop("plugins/Autodafe/samples/table1/55.wav", true );
FileLoop *waveFile56= new FileLoop("plugins/Autodafe/samples/table1/56.wav", true );
FileLoop *waveFile57= new FileLoop("plugins/Autodafe/samples/table1/57.wav", true );
FileLoop *waveFile58= new FileLoop("plugins/Autodafe/samples/table1/58.wav", true );
FileLoop *waveFile59= new FileLoop("plugins/Autodafe/samples/table1/59.wav", true );
FileLoop *waveFile60= new FileLoop("plugins/Autodafe/samples/table1/60.wav", true );
FileLoop *waveFile61= new FileLoop("plugins/Autodafe/samples/table1/61.wav", true );
FileLoop *waveFile62= new FileLoop("plugins/Autodafe/samples/table1/62.wav", true );
FileLoop *waveFile63= new FileLoop("plugins/Autodafe/samples/table1/63.wav", true );
	




//BANK 2
FileLoop *waveFile64= new FileLoop("plugins/Autodafe/samples/table2/00.wav", true );
FileLoop *waveFile65= new FileLoop("plugins/Autodafe/samples/table2/01.wav", true );
FileLoop *waveFile66= new FileLoop("plugins/Autodafe/samples/table2/02.wav", true );
FileLoop *waveFile67= new FileLoop("plugins/Autodafe/samples/table2/03.wav", true );
FileLoop *waveFile68= new FileLoop("plugins/Autodafe/samples/table2/04.wav", true );
FileLoop *waveFile69= new FileLoop("plugins/Autodafe/samples/table2/05.wav", true );
FileLoop *waveFile70= new FileLoop("plugins/Autodafe/samples/table2/06.wav", true );
FileLoop *waveFile71= new FileLoop("plugins/Autodafe/samples/table2/07.wav", true );
FileLoop *waveFile72= new FileLoop("plugins/Autodafe/samples/table2/08.wav", true );
FileLoop *waveFile73= new FileLoop("plugins/Autodafe/samples/table2/09.wav", true );
FileLoop *waveFile74= new FileLoop("plugins/Autodafe/samples/table2/10.wav", true );
FileLoop *waveFile75= new FileLoop("plugins/Autodafe/samples/table2/11.wav", true );
FileLoop *waveFile76= new FileLoop("plugins/Autodafe/samples/table2/12.wav", true );
FileLoop *waveFile77= new FileLoop("plugins/Autodafe/samples/table2/13.wav", true );
FileLoop *waveFile78= new FileLoop("plugins/Autodafe/samples/table2/14.wav", true );
FileLoop *waveFile79= new FileLoop("plugins/Autodafe/samples/table2/15.wav", true );
FileLoop *waveFile80= new FileLoop("plugins/Autodafe/samples/table2/16.wav", true );
FileLoop *waveFile81= new FileLoop("plugins/Autodafe/samples/table2/17.wav", true );
FileLoop *waveFile82= new FileLoop("plugins/Autodafe/samples/table2/18.wav", true );
FileLoop *waveFile83= new FileLoop("plugins/Autodafe/samples/table2/19.wav", true );
FileLoop *waveFile84= new FileLoop("plugins/Autodafe/samples/table2/20.wav", true );
FileLoop *waveFile85= new FileLoop("plugins/Autodafe/samples/table2/21.wav", true );
FileLoop *waveFile86= new FileLoop("plugins/Autodafe/samples/table2/22.wav", true );
FileLoop *waveFile87= new FileLoop("plugins/Autodafe/samples/table2/23.wav", true );
FileLoop *waveFile88= new FileLoop("plugins/Autodafe/samples/table2/24.wav", true );
FileLoop *waveFile89= new FileLoop("plugins/Autodafe/samples/table2/25.wav", true );
FileLoop *waveFile90= new FileLoop("plugins/Autodafe/samples/table2/26.wav", true );
FileLoop *waveFile91= new FileLoop("plugins/Autodafe/samples/table2/27.wav", true );
FileLoop *waveFile92= new FileLoop("plugins/Autodafe/samples/table2/28.wav", true );
FileLoop *waveFile93= new FileLoop("plugins/Autodafe/samples/table2/29.wav", true );
FileLoop *waveFile94= new FileLoop("plugins/Autodafe/samples/table2/30.wav", true );
FileLoop *waveFile95= new FileLoop("plugins/Autodafe/samples/table2/31.wav", true );
FileLoop *waveFile96= new FileLoop("plugins/Autodafe/samples/table2/32.wav", true );
FileLoop *waveFile97= new FileLoop("plugins/Autodafe/samples/table2/33.wav", true );
FileLoop *waveFile98= new FileLoop("plugins/Autodafe/samples/table2/34.wav", true );
FileLoop *waveFile99= new FileLoop("plugins/Autodafe/samples/table2/35.wav", true );
FileLoop *waveFile100= new FileLoop("plugins/Autodafe/samples/table2/36.wav", true );
FileLoop *waveFile101= new FileLoop("plugins/Autodafe/samples/table2/37.wav", true );
FileLoop *waveFile102= new FileLoop("plugins/Autodafe/samples/table2/38.wav", true );
FileLoop *waveFile103= new FileLoop("plugins/Autodafe/samples/table2/39.wav", true );
FileLoop *waveFile104= new FileLoop("plugins/Autodafe/samples/table2/40.wav", true );
FileLoop *waveFile105= new FileLoop("plugins/Autodafe/samples/table2/41.wav", true );
FileLoop *waveFile106= new FileLoop("plugins/Autodafe/samples/table2/42.wav", true );
FileLoop *waveFile107= new FileLoop("plugins/Autodafe/samples/table2/43.wav", true );
FileLoop *waveFile108= new FileLoop("plugins/Autodafe/samples/table2/44.wav", true );
FileLoop *waveFile109= new FileLoop("plugins/Autodafe/samples/table2/45.wav", true );
FileLoop *waveFile110= new FileLoop("plugins/Autodafe/samples/table2/46.wav", true );
FileLoop *waveFile111= new FileLoop("plugins/Autodafe/samples/table2/47.wav", true );
FileLoop *waveFile112= new FileLoop("plugins/Autodafe/samples/table2/48.wav", true );
FileLoop *waveFile113= new FileLoop("plugins/Autodafe/samples/table2/49.wav", true );
FileLoop *waveFile114= new FileLoop("plugins/Autodafe/samples/table2/50.wav", true );
FileLoop *waveFile115= new FileLoop("plugins/Autodafe/samples/table2/51.wav", true );
FileLoop *waveFile116= new FileLoop("plugins/Autodafe/samples/table2/52.wav", true );
FileLoop *waveFile117= new FileLoop("plugins/Autodafe/samples/table2/53.wav", true );
FileLoop *waveFile118= new FileLoop("plugins/Autodafe/samples/table2/54.wav", true );
FileLoop *waveFile119= new FileLoop("plugins/Autodafe/samples/table2/55.wav", true );
FileLoop *waveFile120= new FileLoop("plugins/Autodafe/samples/table2/56.wav", true );
FileLoop *waveFile121= new FileLoop("plugins/Autodafe/samples/table2/57.wav", true );
FileLoop *waveFile122= new FileLoop("plugins/Autodafe/samples/table2/58.wav", true );
FileLoop *waveFile123= new FileLoop("plugins/Autodafe/samples/table2/59.wav", true );
FileLoop *waveFile124= new FileLoop("plugins/Autodafe/samples/table2/60.wav", true );
FileLoop *waveFile125= new FileLoop("plugins/Autodafe/samples/table2/61.wav", true );
FileLoop *waveFile126= new FileLoop("plugins/Autodafe/samples/table2/62.wav", true );
FileLoop *waveFile127= new FileLoop("plugins/Autodafe/samples/table2/63.wav", true );


//BANK 3
FileLoop *waveFile128= new FileLoop("plugins/Autodafe/samples/table3/00.wav", true );
FileLoop *waveFile129= new FileLoop("plugins/Autodafe/samples/table3/01.wav", true );
FileLoop *waveFile130= new FileLoop("plugins/Autodafe/samples/table3/02.wav", true );
FileLoop *waveFile131= new FileLoop("plugins/Autodafe/samples/table3/03.wav", true );
FileLoop *waveFile132= new FileLoop("plugins/Autodafe/samples/table3/04.wav", true );
FileLoop *waveFile133= new FileLoop("plugins/Autodafe/samples/table3/05.wav", true );
FileLoop *waveFile134= new FileLoop("plugins/Autodafe/samples/table3/06.wav", true );
FileLoop *waveFile135= new FileLoop("plugins/Autodafe/samples/table3/07.wav", true );
FileLoop *waveFile136= new FileLoop("plugins/Autodafe/samples/table3/08.wav", true );
FileLoop *waveFile137= new FileLoop("plugins/Autodafe/samples/table3/09.wav", true );
FileLoop *waveFile138= new FileLoop("plugins/Autodafe/samples/table3/10.wav", true );
FileLoop *waveFile139= new FileLoop("plugins/Autodafe/samples/table3/11.wav", true );
FileLoop *waveFile140= new FileLoop("plugins/Autodafe/samples/table3/12.wav", true );
FileLoop *waveFile141= new FileLoop("plugins/Autodafe/samples/table3/13.wav", true );
FileLoop *waveFile142= new FileLoop("plugins/Autodafe/samples/table3/14.wav", true );
FileLoop *waveFile143= new FileLoop("plugins/Autodafe/samples/table3/15.wav", true );
FileLoop *waveFile144= new FileLoop("plugins/Autodafe/samples/table3/16.wav", true );
FileLoop *waveFile145= new FileLoop("plugins/Autodafe/samples/table3/17.wav", true );
FileLoop *waveFile146= new FileLoop("plugins/Autodafe/samples/table3/18.wav", true );
FileLoop *waveFile147= new FileLoop("plugins/Autodafe/samples/table3/19.wav", true );
FileLoop *waveFile148= new FileLoop("plugins/Autodafe/samples/table3/20.wav", true );
FileLoop *waveFile149= new FileLoop("plugins/Autodafe/samples/table3/21.wav", true );
FileLoop *waveFile150= new FileLoop("plugins/Autodafe/samples/table3/22.wav", true );
FileLoop *waveFile151= new FileLoop("plugins/Autodafe/samples/table3/23.wav", true );
FileLoop *waveFile152= new FileLoop("plugins/Autodafe/samples/table3/24.wav", true );
FileLoop *waveFile153= new FileLoop("plugins/Autodafe/samples/table3/25.wav", true );
FileLoop *waveFile154= new FileLoop("plugins/Autodafe/samples/table3/26.wav", true );
FileLoop *waveFile155= new FileLoop("plugins/Autodafe/samples/table3/27.wav", true );
FileLoop *waveFile156= new FileLoop("plugins/Autodafe/samples/table3/28.wav", true );
FileLoop *waveFile157= new FileLoop("plugins/Autodafe/samples/table3/29.wav", true );
FileLoop *waveFile158= new FileLoop("plugins/Autodafe/samples/table3/30.wav", true );
FileLoop *waveFile159= new FileLoop("plugins/Autodafe/samples/table3/31.wav", true );
FileLoop *waveFile160= new FileLoop("plugins/Autodafe/samples/table3/32.wav", true );
FileLoop *waveFile161= new FileLoop("plugins/Autodafe/samples/table3/33.wav", true );
FileLoop *waveFile162= new FileLoop("plugins/Autodafe/samples/table3/34.wav", true );
FileLoop *waveFile163= new FileLoop("plugins/Autodafe/samples/table3/35.wav", true );
FileLoop *waveFile164= new FileLoop("plugins/Autodafe/samples/table3/36.wav", true );
FileLoop *waveFile165= new FileLoop("plugins/Autodafe/samples/table3/37.wav", true );
FileLoop *waveFile166= new FileLoop("plugins/Autodafe/samples/table3/38.wav", true );
FileLoop *waveFile167= new FileLoop("plugins/Autodafe/samples/table3/39.wav", true );
FileLoop *waveFile168= new FileLoop("plugins/Autodafe/samples/table3/40.wav", true );
FileLoop *waveFile169= new FileLoop("plugins/Autodafe/samples/table3/41.wav", true );
FileLoop *waveFile170= new FileLoop("plugins/Autodafe/samples/table3/42.wav", true );
FileLoop *waveFile171= new FileLoop("plugins/Autodafe/samples/table3/43.wav", true );
FileLoop *waveFile172= new FileLoop("plugins/Autodafe/samples/table3/44.wav", true );
FileLoop *waveFile173= new FileLoop("plugins/Autodafe/samples/table3/45.wav", true );
FileLoop *waveFile174= new FileLoop("plugins/Autodafe/samples/table3/46.wav", true );
FileLoop *waveFile175= new FileLoop("plugins/Autodafe/samples/table3/47.wav", true );
FileLoop *waveFile176= new FileLoop("plugins/Autodafe/samples/table3/48.wav", true );
FileLoop *waveFile177= new FileLoop("plugins/Autodafe/samples/table3/49.wav", true );
FileLoop *waveFile178= new FileLoop("plugins/Autodafe/samples/table3/50.wav", true );
FileLoop *waveFile179= new FileLoop("plugins/Autodafe/samples/table3/51.wav", true );
FileLoop *waveFile180= new FileLoop("plugins/Autodafe/samples/table3/52.wav", true );
FileLoop *waveFile181= new FileLoop("plugins/Autodafe/samples/table3/53.wav", true );
FileLoop *waveFile182= new FileLoop("plugins/Autodafe/samples/table3/54.wav", true );
FileLoop *waveFile183= new FileLoop("plugins/Autodafe/samples/table3/55.wav", true );
FileLoop *waveFile184= new FileLoop("plugins/Autodafe/samples/table3/56.wav", true );
FileLoop *waveFile185= new FileLoop("plugins/Autodafe/samples/table3/57.wav", true );
FileLoop *waveFile186= new FileLoop("plugins/Autodafe/samples/table3/58.wav", true );
FileLoop *waveFile187= new FileLoop("plugins/Autodafe/samples/table3/59.wav", true );
FileLoop *waveFile188= new FileLoop("plugins/Autodafe/samples/table3/60.wav", true );
FileLoop *waveFile189= new FileLoop("plugins/Autodafe/samples/table3/61.wav", true );
FileLoop *waveFile190= new FileLoop("plugins/Autodafe/samples/table3/62.wav", true );
FileLoop *waveFile191= new FileLoop("plugins/Autodafe/samples/table3/63.wav", true );





//bank04 - SAW WAVES


FileLoop *waveFile192= new FileLoop("plugins/Autodafe/samples/table4-saw/00.wav", true );
FileLoop *waveFile193= new FileLoop("plugins/Autodafe/samples/table4-saw/01.wav", true );
FileLoop *waveFile194= new FileLoop("plugins/Autodafe/samples/table4-saw/02.wav", true );
FileLoop *waveFile195= new FileLoop("plugins/Autodafe/samples/table4-saw/03.wav", true );
FileLoop *waveFile196= new FileLoop("plugins/Autodafe/samples/table4-saw/04.wav", true );
FileLoop *waveFile197= new FileLoop("plugins/Autodafe/samples/table4-saw/05.wav", true );
FileLoop *waveFile198= new FileLoop("plugins/Autodafe/samples/table4-saw/06.wav", true );
FileLoop *waveFile199= new FileLoop("plugins/Autodafe/samples/table4-saw/07.wav", true );
FileLoop *waveFile200= new FileLoop("plugins/Autodafe/samples/table4-saw/08.wav", true );
FileLoop *waveFile201= new FileLoop("plugins/Autodafe/samples/table4-saw/09.wav", true );
FileLoop *waveFile202= new FileLoop("plugins/Autodafe/samples/table4-saw/10.wav", true );
FileLoop *waveFile203= new FileLoop("plugins/Autodafe/samples/table4-saw/11.wav", true );
FileLoop *waveFile204= new FileLoop("plugins/Autodafe/samples/table4-saw/12.wav", true );
FileLoop *waveFile205= new FileLoop("plugins/Autodafe/samples/table4-saw/13.wav", true );
FileLoop *waveFile206= new FileLoop("plugins/Autodafe/samples/table4-saw/14.wav", true );
FileLoop *waveFile207= new FileLoop("plugins/Autodafe/samples/table4-saw/15.wav", true );
FileLoop *waveFile208= new FileLoop("plugins/Autodafe/samples/table4-saw/16.wav", true );
FileLoop *waveFile209= new FileLoop("plugins/Autodafe/samples/table4-saw/17.wav", true );
FileLoop *waveFile210= new FileLoop("plugins/Autodafe/samples/table4-saw/18.wav", true );
FileLoop *waveFile211= new FileLoop("plugins/Autodafe/samples/table4-saw/19.wav", true );
FileLoop *waveFile212= new FileLoop("plugins/Autodafe/samples/table4-saw/20.wav", true );
FileLoop *waveFile213= new FileLoop("plugins/Autodafe/samples/table4-saw/21.wav", true );
FileLoop *waveFile214= new FileLoop("plugins/Autodafe/samples/table4-saw/22.wav", true );
FileLoop *waveFile215= new FileLoop("plugins/Autodafe/samples/table4-saw/23.wav", true );
FileLoop *waveFile216= new FileLoop("plugins/Autodafe/samples/table4-saw/24.wav", true );
FileLoop *waveFile217= new FileLoop("plugins/Autodafe/samples/table4-saw/25.wav", true );
FileLoop *waveFile218= new FileLoop("plugins/Autodafe/samples/table4-saw/26.wav", true );
FileLoop *waveFile219= new FileLoop("plugins/Autodafe/samples/table4-saw/27.wav", true );
FileLoop *waveFile220= new FileLoop("plugins/Autodafe/samples/table4-saw/28.wav", true );
FileLoop *waveFile221= new FileLoop("plugins/Autodafe/samples/table4-saw/29.wav", true );
FileLoop *waveFile222= new FileLoop("plugins/Autodafe/samples/table4-saw/30.wav", true );
FileLoop *waveFile223= new FileLoop("plugins/Autodafe/samples/table4-saw/31.wav", true );
FileLoop *waveFile224= new FileLoop("plugins/Autodafe/samples/table4-saw/32.wav", true );
FileLoop *waveFile225= new FileLoop("plugins/Autodafe/samples/table4-saw/33.wav", true );
FileLoop *waveFile226= new FileLoop("plugins/Autodafe/samples/table4-saw/34.wav", true );
FileLoop *waveFile227= new FileLoop("plugins/Autodafe/samples/table4-saw/35.wav", true );
FileLoop *waveFile228= new FileLoop("plugins/Autodafe/samples/table4-saw/36.wav", true );
FileLoop *waveFile229= new FileLoop("plugins/Autodafe/samples/table4-saw/37.wav", true );
FileLoop *waveFile230= new FileLoop("plugins/Autodafe/samples/table4-saw/38.wav", true );
FileLoop *waveFile231= new FileLoop("plugins/Autodafe/samples/table4-saw/39.wav", true );
FileLoop *waveFile232= new FileLoop("plugins/Autodafe/samples/table4-saw/40.wav", true );
FileLoop *waveFile233= new FileLoop("plugins/Autodafe/samples/table4-saw/41.wav", true );
FileLoop *waveFile234= new FileLoop("plugins/Autodafe/samples/table4-saw/42.wav", true );
FileLoop *waveFile235= new FileLoop("plugins/Autodafe/samples/table4-saw/43.wav", true );
FileLoop *waveFile236= new FileLoop("plugins/Autodafe/samples/table4-saw/44.wav", true );
FileLoop *waveFile237= new FileLoop("plugins/Autodafe/samples/table4-saw/45.wav", true );
FileLoop *waveFile238= new FileLoop("plugins/Autodafe/samples/table4-saw/46.wav", true );
FileLoop *waveFile239= new FileLoop("plugins/Autodafe/samples/table4-saw/47.wav", true );
FileLoop *waveFile240= new FileLoop("plugins/Autodafe/samples/table4-saw/48.wav", true );
FileLoop *waveFile241= new FileLoop("plugins/Autodafe/samples/table4-saw/49.wav", true );
FileLoop *waveFile242= new FileLoop("plugins/Autodafe/samples/table4-saw/50.wav", true );
FileLoop *waveFile243= new FileLoop("plugins/Autodafe/samples/table4-saw/51.wav", true );
FileLoop *waveFile244= new FileLoop("plugins/Autodafe/samples/table4-saw/52.wav", true );
FileLoop *waveFile245= new FileLoop("plugins/Autodafe/samples/table4-saw/53.wav", true );
FileLoop *waveFile246= new FileLoop("plugins/Autodafe/samples/table4-saw/54.wav", true );
FileLoop *waveFile247= new FileLoop("plugins/Autodafe/samples/table4-saw/55.wav", true );
FileLoop *waveFile248= new FileLoop("plugins/Autodafe/samples/table4-saw/56.wav", true );
FileLoop *waveFile249= new FileLoop("plugins/Autodafe/samples/table4-saw/57.wav", true );
FileLoop *waveFile250= new FileLoop("plugins/Autodafe/samples/table4-saw/58.wav", true );
FileLoop *waveFile251= new FileLoop("plugins/Autodafe/samples/table4-saw/59.wav", true );
FileLoop *waveFile252= new FileLoop("plugins/Autodafe/samples/table4-saw/60.wav", true );
FileLoop *waveFile253= new FileLoop("plugins/Autodafe/samples/table4-saw/61.wav", true );
FileLoop *waveFile254= new FileLoop("plugins/Autodafe/samples/table4-saw/62.wav", true );
FileLoop *waveFile255= new FileLoop("plugins/Autodafe/samples/table4-saw/63.wav", true ); 
 


//BANK 05 -square



FileLoop *waveFile256= new FileLoop("plugins/Autodafe/samples/table5-square/00.wav", true );
FileLoop *waveFile257= new FileLoop("plugins/Autodafe/samples/table5-square/01.wav", true );
FileLoop *waveFile258= new FileLoop("plugins/Autodafe/samples/table5-square/02.wav", true );
FileLoop *waveFile259= new FileLoop("plugins/Autodafe/samples/table5-square/03.wav", true );
FileLoop *waveFile260= new FileLoop("plugins/Autodafe/samples/table5-square/04.wav", true );
FileLoop *waveFile261= new FileLoop("plugins/Autodafe/samples/table5-square/05.wav", true );
FileLoop *waveFile262= new FileLoop("plugins/Autodafe/samples/table5-square/06.wav", true );
FileLoop *waveFile263= new FileLoop("plugins/Autodafe/samples/table5-square/07.wav", true );
FileLoop *waveFile264= new FileLoop("plugins/Autodafe/samples/table5-square/08.wav", true );
FileLoop *waveFile265= new FileLoop("plugins/Autodafe/samples/table5-square/09.wav", true );
FileLoop *waveFile266= new FileLoop("plugins/Autodafe/samples/table5-square/10.wav", true );
FileLoop *waveFile267= new FileLoop("plugins/Autodafe/samples/table5-square/11.wav", true );
FileLoop *waveFile268= new FileLoop("plugins/Autodafe/samples/table5-square/12.wav", true );
FileLoop *waveFile269= new FileLoop("plugins/Autodafe/samples/table5-square/13.wav", true );
FileLoop *waveFile270= new FileLoop("plugins/Autodafe/samples/table5-square/14.wav", true );
FileLoop *waveFile271= new FileLoop("plugins/Autodafe/samples/table5-square/15.wav", true );
FileLoop *waveFile272= new FileLoop("plugins/Autodafe/samples/table5-square/16.wav", true );
FileLoop *waveFile273= new FileLoop("plugins/Autodafe/samples/table5-square/17.wav", true );
FileLoop *waveFile274= new FileLoop("plugins/Autodafe/samples/table5-square/18.wav", true );
FileLoop *waveFile275= new FileLoop("plugins/Autodafe/samples/table5-square/19.wav", true );
FileLoop *waveFile276= new FileLoop("plugins/Autodafe/samples/table5-square/20.wav", true );
FileLoop *waveFile277= new FileLoop("plugins/Autodafe/samples/table5-square/21.wav", true );
FileLoop *waveFile278= new FileLoop("plugins/Autodafe/samples/table5-square/22.wav", true );
FileLoop *waveFile279= new FileLoop("plugins/Autodafe/samples/table5-square/23.wav", true );
FileLoop *waveFile280= new FileLoop("plugins/Autodafe/samples/table5-square/24.wav", true );
FileLoop *waveFile281= new FileLoop("plugins/Autodafe/samples/table5-square/25.wav", true );
FileLoop *waveFile282= new FileLoop("plugins/Autodafe/samples/table5-square/26.wav", true );
FileLoop *waveFile283= new FileLoop("plugins/Autodafe/samples/table5-square/27.wav", true );
FileLoop *waveFile284= new FileLoop("plugins/Autodafe/samples/table5-square/28.wav", true );
FileLoop *waveFile285= new FileLoop("plugins/Autodafe/samples/table5-square/29.wav", true );
FileLoop *waveFile286= new FileLoop("plugins/Autodafe/samples/table5-square/30.wav", true );
FileLoop *waveFile287= new FileLoop("plugins/Autodafe/samples/table5-square/31.wav", true );
FileLoop *waveFile288= new FileLoop("plugins/Autodafe/samples/table5-square/32.wav", true );
FileLoop *waveFile289= new FileLoop("plugins/Autodafe/samples/table5-square/33.wav", true );
FileLoop *waveFile290= new FileLoop("plugins/Autodafe/samples/table5-square/34.wav", true );
FileLoop *waveFile291= new FileLoop("plugins/Autodafe/samples/table5-square/35.wav", true );
FileLoop *waveFile292= new FileLoop("plugins/Autodafe/samples/table5-square/36.wav", true );
FileLoop *waveFile293= new FileLoop("plugins/Autodafe/samples/table5-square/37.wav", true );
FileLoop *waveFile294= new FileLoop("plugins/Autodafe/samples/table5-square/38.wav", true );
FileLoop *waveFile295= new FileLoop("plugins/Autodafe/samples/table5-square/39.wav", true );
FileLoop *waveFile296= new FileLoop("plugins/Autodafe/samples/table5-square/40.wav", true );
FileLoop *waveFile297= new FileLoop("plugins/Autodafe/samples/table5-square/41.wav", true );
FileLoop *waveFile298= new FileLoop("plugins/Autodafe/samples/table5-square/42.wav", true );
FileLoop *waveFile299= new FileLoop("plugins/Autodafe/samples/table5-square/43.wav", true );
FileLoop *waveFile300= new FileLoop("plugins/Autodafe/samples/table5-square/44.wav", true );
FileLoop *waveFile301= new FileLoop("plugins/Autodafe/samples/table5-square/45.wav", true );
FileLoop *waveFile302= new FileLoop("plugins/Autodafe/samples/table5-square/46.wav", true );
FileLoop *waveFile303= new FileLoop("plugins/Autodafe/samples/table5-square/47.wav", true );
FileLoop *waveFile304= new FileLoop("plugins/Autodafe/samples/table5-square/48.wav", true );
FileLoop *waveFile305= new FileLoop("plugins/Autodafe/samples/table5-square/49.wav", true );
FileLoop *waveFile306= new FileLoop("plugins/Autodafe/samples/table5-square/50.wav", true );
FileLoop *waveFile307= new FileLoop("plugins/Autodafe/samples/table5-square/51.wav", true );
FileLoop *waveFile308= new FileLoop("plugins/Autodafe/samples/table5-square/52.wav", true );
FileLoop *waveFile309= new FileLoop("plugins/Autodafe/samples/table5-square/53.wav", true );
FileLoop *waveFile310= new FileLoop("plugins/Autodafe/samples/table5-square/54.wav", true );
FileLoop *waveFile311= new FileLoop("plugins/Autodafe/samples/table5-square/55.wav", true );
FileLoop *waveFile312= new FileLoop("plugins/Autodafe/samples/table5-square/56.wav", true );
FileLoop *waveFile313= new FileLoop("plugins/Autodafe/samples/table5-square/57.wav", true );
FileLoop *waveFile314= new FileLoop("plugins/Autodafe/samples/table5-square/58.wav", true );
FileLoop *waveFile315= new FileLoop("plugins/Autodafe/samples/table5-square/59.wav", true );
FileLoop *waveFile316= new FileLoop("plugins/Autodafe/samples/table5-square/60.wav", true );
FileLoop *waveFile317= new FileLoop("plugins/Autodafe/samples/table5-square/61.wav", true );
FileLoop *waveFile318= new FileLoop("plugins/Autodafe/samples/table5-square/62.wav", true );
FileLoop *waveFile319= new FileLoop("plugins/Autodafe/samples/table5-square/63.wav", true );




//BANK 06 -SQUARE 2


FileLoop *waveFile320= new FileLoop("plugins/Autodafe/samples/table6-square2/00.wav", true );
FileLoop *waveFile321= new FileLoop("plugins/Autodafe/samples/table6-square2/01.wav", true );
FileLoop *waveFile322= new FileLoop("plugins/Autodafe/samples/table6-square2/02.wav", true );
FileLoop *waveFile323= new FileLoop("plugins/Autodafe/samples/table6-square2/03.wav", true );
FileLoop *waveFile324= new FileLoop("plugins/Autodafe/samples/table6-square2/04.wav", true );
FileLoop *waveFile325= new FileLoop("plugins/Autodafe/samples/table6-square2/05.wav", true );
FileLoop *waveFile326= new FileLoop("plugins/Autodafe/samples/table6-square2/06.wav", true );
FileLoop *waveFile327= new FileLoop("plugins/Autodafe/samples/table6-square2/07.wav", true );
FileLoop *waveFile328= new FileLoop("plugins/Autodafe/samples/table6-square2/08.wav", true );
FileLoop *waveFile329= new FileLoop("plugins/Autodafe/samples/table6-square2/09.wav", true );
FileLoop *waveFile330= new FileLoop("plugins/Autodafe/samples/table6-square2/10.wav", true );
FileLoop *waveFile331= new FileLoop("plugins/Autodafe/samples/table6-square2/11.wav", true );
FileLoop *waveFile332= new FileLoop("plugins/Autodafe/samples/table6-square2/12.wav", true );
FileLoop *waveFile333= new FileLoop("plugins/Autodafe/samples/table6-square2/13.wav", true );
FileLoop *waveFile334= new FileLoop("plugins/Autodafe/samples/table6-square2/14.wav", true );
FileLoop *waveFile335= new FileLoop("plugins/Autodafe/samples/table6-square2/15.wav", true );
FileLoop *waveFile336= new FileLoop("plugins/Autodafe/samples/table6-square2/16.wav", true );
FileLoop *waveFile337= new FileLoop("plugins/Autodafe/samples/table6-square2/17.wav", true );
FileLoop *waveFile338= new FileLoop("plugins/Autodafe/samples/table6-square2/18.wav", true );
FileLoop *waveFile339= new FileLoop("plugins/Autodafe/samples/table6-square2/19.wav", true );
FileLoop *waveFile340= new FileLoop("plugins/Autodafe/samples/table6-square2/20.wav", true );
FileLoop *waveFile341= new FileLoop("plugins/Autodafe/samples/table6-square2/21.wav", true );
FileLoop *waveFile342= new FileLoop("plugins/Autodafe/samples/table6-square2/22.wav", true );
FileLoop *waveFile343= new FileLoop("plugins/Autodafe/samples/table6-square2/23.wav", true );
FileLoop *waveFile344= new FileLoop("plugins/Autodafe/samples/table6-square2/24.wav", true );
FileLoop *waveFile345= new FileLoop("plugins/Autodafe/samples/table6-square2/25.wav", true );
FileLoop *waveFile346= new FileLoop("plugins/Autodafe/samples/table6-square2/26.wav", true );
FileLoop *waveFile347= new FileLoop("plugins/Autodafe/samples/table6-square2/27.wav", true );
FileLoop *waveFile348= new FileLoop("plugins/Autodafe/samples/table6-square2/28.wav", true );
FileLoop *waveFile349= new FileLoop("plugins/Autodafe/samples/table6-square2/29.wav", true );
FileLoop *waveFile350= new FileLoop("plugins/Autodafe/samples/table6-square2/30.wav", true );
FileLoop *waveFile351= new FileLoop("plugins/Autodafe/samples/table6-square2/31.wav", true );
FileLoop *waveFile352= new FileLoop("plugins/Autodafe/samples/table6-square2/32.wav", true );
FileLoop *waveFile353= new FileLoop("plugins/Autodafe/samples/table6-square2/33.wav", true );
FileLoop *waveFile354= new FileLoop("plugins/Autodafe/samples/table6-square2/34.wav", true );
FileLoop *waveFile355= new FileLoop("plugins/Autodafe/samples/table6-square2/35.wav", true );
FileLoop *waveFile356= new FileLoop("plugins/Autodafe/samples/table6-square2/36.wav", true );
FileLoop *waveFile357= new FileLoop("plugins/Autodafe/samples/table6-square2/37.wav", true );
FileLoop *waveFile358= new FileLoop("plugins/Autodafe/samples/table6-square2/38.wav", true );
FileLoop *waveFile359= new FileLoop("plugins/Autodafe/samples/table6-square2/39.wav", true );
FileLoop *waveFile360= new FileLoop("plugins/Autodafe/samples/table6-square2/40.wav", true );
FileLoop *waveFile361= new FileLoop("plugins/Autodafe/samples/table6-square2/41.wav", true );
FileLoop *waveFile362= new FileLoop("plugins/Autodafe/samples/table6-square2/42.wav", true );
FileLoop *waveFile363= new FileLoop("plugins/Autodafe/samples/table6-square2/43.wav", true );
FileLoop *waveFile364= new FileLoop("plugins/Autodafe/samples/table6-square2/44.wav", true );
FileLoop *waveFile365= new FileLoop("plugins/Autodafe/samples/table6-square2/45.wav", true );
FileLoop *waveFile366= new FileLoop("plugins/Autodafe/samples/table6-square2/46.wav", true );
FileLoop *waveFile367= new FileLoop("plugins/Autodafe/samples/table6-square2/47.wav", true );
FileLoop *waveFile368= new FileLoop("plugins/Autodafe/samples/table6-square2/48.wav", true );
FileLoop *waveFile369= new FileLoop("plugins/Autodafe/samples/table6-square2/49.wav", true );
FileLoop *waveFile370= new FileLoop("plugins/Autodafe/samples/table6-square2/50.wav", true );
FileLoop *waveFile371= new FileLoop("plugins/Autodafe/samples/table6-square2/51.wav", true );
FileLoop *waveFile372= new FileLoop("plugins/Autodafe/samples/table6-square2/52.wav", true );
FileLoop *waveFile373= new FileLoop("plugins/Autodafe/samples/table6-square2/53.wav", true );
FileLoop *waveFile374= new FileLoop("plugins/Autodafe/samples/table6-square2/54.wav", true );
FileLoop *waveFile375= new FileLoop("plugins/Autodafe/samples/table6-square2/55.wav", true );
FileLoop *waveFile376= new FileLoop("plugins/Autodafe/samples/table6-square2/56.wav", true );
FileLoop *waveFile377= new FileLoop("plugins/Autodafe/samples/table6-square2/57.wav", true );
FileLoop *waveFile378= new FileLoop("plugins/Autodafe/samples/table6-square2/58.wav", true );
FileLoop *waveFile379= new FileLoop("plugins/Autodafe/samples/table6-square2/59.wav", true );
FileLoop *waveFile380= new FileLoop("plugins/Autodafe/samples/table6-square2/60.wav", true );
FileLoop *waveFile381= new FileLoop("plugins/Autodafe/samples/table6-square2/61.wav", true );
FileLoop *waveFile382= new FileLoop("plugins/Autodafe/samples/table6-square2/62.wav", true );
FileLoop *waveFile383= new FileLoop("plugins/Autodafe/samples/table6-square2/63.wav", true );








FileLoop *waveFile384= new FileLoop("plugins/Autodafe/samples/table7-chip/00.wav", true );
FileLoop *waveFile385= new FileLoop("plugins/Autodafe/samples/table7-chip/01.wav", true );
FileLoop *waveFile386= new FileLoop("plugins/Autodafe/samples/table7-chip/02.wav", true );
FileLoop *waveFile387= new FileLoop("plugins/Autodafe/samples/table7-chip/03.wav", true );
FileLoop *waveFile388= new FileLoop("plugins/Autodafe/samples/table7-chip/04.wav", true );
FileLoop *waveFile389= new FileLoop("plugins/Autodafe/samples/table7-chip/05.wav", true );
FileLoop *waveFile390= new FileLoop("plugins/Autodafe/samples/table7-chip/06.wav", true );
FileLoop *waveFile391= new FileLoop("plugins/Autodafe/samples/table7-chip/07.wav", true );
FileLoop *waveFile392= new FileLoop("plugins/Autodafe/samples/table7-chip/08.wav", true );
FileLoop *waveFile393= new FileLoop("plugins/Autodafe/samples/table7-chip/09.wav", true );
FileLoop *waveFile394= new FileLoop("plugins/Autodafe/samples/table7-chip/10.wav", true );
FileLoop *waveFile395= new FileLoop("plugins/Autodafe/samples/table7-chip/11.wav", true );
FileLoop *waveFile396= new FileLoop("plugins/Autodafe/samples/table7-chip/12.wav", true );
FileLoop *waveFile397= new FileLoop("plugins/Autodafe/samples/table7-chip/13.wav", true );
FileLoop *waveFile398= new FileLoop("plugins/Autodafe/samples/table7-chip/14.wav", true );
FileLoop *waveFile399= new FileLoop("plugins/Autodafe/samples/table7-chip/15.wav", true );
FileLoop *waveFile400= new FileLoop("plugins/Autodafe/samples/table7-chip/16.wav", true );
FileLoop *waveFile401= new FileLoop("plugins/Autodafe/samples/table7-chip/17.wav", true );
FileLoop *waveFile402= new FileLoop("plugins/Autodafe/samples/table7-chip/18.wav", true );
FileLoop *waveFile403= new FileLoop("plugins/Autodafe/samples/table7-chip/19.wav", true );
FileLoop *waveFile404= new FileLoop("plugins/Autodafe/samples/table7-chip/20.wav", true );
FileLoop *waveFile405= new FileLoop("plugins/Autodafe/samples/table7-chip/21.wav", true );
FileLoop *waveFile406= new FileLoop("plugins/Autodafe/samples/table7-chip/22.wav", true );
FileLoop *waveFile407= new FileLoop("plugins/Autodafe/samples/table7-chip/23.wav", true );
FileLoop *waveFile408= new FileLoop("plugins/Autodafe/samples/table7-chip/24.wav", true );
FileLoop *waveFile409= new FileLoop("plugins/Autodafe/samples/table7-chip/25.wav", true );
FileLoop *waveFile410= new FileLoop("plugins/Autodafe/samples/table7-chip/26.wav", true );
FileLoop *waveFile411= new FileLoop("plugins/Autodafe/samples/table7-chip/27.wav", true );
FileLoop *waveFile412= new FileLoop("plugins/Autodafe/samples/table7-chip/28.wav", true );
FileLoop *waveFile413= new FileLoop("plugins/Autodafe/samples/table7-chip/29.wav", true );
FileLoop *waveFile414= new FileLoop("plugins/Autodafe/samples/table7-chip/30.wav", true );
FileLoop *waveFile415= new FileLoop("plugins/Autodafe/samples/table7-chip/31.wav", true );
FileLoop *waveFile416= new FileLoop("plugins/Autodafe/samples/table7-chip/32.wav", true );
FileLoop *waveFile417= new FileLoop("plugins/Autodafe/samples/table7-chip/33.wav", true );
FileLoop *waveFile418= new FileLoop("plugins/Autodafe/samples/table7-chip/34.wav", true );
FileLoop *waveFile419= new FileLoop("plugins/Autodafe/samples/table7-chip/35.wav", true );
FileLoop *waveFile420= new FileLoop("plugins/Autodafe/samples/table7-chip/36.wav", true );
FileLoop *waveFile421= new FileLoop("plugins/Autodafe/samples/table7-chip/37.wav", true );
FileLoop *waveFile422= new FileLoop("plugins/Autodafe/samples/table7-chip/38.wav", true );
FileLoop *waveFile423= new FileLoop("plugins/Autodafe/samples/table7-chip/39.wav", true );
FileLoop *waveFile424= new FileLoop("plugins/Autodafe/samples/table7-chip/40.wav", true );
FileLoop *waveFile425= new FileLoop("plugins/Autodafe/samples/table7-chip/41.wav", true );
FileLoop *waveFile426= new FileLoop("plugins/Autodafe/samples/table7-chip/42.wav", true );
FileLoop *waveFile427= new FileLoop("plugins/Autodafe/samples/table7-chip/43.wav", true );
FileLoop *waveFile428= new FileLoop("plugins/Autodafe/samples/table7-chip/44.wav", true );
FileLoop *waveFile429= new FileLoop("plugins/Autodafe/samples/table7-chip/45.wav", true );
FileLoop *waveFile430= new FileLoop("plugins/Autodafe/samples/table7-chip/46.wav", true );
FileLoop *waveFile431= new FileLoop("plugins/Autodafe/samples/table7-chip/47.wav", true );
FileLoop *waveFile432= new FileLoop("plugins/Autodafe/samples/table7-chip/48.wav", true );
FileLoop *waveFile433= new FileLoop("plugins/Autodafe/samples/table7-chip/49.wav", true );
FileLoop *waveFile434= new FileLoop("plugins/Autodafe/samples/table7-chip/50.wav", true );
FileLoop *waveFile435= new FileLoop("plugins/Autodafe/samples/table7-chip/51.wav", true );
FileLoop *waveFile436= new FileLoop("plugins/Autodafe/samples/table7-chip/52.wav", true );
FileLoop *waveFile437= new FileLoop("plugins/Autodafe/samples/table7-chip/53.wav", true );
FileLoop *waveFile438= new FileLoop("plugins/Autodafe/samples/table7-chip/54.wav", true );
FileLoop *waveFile439= new FileLoop("plugins/Autodafe/samples/table7-chip/55.wav", true );
FileLoop *waveFile440= new FileLoop("plugins/Autodafe/samples/table7-chip/56.wav", true );
FileLoop *waveFile441= new FileLoop("plugins/Autodafe/samples/table7-chip/57.wav", true );
FileLoop *waveFile442= new FileLoop("plugins/Autodafe/samples/table7-chip/58.wav", true );
FileLoop *waveFile443= new FileLoop("plugins/Autodafe/samples/table7-chip/59.wav", true );
FileLoop *waveFile444= new FileLoop("plugins/Autodafe/samples/table7-chip/60.wav", true );
FileLoop *waveFile445= new FileLoop("plugins/Autodafe/samples/table7-chip/61.wav", true );
FileLoop *waveFile446= new FileLoop("plugins/Autodafe/samples/table7-chip/62.wav", true );
FileLoop *waveFile447= new FileLoop("plugins/Autodafe/samples/table7-chip/63.wav", true );



FileLoop *waveFile448= new FileLoop("plugins/Autodafe/samples/table8-hvoice/00.wav", true );
FileLoop *waveFile449= new FileLoop("plugins/Autodafe/samples/table8-hvoice/01.wav", true );
FileLoop *waveFile450= new FileLoop("plugins/Autodafe/samples/table8-hvoice/02.wav", true );
FileLoop *waveFile451= new FileLoop("plugins/Autodafe/samples/table8-hvoice/03.wav", true );
FileLoop *waveFile452= new FileLoop("plugins/Autodafe/samples/table8-hvoice/04.wav", true );
FileLoop *waveFile453= new FileLoop("plugins/Autodafe/samples/table8-hvoice/05.wav", true );
FileLoop *waveFile454= new FileLoop("plugins/Autodafe/samples/table8-hvoice/06.wav", true );
FileLoop *waveFile455= new FileLoop("plugins/Autodafe/samples/table8-hvoice/07.wav", true );
FileLoop *waveFile456= new FileLoop("plugins/Autodafe/samples/table8-hvoice/08.wav", true );
FileLoop *waveFile457= new FileLoop("plugins/Autodafe/samples/table8-hvoice/09.wav", true );
FileLoop *waveFile458= new FileLoop("plugins/Autodafe/samples/table8-hvoice/10.wav", true );
FileLoop *waveFile459= new FileLoop("plugins/Autodafe/samples/table8-hvoice/11.wav", true );
FileLoop *waveFile460= new FileLoop("plugins/Autodafe/samples/table8-hvoice/12.wav", true );
FileLoop *waveFile461= new FileLoop("plugins/Autodafe/samples/table8-hvoice/13.wav", true );
FileLoop *waveFile462= new FileLoop("plugins/Autodafe/samples/table8-hvoice/14.wav", true );
FileLoop *waveFile463= new FileLoop("plugins/Autodafe/samples/table8-hvoice/15.wav", true );
FileLoop *waveFile464= new FileLoop("plugins/Autodafe/samples/table8-hvoice/16.wav", true );
FileLoop *waveFile465= new FileLoop("plugins/Autodafe/samples/table8-hvoice/17.wav", true );
FileLoop *waveFile466= new FileLoop("plugins/Autodafe/samples/table8-hvoice/18.wav", true );
FileLoop *waveFile467= new FileLoop("plugins/Autodafe/samples/table8-hvoice/19.wav", true );
FileLoop *waveFile468= new FileLoop("plugins/Autodafe/samples/table8-hvoice/20.wav", true );
FileLoop *waveFile469= new FileLoop("plugins/Autodafe/samples/table8-hvoice/21.wav", true );
FileLoop *waveFile470= new FileLoop("plugins/Autodafe/samples/table8-hvoice/22.wav", true );
FileLoop *waveFile471= new FileLoop("plugins/Autodafe/samples/table8-hvoice/23.wav", true );
FileLoop *waveFile472= new FileLoop("plugins/Autodafe/samples/table8-hvoice/24.wav", true );
FileLoop *waveFile473= new FileLoop("plugins/Autodafe/samples/table8-hvoice/25.wav", true );
FileLoop *waveFile474= new FileLoop("plugins/Autodafe/samples/table8-hvoice/26.wav", true );
FileLoop *waveFile475= new FileLoop("plugins/Autodafe/samples/table8-hvoice/27.wav", true );
FileLoop *waveFile476= new FileLoop("plugins/Autodafe/samples/table8-hvoice/28.wav", true );
FileLoop *waveFile477= new FileLoop("plugins/Autodafe/samples/table8-hvoice/29.wav", true );
FileLoop *waveFile478= new FileLoop("plugins/Autodafe/samples/table8-hvoice/30.wav", true );
FileLoop *waveFile479= new FileLoop("plugins/Autodafe/samples/table8-hvoice/31.wav", true );
FileLoop *waveFile480= new FileLoop("plugins/Autodafe/samples/table8-hvoice/32.wav", true );
FileLoop *waveFile481= new FileLoop("plugins/Autodafe/samples/table8-hvoice/33.wav", true );
FileLoop *waveFile482= new FileLoop("plugins/Autodafe/samples/table8-hvoice/34.wav", true );
FileLoop *waveFile483= new FileLoop("plugins/Autodafe/samples/table8-hvoice/35.wav", true );
FileLoop *waveFile484= new FileLoop("plugins/Autodafe/samples/table8-hvoice/36.wav", true );
FileLoop *waveFile485= new FileLoop("plugins/Autodafe/samples/table8-hvoice/37.wav", true );
FileLoop *waveFile486= new FileLoop("plugins/Autodafe/samples/table8-hvoice/38.wav", true );
FileLoop *waveFile487= new FileLoop("plugins/Autodafe/samples/table8-hvoice/39.wav", true );
FileLoop *waveFile488= new FileLoop("plugins/Autodafe/samples/table8-hvoice/40.wav", true );
FileLoop *waveFile489= new FileLoop("plugins/Autodafe/samples/table8-hvoice/41.wav", true );
FileLoop *waveFile490= new FileLoop("plugins/Autodafe/samples/table8-hvoice/42.wav", true );
FileLoop *waveFile491= new FileLoop("plugins/Autodafe/samples/table8-hvoice/43.wav", true );
FileLoop *waveFile492= new FileLoop("plugins/Autodafe/samples/table8-hvoice/44.wav", true );
FileLoop *waveFile493= new FileLoop("plugins/Autodafe/samples/table8-hvoice/45.wav", true );
FileLoop *waveFile494= new FileLoop("plugins/Autodafe/samples/table8-hvoice/46.wav", true );
FileLoop *waveFile495= new FileLoop("plugins/Autodafe/samples/table8-hvoice/47.wav", true );
FileLoop *waveFile496= new FileLoop("plugins/Autodafe/samples/table8-hvoice/48.wav", true );
FileLoop *waveFile497= new FileLoop("plugins/Autodafe/samples/table8-hvoice/49.wav", true );
FileLoop *waveFile498= new FileLoop("plugins/Autodafe/samples/table8-hvoice/50.wav", true );
FileLoop *waveFile499= new FileLoop("plugins/Autodafe/samples/table8-hvoice/51.wav", true );
FileLoop *waveFile500= new FileLoop("plugins/Autodafe/samples/table8-hvoice/52.wav", true );
FileLoop *waveFile501= new FileLoop("plugins/Autodafe/samples/table8-hvoice/53.wav", true );
FileLoop *waveFile502= new FileLoop("plugins/Autodafe/samples/table8-hvoice/54.wav", true );
FileLoop *waveFile503= new FileLoop("plugins/Autodafe/samples/table8-hvoice/55.wav", true );
FileLoop *waveFile504= new FileLoop("plugins/Autodafe/samples/table8-hvoice/56.wav", true );
FileLoop *waveFile505= new FileLoop("plugins/Autodafe/samples/table8-hvoice/57.wav", true );
FileLoop *waveFile506= new FileLoop("plugins/Autodafe/samples/table8-hvoice/58.wav", true );
FileLoop *waveFile507= new FileLoop("plugins/Autodafe/samples/table8-hvoice/59.wav", true );
FileLoop *waveFile508= new FileLoop("plugins/Autodafe/samples/table8-hvoice/60.wav", true );
FileLoop *waveFile509= new FileLoop("plugins/Autodafe/samples/table8-hvoice/61.wav", true );
FileLoop *waveFile510= new FileLoop("plugins/Autodafe/samples/table8-hvoice/62.wav", true );
FileLoop *waveFile511= new FileLoop("plugins/Autodafe/samples/table8-hvoice/63.wav", true );




FileLoop *waveFile512= new FileLoop("plugins/Autodafe/samples/table9-epiano/00.wav", true );
FileLoop *waveFile513= new FileLoop("plugins/Autodafe/samples/table9-epiano/01.wav", true );
FileLoop *waveFile514= new FileLoop("plugins/Autodafe/samples/table9-epiano/02.wav", true );
FileLoop *waveFile515= new FileLoop("plugins/Autodafe/samples/table9-epiano/03.wav", true );
FileLoop *waveFile516= new FileLoop("plugins/Autodafe/samples/table9-epiano/04.wav", true );
FileLoop *waveFile517= new FileLoop("plugins/Autodafe/samples/table9-epiano/05.wav", true );
FileLoop *waveFile518= new FileLoop("plugins/Autodafe/samples/table9-epiano/06.wav", true );
FileLoop *waveFile519= new FileLoop("plugins/Autodafe/samples/table9-epiano/07.wav", true );
FileLoop *waveFile520= new FileLoop("plugins/Autodafe/samples/table9-epiano/08.wav", true );
FileLoop *waveFile521= new FileLoop("plugins/Autodafe/samples/table9-epiano/09.wav", true );
FileLoop *waveFile522= new FileLoop("plugins/Autodafe/samples/table9-epiano/10.wav", true );
FileLoop *waveFile523= new FileLoop("plugins/Autodafe/samples/table9-epiano/11.wav", true );
FileLoop *waveFile524= new FileLoop("plugins/Autodafe/samples/table9-epiano/12.wav", true );
FileLoop *waveFile525= new FileLoop("plugins/Autodafe/samples/table9-epiano/13.wav", true );
FileLoop *waveFile526= new FileLoop("plugins/Autodafe/samples/table9-epiano/14.wav", true );
FileLoop *waveFile527= new FileLoop("plugins/Autodafe/samples/table9-epiano/15.wav", true );
FileLoop *waveFile528= new FileLoop("plugins/Autodafe/samples/table9-epiano/16.wav", true );
FileLoop *waveFile529= new FileLoop("plugins/Autodafe/samples/table9-epiano/17.wav", true );
FileLoop *waveFile530= new FileLoop("plugins/Autodafe/samples/table9-epiano/18.wav", true );
FileLoop *waveFile531= new FileLoop("plugins/Autodafe/samples/table9-epiano/19.wav", true );
FileLoop *waveFile532= new FileLoop("plugins/Autodafe/samples/table9-epiano/20.wav", true );
FileLoop *waveFile533= new FileLoop("plugins/Autodafe/samples/table9-epiano/21.wav", true );
FileLoop *waveFile534= new FileLoop("plugins/Autodafe/samples/table9-epiano/22.wav", true );
FileLoop *waveFile535= new FileLoop("plugins/Autodafe/samples/table9-epiano/23.wav", true );
FileLoop *waveFile536= new FileLoop("plugins/Autodafe/samples/table9-epiano/24.wav", true );
FileLoop *waveFile537= new FileLoop("plugins/Autodafe/samples/table9-epiano/25.wav", true );
FileLoop *waveFile538= new FileLoop("plugins/Autodafe/samples/table9-epiano/26.wav", true );
FileLoop *waveFile539= new FileLoop("plugins/Autodafe/samples/table9-epiano/27.wav", true );
FileLoop *waveFile540= new FileLoop("plugins/Autodafe/samples/table9-epiano/28.wav", true );
FileLoop *waveFile541= new FileLoop("plugins/Autodafe/samples/table9-epiano/29.wav", true );
FileLoop *waveFile542= new FileLoop("plugins/Autodafe/samples/table9-epiano/30.wav", true );
FileLoop *waveFile543= new FileLoop("plugins/Autodafe/samples/table9-epiano/31.wav", true );
FileLoop *waveFile544= new FileLoop("plugins/Autodafe/samples/table9-epiano/32.wav", true );
FileLoop *waveFile545= new FileLoop("plugins/Autodafe/samples/table9-epiano/33.wav", true );
FileLoop *waveFile546= new FileLoop("plugins/Autodafe/samples/table9-epiano/34.wav", true );
FileLoop *waveFile547= new FileLoop("plugins/Autodafe/samples/table9-epiano/35.wav", true );
FileLoop *waveFile548= new FileLoop("plugins/Autodafe/samples/table9-epiano/36.wav", true );
FileLoop *waveFile549= new FileLoop("plugins/Autodafe/samples/table9-epiano/37.wav", true );
FileLoop *waveFile550= new FileLoop("plugins/Autodafe/samples/table9-epiano/38.wav", true );
FileLoop *waveFile551= new FileLoop("plugins/Autodafe/samples/table9-epiano/39.wav", true );
FileLoop *waveFile552= new FileLoop("plugins/Autodafe/samples/table9-epiano/40.wav", true );
FileLoop *waveFile553= new FileLoop("plugins/Autodafe/samples/table9-epiano/41.wav", true );
FileLoop *waveFile554= new FileLoop("plugins/Autodafe/samples/table9-epiano/42.wav", true );
FileLoop *waveFile555= new FileLoop("plugins/Autodafe/samples/table9-epiano/43.wav", true );
FileLoop *waveFile556= new FileLoop("plugins/Autodafe/samples/table9-epiano/44.wav", true );
FileLoop *waveFile557= new FileLoop("plugins/Autodafe/samples/table9-epiano/45.wav", true );
FileLoop *waveFile558= new FileLoop("plugins/Autodafe/samples/table9-epiano/46.wav", true );
FileLoop *waveFile559= new FileLoop("plugins/Autodafe/samples/table9-epiano/47.wav", true );
FileLoop *waveFile560= new FileLoop("plugins/Autodafe/samples/table9-epiano/48.wav", true );
FileLoop *waveFile561= new FileLoop("plugins/Autodafe/samples/table9-epiano/49.wav", true );
FileLoop *waveFile562= new FileLoop("plugins/Autodafe/samples/table9-epiano/50.wav", true );
FileLoop *waveFile563= new FileLoop("plugins/Autodafe/samples/table9-epiano/51.wav", true );
FileLoop *waveFile564= new FileLoop("plugins/Autodafe/samples/table9-epiano/52.wav", true );
FileLoop *waveFile565= new FileLoop("plugins/Autodafe/samples/table9-epiano/53.wav", true );
FileLoop *waveFile566= new FileLoop("plugins/Autodafe/samples/table9-epiano/54.wav", true );
FileLoop *waveFile567= new FileLoop("plugins/Autodafe/samples/table9-epiano/55.wav", true );
FileLoop *waveFile568= new FileLoop("plugins/Autodafe/samples/table9-epiano/56.wav", true );
FileLoop *waveFile569= new FileLoop("plugins/Autodafe/samples/table9-epiano/57.wav", true );
FileLoop *waveFile570= new FileLoop("plugins/Autodafe/samples/table9-epiano/58.wav", true );
FileLoop *waveFile571= new FileLoop("plugins/Autodafe/samples/table9-epiano/59.wav", true );
FileLoop *waveFile572= new FileLoop("plugins/Autodafe/samples/table9-epiano/60.wav", true );
FileLoop *waveFile573= new FileLoop("plugins/Autodafe/samples/table9-epiano/61.wav", true );
FileLoop *waveFile574= new FileLoop("plugins/Autodafe/samples/table9-epiano/62.wav", true );
FileLoop *waveFile575= new FileLoop("plugins/Autodafe/samples/table9-epiano/63.wav", true );







FileLoop *waveFile576= new FileLoop("plugins/Autodafe/samples/table10-dbass/00.wav", true );
FileLoop *waveFile577= new FileLoop("plugins/Autodafe/samples/table10-dbass/01.wav", true );
FileLoop *waveFile578= new FileLoop("plugins/Autodafe/samples/table10-dbass/02.wav", true );
FileLoop *waveFile579= new FileLoop("plugins/Autodafe/samples/table10-dbass/03.wav", true );
FileLoop *waveFile580= new FileLoop("plugins/Autodafe/samples/table10-dbass/04.wav", true );
FileLoop *waveFile581= new FileLoop("plugins/Autodafe/samples/table10-dbass/05.wav", true );
FileLoop *waveFile582= new FileLoop("plugins/Autodafe/samples/table10-dbass/06.wav", true );
FileLoop *waveFile583= new FileLoop("plugins/Autodafe/samples/table10-dbass/07.wav", true );
FileLoop *waveFile584= new FileLoop("plugins/Autodafe/samples/table10-dbass/08.wav", true );
FileLoop *waveFile585= new FileLoop("plugins/Autodafe/samples/table10-dbass/09.wav", true );
FileLoop *waveFile586= new FileLoop("plugins/Autodafe/samples/table10-dbass/10.wav", true );
FileLoop *waveFile587= new FileLoop("plugins/Autodafe/samples/table10-dbass/11.wav", true );
FileLoop *waveFile588= new FileLoop("plugins/Autodafe/samples/table10-dbass/12.wav", true );
FileLoop *waveFile589= new FileLoop("plugins/Autodafe/samples/table10-dbass/13.wav", true );
FileLoop *waveFile590= new FileLoop("plugins/Autodafe/samples/table10-dbass/14.wav", true );
FileLoop *waveFile591= new FileLoop("plugins/Autodafe/samples/table10-dbass/15.wav", true );
FileLoop *waveFile592= new FileLoop("plugins/Autodafe/samples/table10-dbass/16.wav", true );
FileLoop *waveFile593= new FileLoop("plugins/Autodafe/samples/table10-dbass/17.wav", true );
FileLoop *waveFile594= new FileLoop("plugins/Autodafe/samples/table10-dbass/18.wav", true );
FileLoop *waveFile595= new FileLoop("plugins/Autodafe/samples/table10-dbass/19.wav", true );
FileLoop *waveFile596= new FileLoop("plugins/Autodafe/samples/table10-dbass/20.wav", true );
FileLoop *waveFile597= new FileLoop("plugins/Autodafe/samples/table10-dbass/21.wav", true );
FileLoop *waveFile598= new FileLoop("plugins/Autodafe/samples/table10-dbass/22.wav", true );
FileLoop *waveFile599= new FileLoop("plugins/Autodafe/samples/table10-dbass/23.wav", true );
FileLoop *waveFile600= new FileLoop("plugins/Autodafe/samples/table10-dbass/24.wav", true );
FileLoop *waveFile601= new FileLoop("plugins/Autodafe/samples/table10-dbass/25.wav", true );
FileLoop *waveFile602= new FileLoop("plugins/Autodafe/samples/table10-dbass/26.wav", true );
FileLoop *waveFile603= new FileLoop("plugins/Autodafe/samples/table10-dbass/27.wav", true );
FileLoop *waveFile604= new FileLoop("plugins/Autodafe/samples/table10-dbass/28.wav", true );
FileLoop *waveFile605= new FileLoop("plugins/Autodafe/samples/table10-dbass/29.wav", true );
FileLoop *waveFile606= new FileLoop("plugins/Autodafe/samples/table10-dbass/30.wav", true );
FileLoop *waveFile607= new FileLoop("plugins/Autodafe/samples/table10-dbass/31.wav", true );
FileLoop *waveFile608= new FileLoop("plugins/Autodafe/samples/table10-dbass/32.wav", true );
FileLoop *waveFile609= new FileLoop("plugins/Autodafe/samples/table10-dbass/33.wav", true );
FileLoop *waveFile610= new FileLoop("plugins/Autodafe/samples/table10-dbass/34.wav", true );
FileLoop *waveFile611= new FileLoop("plugins/Autodafe/samples/table10-dbass/35.wav", true );
FileLoop *waveFile612= new FileLoop("plugins/Autodafe/samples/table10-dbass/36.wav", true );
FileLoop *waveFile613= new FileLoop("plugins/Autodafe/samples/table10-dbass/37.wav", true );
FileLoop *waveFile614= new FileLoop("plugins/Autodafe/samples/table10-dbass/38.wav", true );
FileLoop *waveFile615= new FileLoop("plugins/Autodafe/samples/table10-dbass/39.wav", true );
FileLoop *waveFile616= new FileLoop("plugins/Autodafe/samples/table10-dbass/40.wav", true );
FileLoop *waveFile617= new FileLoop("plugins/Autodafe/samples/table10-dbass/41.wav", true );
FileLoop *waveFile618= new FileLoop("plugins/Autodafe/samples/table10-dbass/42.wav", true );
FileLoop *waveFile619= new FileLoop("plugins/Autodafe/samples/table10-dbass/43.wav", true );
FileLoop *waveFile620= new FileLoop("plugins/Autodafe/samples/table10-dbass/44.wav", true );
FileLoop *waveFile621= new FileLoop("plugins/Autodafe/samples/table10-dbass/45.wav", true );
FileLoop *waveFile622= new FileLoop("plugins/Autodafe/samples/table10-dbass/46.wav", true );
FileLoop *waveFile623= new FileLoop("plugins/Autodafe/samples/table10-dbass/47.wav", true );
FileLoop *waveFile624= new FileLoop("plugins/Autodafe/samples/table10-dbass/48.wav", true );
FileLoop *waveFile625= new FileLoop("plugins/Autodafe/samples/table10-dbass/49.wav", true );
FileLoop *waveFile626= new FileLoop("plugins/Autodafe/samples/table10-dbass/50.wav", true );
FileLoop *waveFile627= new FileLoop("plugins/Autodafe/samples/table10-dbass/51.wav", true );
FileLoop *waveFile628= new FileLoop("plugins/Autodafe/samples/table10-dbass/52.wav", true );
FileLoop *waveFile629= new FileLoop("plugins/Autodafe/samples/table10-dbass/53.wav", true );
FileLoop *waveFile630= new FileLoop("plugins/Autodafe/samples/table10-dbass/54.wav", true );
FileLoop *waveFile631= new FileLoop("plugins/Autodafe/samples/table10-dbass/55.wav", true );
FileLoop *waveFile632= new FileLoop("plugins/Autodafe/samples/table10-dbass/56.wav", true );
FileLoop *waveFile633= new FileLoop("plugins/Autodafe/samples/table10-dbass/57.wav", true );
FileLoop *waveFile634= new FileLoop("plugins/Autodafe/samples/table10-dbass/58.wav", true );
FileLoop *waveFile635= new FileLoop("plugins/Autodafe/samples/table10-dbass/59.wav", true );
FileLoop *waveFile636= new FileLoop("plugins/Autodafe/samples/table10-dbass/60.wav", true );
FileLoop *waveFile637= new FileLoop("plugins/Autodafe/samples/table10-dbass/61.wav", true );
FileLoop *waveFile638= new FileLoop("plugins/Autodafe/samples/table10-dbass/62.wav", true );
FileLoop *waveFile639= new FileLoop("plugins/Autodafe/samples/table10-dbass/63.wav", true );








FileLoop *waveFile640= new FileLoop("plugins/Autodafe/samples/table11-ebass/00.wav", true );
FileLoop *waveFile641= new FileLoop("plugins/Autodafe/samples/table11-ebass/01.wav", true );
FileLoop *waveFile642= new FileLoop("plugins/Autodafe/samples/table11-ebass/02.wav", true );
FileLoop *waveFile643= new FileLoop("plugins/Autodafe/samples/table11-ebass/03.wav", true );
FileLoop *waveFile644= new FileLoop("plugins/Autodafe/samples/table11-ebass/04.wav", true );
FileLoop *waveFile645= new FileLoop("plugins/Autodafe/samples/table11-ebass/05.wav", true );
FileLoop *waveFile646= new FileLoop("plugins/Autodafe/samples/table11-ebass/06.wav", true );
FileLoop *waveFile647= new FileLoop("plugins/Autodafe/samples/table11-ebass/07.wav", true );
FileLoop *waveFile648= new FileLoop("plugins/Autodafe/samples/table11-ebass/08.wav", true );
FileLoop *waveFile649= new FileLoop("plugins/Autodafe/samples/table11-ebass/09.wav", true );
FileLoop *waveFile650= new FileLoop("plugins/Autodafe/samples/table11-ebass/10.wav", true );
FileLoop *waveFile651= new FileLoop("plugins/Autodafe/samples/table11-ebass/11.wav", true );
FileLoop *waveFile652= new FileLoop("plugins/Autodafe/samples/table11-ebass/12.wav", true );
FileLoop *waveFile653= new FileLoop("plugins/Autodafe/samples/table11-ebass/13.wav", true );
FileLoop *waveFile654= new FileLoop("plugins/Autodafe/samples/table11-ebass/14.wav", true );
FileLoop *waveFile655= new FileLoop("plugins/Autodafe/samples/table11-ebass/15.wav", true );
FileLoop *waveFile656= new FileLoop("plugins/Autodafe/samples/table11-ebass/16.wav", true );
FileLoop *waveFile657= new FileLoop("plugins/Autodafe/samples/table11-ebass/17.wav", true );
FileLoop *waveFile658= new FileLoop("plugins/Autodafe/samples/table11-ebass/18.wav", true );
FileLoop *waveFile659= new FileLoop("plugins/Autodafe/samples/table11-ebass/19.wav", true );
FileLoop *waveFile660= new FileLoop("plugins/Autodafe/samples/table11-ebass/20.wav", true );
FileLoop *waveFile661= new FileLoop("plugins/Autodafe/samples/table11-ebass/21.wav", true );
FileLoop *waveFile662= new FileLoop("plugins/Autodafe/samples/table11-ebass/22.wav", true );
FileLoop *waveFile663= new FileLoop("plugins/Autodafe/samples/table11-ebass/23.wav", true );
FileLoop *waveFile664= new FileLoop("plugins/Autodafe/samples/table11-ebass/24.wav", true );
FileLoop *waveFile665= new FileLoop("plugins/Autodafe/samples/table11-ebass/25.wav", true );
FileLoop *waveFile666= new FileLoop("plugins/Autodafe/samples/table11-ebass/26.wav", true );
FileLoop *waveFile667= new FileLoop("plugins/Autodafe/samples/table11-ebass/27.wav", true );
FileLoop *waveFile668= new FileLoop("plugins/Autodafe/samples/table11-ebass/28.wav", true );
FileLoop *waveFile669= new FileLoop("plugins/Autodafe/samples/table11-ebass/29.wav", true );
FileLoop *waveFile670= new FileLoop("plugins/Autodafe/samples/table11-ebass/30.wav", true );
FileLoop *waveFile671= new FileLoop("plugins/Autodafe/samples/table11-ebass/31.wav", true );
FileLoop *waveFile672= new FileLoop("plugins/Autodafe/samples/table11-ebass/32.wav", true );
FileLoop *waveFile673= new FileLoop("plugins/Autodafe/samples/table11-ebass/33.wav", true );
FileLoop *waveFile674= new FileLoop("plugins/Autodafe/samples/table11-ebass/34.wav", true );
FileLoop *waveFile675= new FileLoop("plugins/Autodafe/samples/table11-ebass/35.wav", true );
FileLoop *waveFile676= new FileLoop("plugins/Autodafe/samples/table11-ebass/36.wav", true );
FileLoop *waveFile677= new FileLoop("plugins/Autodafe/samples/table11-ebass/37.wav", true );
FileLoop *waveFile678= new FileLoop("plugins/Autodafe/samples/table11-ebass/38.wav", true );
FileLoop *waveFile679= new FileLoop("plugins/Autodafe/samples/table11-ebass/39.wav", true );
FileLoop *waveFile680= new FileLoop("plugins/Autodafe/samples/table11-ebass/40.wav", true );
FileLoop *waveFile681= new FileLoop("plugins/Autodafe/samples/table11-ebass/41.wav", true );
FileLoop *waveFile682= new FileLoop("plugins/Autodafe/samples/table11-ebass/42.wav", true );
FileLoop *waveFile683= new FileLoop("plugins/Autodafe/samples/table11-ebass/43.wav", true );
FileLoop *waveFile684= new FileLoop("plugins/Autodafe/samples/table11-ebass/44.wav", true );
FileLoop *waveFile685= new FileLoop("plugins/Autodafe/samples/table11-ebass/45.wav", true );
FileLoop *waveFile686= new FileLoop("plugins/Autodafe/samples/table11-ebass/46.wav", true );
FileLoop *waveFile687= new FileLoop("plugins/Autodafe/samples/table11-ebass/47.wav", true );
FileLoop *waveFile688= new FileLoop("plugins/Autodafe/samples/table11-ebass/48.wav", true );
FileLoop *waveFile689= new FileLoop("plugins/Autodafe/samples/table11-ebass/49.wav", true );
FileLoop *waveFile690= new FileLoop("plugins/Autodafe/samples/table11-ebass/50.wav", true );
FileLoop *waveFile691= new FileLoop("plugins/Autodafe/samples/table11-ebass/51.wav", true );
FileLoop *waveFile692= new FileLoop("plugins/Autodafe/samples/table11-ebass/52.wav", true );
FileLoop *waveFile693= new FileLoop("plugins/Autodafe/samples/table11-ebass/53.wav", true );
FileLoop *waveFile694= new FileLoop("plugins/Autodafe/samples/table11-ebass/54.wav", true );
FileLoop *waveFile695= new FileLoop("plugins/Autodafe/samples/table11-ebass/55.wav", true );
FileLoop *waveFile696= new FileLoop("plugins/Autodafe/samples/table11-ebass/56.wav", true );
FileLoop *waveFile697= new FileLoop("plugins/Autodafe/samples/table11-ebass/57.wav", true );
FileLoop *waveFile698= new FileLoop("plugins/Autodafe/samples/table11-ebass/58.wav", true );
FileLoop *waveFile699= new FileLoop("plugins/Autodafe/samples/table11-ebass/59.wav", true );
FileLoop *waveFile700= new FileLoop("plugins/Autodafe/samples/table11-ebass/60.wav", true );
FileLoop *waveFile701= new FileLoop("plugins/Autodafe/samples/table11-ebass/61.wav", true );
FileLoop *waveFile702= new FileLoop("plugins/Autodafe/samples/table11-ebass/62.wav", true );
FileLoop *waveFile703= new FileLoop("plugins/Autodafe/samples/table11-ebass/63.wav", true );



FileLoop *waveFile704= new FileLoop("plugins/Autodafe/samples/table12-eorgan/00.wav", true );
FileLoop *waveFile705= new FileLoop("plugins/Autodafe/samples/table12-eorgan/01.wav", true );
FileLoop *waveFile706= new FileLoop("plugins/Autodafe/samples/table12-eorgan/02.wav", true );
FileLoop *waveFile707= new FileLoop("plugins/Autodafe/samples/table12-eorgan/03.wav", true );
FileLoop *waveFile708= new FileLoop("plugins/Autodafe/samples/table12-eorgan/04.wav", true );
FileLoop *waveFile709= new FileLoop("plugins/Autodafe/samples/table12-eorgan/05.wav", true );
FileLoop *waveFile710= new FileLoop("plugins/Autodafe/samples/table12-eorgan/06.wav", true );
FileLoop *waveFile711= new FileLoop("plugins/Autodafe/samples/table12-eorgan/07.wav", true );
FileLoop *waveFile712= new FileLoop("plugins/Autodafe/samples/table12-eorgan/08.wav", true );
FileLoop *waveFile713= new FileLoop("plugins/Autodafe/samples/table12-eorgan/09.wav", true );
FileLoop *waveFile714= new FileLoop("plugins/Autodafe/samples/table12-eorgan/10.wav", true );
FileLoop *waveFile715= new FileLoop("plugins/Autodafe/samples/table12-eorgan/11.wav", true );
FileLoop *waveFile716= new FileLoop("plugins/Autodafe/samples/table12-eorgan/12.wav", true );
FileLoop *waveFile717= new FileLoop("plugins/Autodafe/samples/table12-eorgan/13.wav", true );
FileLoop *waveFile718= new FileLoop("plugins/Autodafe/samples/table12-eorgan/14.wav", true );
FileLoop *waveFile719= new FileLoop("plugins/Autodafe/samples/table12-eorgan/15.wav", true );
FileLoop *waveFile720= new FileLoop("plugins/Autodafe/samples/table12-eorgan/16.wav", true );
FileLoop *waveFile721= new FileLoop("plugins/Autodafe/samples/table12-eorgan/17.wav", true );
FileLoop *waveFile722= new FileLoop("plugins/Autodafe/samples/table12-eorgan/18.wav", true );
FileLoop *waveFile723= new FileLoop("plugins/Autodafe/samples/table12-eorgan/19.wav", true );
FileLoop *waveFile724= new FileLoop("plugins/Autodafe/samples/table12-eorgan/20.wav", true );
FileLoop *waveFile725= new FileLoop("plugins/Autodafe/samples/table12-eorgan/21.wav", true );
FileLoop *waveFile726= new FileLoop("plugins/Autodafe/samples/table12-eorgan/22.wav", true );
FileLoop *waveFile727= new FileLoop("plugins/Autodafe/samples/table12-eorgan/23.wav", true );
FileLoop *waveFile728= new FileLoop("plugins/Autodafe/samples/table12-eorgan/24.wav", true );
FileLoop *waveFile729= new FileLoop("plugins/Autodafe/samples/table12-eorgan/25.wav", true );
FileLoop *waveFile730= new FileLoop("plugins/Autodafe/samples/table12-eorgan/26.wav", true );
FileLoop *waveFile731= new FileLoop("plugins/Autodafe/samples/table12-eorgan/27.wav", true );
FileLoop *waveFile732= new FileLoop("plugins/Autodafe/samples/table12-eorgan/28.wav", true );
FileLoop *waveFile733= new FileLoop("plugins/Autodafe/samples/table12-eorgan/29.wav", true );
FileLoop *waveFile734= new FileLoop("plugins/Autodafe/samples/table12-eorgan/30.wav", true );
FileLoop *waveFile735= new FileLoop("plugins/Autodafe/samples/table12-eorgan/31.wav", true );
FileLoop *waveFile736= new FileLoop("plugins/Autodafe/samples/table12-eorgan/32.wav", true );
FileLoop *waveFile737= new FileLoop("plugins/Autodafe/samples/table12-eorgan/33.wav", true );
FileLoop *waveFile738= new FileLoop("plugins/Autodafe/samples/table12-eorgan/34.wav", true );
FileLoop *waveFile739= new FileLoop("plugins/Autodafe/samples/table12-eorgan/35.wav", true );
FileLoop *waveFile740= new FileLoop("plugins/Autodafe/samples/table12-eorgan/36.wav", true );
FileLoop *waveFile741= new FileLoop("plugins/Autodafe/samples/table12-eorgan/37.wav", true );
FileLoop *waveFile742= new FileLoop("plugins/Autodafe/samples/table12-eorgan/38.wav", true );
FileLoop *waveFile743= new FileLoop("plugins/Autodafe/samples/table12-eorgan/39.wav", true );
FileLoop *waveFile744= new FileLoop("plugins/Autodafe/samples/table12-eorgan/40.wav", true );
FileLoop *waveFile745= new FileLoop("plugins/Autodafe/samples/table12-eorgan/41.wav", true );
FileLoop *waveFile746= new FileLoop("plugins/Autodafe/samples/table12-eorgan/42.wav", true );
FileLoop *waveFile747= new FileLoop("plugins/Autodafe/samples/table12-eorgan/43.wav", true );
FileLoop *waveFile748= new FileLoop("plugins/Autodafe/samples/table12-eorgan/44.wav", true );
FileLoop *waveFile749= new FileLoop("plugins/Autodafe/samples/table12-eorgan/45.wav", true );
FileLoop *waveFile750= new FileLoop("plugins/Autodafe/samples/table12-eorgan/46.wav", true );
FileLoop *waveFile751= new FileLoop("plugins/Autodafe/samples/table12-eorgan/47.wav", true );
FileLoop *waveFile752= new FileLoop("plugins/Autodafe/samples/table12-eorgan/48.wav", true );
FileLoop *waveFile753= new FileLoop("plugins/Autodafe/samples/table12-eorgan/49.wav", true );
FileLoop *waveFile754= new FileLoop("plugins/Autodafe/samples/table12-eorgan/50.wav", true );
FileLoop *waveFile755= new FileLoop("plugins/Autodafe/samples/table12-eorgan/51.wav", true );
FileLoop *waveFile756= new FileLoop("plugins/Autodafe/samples/table12-eorgan/52.wav", true );
FileLoop *waveFile757= new FileLoop("plugins/Autodafe/samples/table12-eorgan/53.wav", true );
FileLoop *waveFile758= new FileLoop("plugins/Autodafe/samples/table12-eorgan/54.wav", true );
FileLoop *waveFile759= new FileLoop("plugins/Autodafe/samples/table12-eorgan/55.wav", true );
FileLoop *waveFile760= new FileLoop("plugins/Autodafe/samples/table12-eorgan/56.wav", true );
FileLoop *waveFile761= new FileLoop("plugins/Autodafe/samples/table12-eorgan/57.wav", true );
FileLoop *waveFile762= new FileLoop("plugins/Autodafe/samples/table12-eorgan/58.wav", true );
FileLoop *waveFile763= new FileLoop("plugins/Autodafe/samples/table12-eorgan/59.wav", true );
FileLoop *waveFile764= new FileLoop("plugins/Autodafe/samples/table12-eorgan/60.wav", true );
FileLoop *waveFile765= new FileLoop("plugins/Autodafe/samples/table12-eorgan/61.wav", true );
FileLoop *waveFile766= new FileLoop("plugins/Autodafe/samples/table12-eorgan/62.wav", true );
FileLoop *waveFile767= new FileLoop("plugins/Autodafe/samples/table12-eorgan/63.wav", true );






FileLoop *waveFile768= new FileLoop("plugins/Autodafe/samples/table13-fmsynth/00.wav", true );
FileLoop *waveFile769= new FileLoop("plugins/Autodafe/samples/table13-fmsynth/01.wav", true );
FileLoop *waveFile770= new FileLoop("plugins/Autodafe/samples/table13-fmsynth/02.wav", true );
FileLoop *waveFile771= new FileLoop("plugins/Autodafe/samples/table13-fmsynth/03.wav", true );
FileLoop *waveFile772= new FileLoop("plugins/Autodafe/samples/table13-fmsynth/04.wav", true );
FileLoop *waveFile773= new FileLoop("plugins/Autodafe/samples/table13-fmsynth/05.wav", true );
FileLoop *waveFile774= new FileLoop("plugins/Autodafe/samples/table13-fmsynth/06.wav", true );
FileLoop *waveFile775= new FileLoop("plugins/Autodafe/samples/table13-fmsynth/07.wav", true );
FileLoop *waveFile776= new FileLoop("plugins/Autodafe/samples/table13-fmsynth/08.wav", true );
FileLoop *waveFile777= new FileLoop("plugins/Autodafe/samples/table13-fmsynth/09.wav", true );
FileLoop *waveFile778= new FileLoop("plugins/Autodafe/samples/table13-fmsynth/10.wav", true );
FileLoop *waveFile779= new FileLoop("plugins/Autodafe/samples/table13-fmsynth/11.wav", true );
FileLoop *waveFile780= new FileLoop("plugins/Autodafe/samples/table13-fmsynth/12.wav", true );
FileLoop *waveFile781= new FileLoop("plugins/Autodafe/samples/table13-fmsynth/13.wav", true );
FileLoop *waveFile782= new FileLoop("plugins/Autodafe/samples/table13-fmsynth/14.wav", true );
FileLoop *waveFile783= new FileLoop("plugins/Autodafe/samples/table13-fmsynth/15.wav", true );
FileLoop *waveFile784= new FileLoop("plugins/Autodafe/samples/table13-fmsynth/16.wav", true );
FileLoop *waveFile785= new FileLoop("plugins/Autodafe/samples/table13-fmsynth/17.wav", true );
FileLoop *waveFile786= new FileLoop("plugins/Autodafe/samples/table13-fmsynth/18.wav", true );
FileLoop *waveFile787= new FileLoop("plugins/Autodafe/samples/table13-fmsynth/19.wav", true );
FileLoop *waveFile788= new FileLoop("plugins/Autodafe/samples/table13-fmsynth/20.wav", true );
FileLoop *waveFile789= new FileLoop("plugins/Autodafe/samples/table13-fmsynth/21.wav", true );
FileLoop *waveFile790= new FileLoop("plugins/Autodafe/samples/table13-fmsynth/22.wav", true );
FileLoop *waveFile791= new FileLoop("plugins/Autodafe/samples/table13-fmsynth/23.wav", true );
FileLoop *waveFile792= new FileLoop("plugins/Autodafe/samples/table13-fmsynth/24.wav", true );
FileLoop *waveFile793= new FileLoop("plugins/Autodafe/samples/table13-fmsynth/25.wav", true );
FileLoop *waveFile794= new FileLoop("plugins/Autodafe/samples/table13-fmsynth/26.wav", true );
FileLoop *waveFile795= new FileLoop("plugins/Autodafe/samples/table13-fmsynth/27.wav", true );
FileLoop *waveFile796= new FileLoop("plugins/Autodafe/samples/table13-fmsynth/28.wav", true );
FileLoop *waveFile797= new FileLoop("plugins/Autodafe/samples/table13-fmsynth/29.wav", true );
FileLoop *waveFile798= new FileLoop("plugins/Autodafe/samples/table13-fmsynth/30.wav", true );
FileLoop *waveFile799= new FileLoop("plugins/Autodafe/samples/table13-fmsynth/31.wav", true );
FileLoop *waveFile800= new FileLoop("plugins/Autodafe/samples/table13-fmsynth/32.wav", true );
FileLoop *waveFile801= new FileLoop("plugins/Autodafe/samples/table13-fmsynth/33.wav", true );
FileLoop *waveFile802= new FileLoop("plugins/Autodafe/samples/table13-fmsynth/34.wav", true );
FileLoop *waveFile803= new FileLoop("plugins/Autodafe/samples/table13-fmsynth/35.wav", true );
FileLoop *waveFile804= new FileLoop("plugins/Autodafe/samples/table13-fmsynth/36.wav", true );
FileLoop *waveFile805= new FileLoop("plugins/Autodafe/samples/table13-fmsynth/37.wav", true );
FileLoop *waveFile806= new FileLoop("plugins/Autodafe/samples/table13-fmsynth/38.wav", true );
FileLoop *waveFile807= new FileLoop("plugins/Autodafe/samples/table13-fmsynth/39.wav", true );
FileLoop *waveFile808= new FileLoop("plugins/Autodafe/samples/table13-fmsynth/40.wav", true );
FileLoop *waveFile809= new FileLoop("plugins/Autodafe/samples/table13-fmsynth/41.wav", true );
FileLoop *waveFile810= new FileLoop("plugins/Autodafe/samples/table13-fmsynth/42.wav", true );
FileLoop *waveFile811= new FileLoop("plugins/Autodafe/samples/table13-fmsynth/43.wav", true );
FileLoop *waveFile812= new FileLoop("plugins/Autodafe/samples/table13-fmsynth/44.wav", true );
FileLoop *waveFile813= new FileLoop("plugins/Autodafe/samples/table13-fmsynth/45.wav", true );
FileLoop *waveFile814= new FileLoop("plugins/Autodafe/samples/table13-fmsynth/46.wav", true );
FileLoop *waveFile815= new FileLoop("plugins/Autodafe/samples/table13-fmsynth/47.wav", true );
FileLoop *waveFile816= new FileLoop("plugins/Autodafe/samples/table13-fmsynth/48.wav", true );
FileLoop *waveFile817= new FileLoop("plugins/Autodafe/samples/table13-fmsynth/49.wav", true );
FileLoop *waveFile818= new FileLoop("plugins/Autodafe/samples/table13-fmsynth/50.wav", true );
FileLoop *waveFile819= new FileLoop("plugins/Autodafe/samples/table13-fmsynth/51.wav", true );
FileLoop *waveFile820= new FileLoop("plugins/Autodafe/samples/table13-fmsynth/52.wav", true );
FileLoop *waveFile821= new FileLoop("plugins/Autodafe/samples/table13-fmsynth/53.wav", true );
FileLoop *waveFile822= new FileLoop("plugins/Autodafe/samples/table13-fmsynth/54.wav", true );
FileLoop *waveFile823= new FileLoop("plugins/Autodafe/samples/table13-fmsynth/55.wav", true );
FileLoop *waveFile824= new FileLoop("plugins/Autodafe/samples/table13-fmsynth/56.wav", true );
FileLoop *waveFile825= new FileLoop("plugins/Autodafe/samples/table13-fmsynth/57.wav", true );
FileLoop *waveFile826= new FileLoop("plugins/Autodafe/samples/table13-fmsynth/58.wav", true );
FileLoop *waveFile827= new FileLoop("plugins/Autodafe/samples/table13-fmsynth/59.wav", true );
FileLoop *waveFile828= new FileLoop("plugins/Autodafe/samples/table13-fmsynth/60.wav", true );
FileLoop *waveFile829= new FileLoop("plugins/Autodafe/samples/table13-fmsynth/61.wav", true );
FileLoop *waveFile830= new FileLoop("plugins/Autodafe/samples/table13-fmsynth/62.wav", true );
FileLoop *waveFile831= new FileLoop("plugins/Autodafe/samples/table13-fmsynth/63.wav", true );







FileLoop *waveFile832= new FileLoop("plugins/Autodafe/samples/table14-fmsynth2/00.wav", true );
FileLoop *waveFile833= new FileLoop("plugins/Autodafe/samples/table14-fmsynth2/01.wav", true );
FileLoop *waveFile834= new FileLoop("plugins/Autodafe/samples/table14-fmsynth2/02.wav", true );
FileLoop *waveFile835= new FileLoop("plugins/Autodafe/samples/table14-fmsynth2/03.wav", true );
FileLoop *waveFile836= new FileLoop("plugins/Autodafe/samples/table14-fmsynth2/04.wav", true );
FileLoop *waveFile837= new FileLoop("plugins/Autodafe/samples/table14-fmsynth2/05.wav", true );
FileLoop *waveFile838= new FileLoop("plugins/Autodafe/samples/table14-fmsynth2/06.wav", true );
FileLoop *waveFile839= new FileLoop("plugins/Autodafe/samples/table14-fmsynth2/07.wav", true );
FileLoop *waveFile840= new FileLoop("plugins/Autodafe/samples/table14-fmsynth2/08.wav", true );
FileLoop *waveFile841= new FileLoop("plugins/Autodafe/samples/table14-fmsynth2/09.wav", true );
FileLoop *waveFile842= new FileLoop("plugins/Autodafe/samples/table14-fmsynth2/10.wav", true );
FileLoop *waveFile843= new FileLoop("plugins/Autodafe/samples/table14-fmsynth2/11.wav", true );
FileLoop *waveFile844= new FileLoop("plugins/Autodafe/samples/table14-fmsynth2/12.wav", true );
FileLoop *waveFile845= new FileLoop("plugins/Autodafe/samples/table14-fmsynth2/13.wav", true );
FileLoop *waveFile846= new FileLoop("plugins/Autodafe/samples/table14-fmsynth2/14.wav", true );
FileLoop *waveFile847= new FileLoop("plugins/Autodafe/samples/table14-fmsynth2/15.wav", true );
FileLoop *waveFile848= new FileLoop("plugins/Autodafe/samples/table14-fmsynth2/16.wav", true );
FileLoop *waveFile849= new FileLoop("plugins/Autodafe/samples/table14-fmsynth2/17.wav", true );
FileLoop *waveFile850= new FileLoop("plugins/Autodafe/samples/table14-fmsynth2/18.wav", true );
FileLoop *waveFile851= new FileLoop("plugins/Autodafe/samples/table14-fmsynth2/19.wav", true );
FileLoop *waveFile852= new FileLoop("plugins/Autodafe/samples/table14-fmsynth2/20.wav", true );
FileLoop *waveFile853= new FileLoop("plugins/Autodafe/samples/table14-fmsynth2/21.wav", true );
FileLoop *waveFile854= new FileLoop("plugins/Autodafe/samples/table14-fmsynth2/22.wav", true );
FileLoop *waveFile855= new FileLoop("plugins/Autodafe/samples/table14-fmsynth2/23.wav", true );
FileLoop *waveFile856= new FileLoop("plugins/Autodafe/samples/table14-fmsynth2/24.wav", true );
FileLoop *waveFile857= new FileLoop("plugins/Autodafe/samples/table14-fmsynth2/25.wav", true );
FileLoop *waveFile858= new FileLoop("plugins/Autodafe/samples/table14-fmsynth2/26.wav", true );
FileLoop *waveFile859= new FileLoop("plugins/Autodafe/samples/table14-fmsynth2/27.wav", true );
FileLoop *waveFile860= new FileLoop("plugins/Autodafe/samples/table14-fmsynth2/28.wav", true );
FileLoop *waveFile861= new FileLoop("plugins/Autodafe/samples/table14-fmsynth2/29.wav", true );
FileLoop *waveFile862= new FileLoop("plugins/Autodafe/samples/table14-fmsynth2/30.wav", true );
FileLoop *waveFile863= new FileLoop("plugins/Autodafe/samples/table14-fmsynth2/31.wav", true );
FileLoop *waveFile864= new FileLoop("plugins/Autodafe/samples/table14-fmsynth2/32.wav", true );
FileLoop *waveFile865= new FileLoop("plugins/Autodafe/samples/table14-fmsynth2/33.wav", true );
FileLoop *waveFile866= new FileLoop("plugins/Autodafe/samples/table14-fmsynth2/34.wav", true );
FileLoop *waveFile867= new FileLoop("plugins/Autodafe/samples/table14-fmsynth2/35.wav", true );
FileLoop *waveFile868= new FileLoop("plugins/Autodafe/samples/table14-fmsynth2/36.wav", true );
FileLoop *waveFile869= new FileLoop("plugins/Autodafe/samples/table14-fmsynth2/37.wav", true );
FileLoop *waveFile870= new FileLoop("plugins/Autodafe/samples/table14-fmsynth2/38.wav", true );
FileLoop *waveFile871= new FileLoop("plugins/Autodafe/samples/table14-fmsynth2/39.wav", true );
FileLoop *waveFile872= new FileLoop("plugins/Autodafe/samples/table14-fmsynth2/40.wav", true );
FileLoop *waveFile873= new FileLoop("plugins/Autodafe/samples/table14-fmsynth2/41.wav", true );
FileLoop *waveFile874= new FileLoop("plugins/Autodafe/samples/table14-fmsynth2/42.wav", true );
FileLoop *waveFile875= new FileLoop("plugins/Autodafe/samples/table14-fmsynth2/43.wav", true );
FileLoop *waveFile876= new FileLoop("plugins/Autodafe/samples/table14-fmsynth2/44.wav", true );
FileLoop *waveFile877= new FileLoop("plugins/Autodafe/samples/table14-fmsynth2/45.wav", true );
FileLoop *waveFile878= new FileLoop("plugins/Autodafe/samples/table14-fmsynth2/46.wav", true );
FileLoop *waveFile879= new FileLoop("plugins/Autodafe/samples/table14-fmsynth2/47.wav", true );
FileLoop *waveFile880= new FileLoop("plugins/Autodafe/samples/table14-fmsynth2/48.wav", true );
FileLoop *waveFile881= new FileLoop("plugins/Autodafe/samples/table14-fmsynth2/49.wav", true );
FileLoop *waveFile882= new FileLoop("plugins/Autodafe/samples/table14-fmsynth2/50.wav", true );
FileLoop *waveFile883= new FileLoop("plugins/Autodafe/samples/table14-fmsynth2/51.wav", true );
FileLoop *waveFile884= new FileLoop("plugins/Autodafe/samples/table14-fmsynth2/52.wav", true );
FileLoop *waveFile885= new FileLoop("plugins/Autodafe/samples/table14-fmsynth2/53.wav", true );
FileLoop *waveFile886= new FileLoop("plugins/Autodafe/samples/table14-fmsynth2/54.wav", true );
FileLoop *waveFile887= new FileLoop("plugins/Autodafe/samples/table14-fmsynth2/55.wav", true );
FileLoop *waveFile888= new FileLoop("plugins/Autodafe/samples/table14-fmsynth2/56.wav", true );
FileLoop *waveFile889= new FileLoop("plugins/Autodafe/samples/table14-fmsynth2/57.wav", true );
FileLoop *waveFile890= new FileLoop("plugins/Autodafe/samples/table14-fmsynth2/58.wav", true );
FileLoop *waveFile891= new FileLoop("plugins/Autodafe/samples/table14-fmsynth2/59.wav", true );
FileLoop *waveFile892= new FileLoop("plugins/Autodafe/samples/table14-fmsynth2/60.wav", true );
FileLoop *waveFile893= new FileLoop("plugins/Autodafe/samples/table14-fmsynth2/61.wav", true );
FileLoop *waveFile894= new FileLoop("plugins/Autodafe/samples/table14-fmsynth2/62.wav", true );
FileLoop *waveFile895= new FileLoop("plugins/Autodafe/samples/table14-fmsynth2/63.wav", true );






FileLoop *waveFile896= new FileLoop("plugins/Autodafe/samples/table15-linear/00.wav", true );
FileLoop *waveFile897= new FileLoop("plugins/Autodafe/samples/table15-linear/01.wav", true );
FileLoop *waveFile898= new FileLoop("plugins/Autodafe/samples/table15-linear/02.wav", true );
FileLoop *waveFile899= new FileLoop("plugins/Autodafe/samples/table15-linear/03.wav", true );
FileLoop *waveFile900= new FileLoop("plugins/Autodafe/samples/table15-linear/04.wav", true );
FileLoop *waveFile901= new FileLoop("plugins/Autodafe/samples/table15-linear/05.wav", true );
FileLoop *waveFile902= new FileLoop("plugins/Autodafe/samples/table15-linear/06.wav", true );
FileLoop *waveFile903= new FileLoop("plugins/Autodafe/samples/table15-linear/07.wav", true );
FileLoop *waveFile904= new FileLoop("plugins/Autodafe/samples/table15-linear/08.wav", true );
FileLoop *waveFile905= new FileLoop("plugins/Autodafe/samples/table15-linear/09.wav", true );
FileLoop *waveFile906= new FileLoop("plugins/Autodafe/samples/table15-linear/10.wav", true );
FileLoop *waveFile907= new FileLoop("plugins/Autodafe/samples/table15-linear/11.wav", true );
FileLoop *waveFile908= new FileLoop("plugins/Autodafe/samples/table15-linear/12.wav", true );
FileLoop *waveFile909= new FileLoop("plugins/Autodafe/samples/table15-linear/13.wav", true );
FileLoop *waveFile910= new FileLoop("plugins/Autodafe/samples/table15-linear/14.wav", true );
FileLoop *waveFile911= new FileLoop("plugins/Autodafe/samples/table15-linear/15.wav", true );
FileLoop *waveFile912= new FileLoop("plugins/Autodafe/samples/table15-linear/16.wav", true );
FileLoop *waveFile913= new FileLoop("plugins/Autodafe/samples/table15-linear/17.wav", true );
FileLoop *waveFile914= new FileLoop("plugins/Autodafe/samples/table15-linear/18.wav", true );
FileLoop *waveFile915= new FileLoop("plugins/Autodafe/samples/table15-linear/19.wav", true );
FileLoop *waveFile916= new FileLoop("plugins/Autodafe/samples/table15-linear/20.wav", true );
FileLoop *waveFile917= new FileLoop("plugins/Autodafe/samples/table15-linear/21.wav", true );
FileLoop *waveFile918= new FileLoop("plugins/Autodafe/samples/table15-linear/22.wav", true );
FileLoop *waveFile919= new FileLoop("plugins/Autodafe/samples/table15-linear/23.wav", true );
FileLoop *waveFile920= new FileLoop("plugins/Autodafe/samples/table15-linear/24.wav", true );
FileLoop *waveFile921= new FileLoop("plugins/Autodafe/samples/table15-linear/25.wav", true );
FileLoop *waveFile922= new FileLoop("plugins/Autodafe/samples/table15-linear/26.wav", true );
FileLoop *waveFile923= new FileLoop("plugins/Autodafe/samples/table15-linear/27.wav", true );
FileLoop *waveFile924= new FileLoop("plugins/Autodafe/samples/table15-linear/28.wav", true );
FileLoop *waveFile925= new FileLoop("plugins/Autodafe/samples/table15-linear/29.wav", true );
FileLoop *waveFile926= new FileLoop("plugins/Autodafe/samples/table15-linear/30.wav", true );
FileLoop *waveFile927= new FileLoop("plugins/Autodafe/samples/table15-linear/31.wav", true );
FileLoop *waveFile928= new FileLoop("plugins/Autodafe/samples/table15-linear/32.wav", true );
FileLoop *waveFile929= new FileLoop("plugins/Autodafe/samples/table15-linear/33.wav", true );
FileLoop *waveFile930= new FileLoop("plugins/Autodafe/samples/table15-linear/34.wav", true );
FileLoop *waveFile931= new FileLoop("plugins/Autodafe/samples/table15-linear/35.wav", true );
FileLoop *waveFile932= new FileLoop("plugins/Autodafe/samples/table15-linear/36.wav", true );
FileLoop *waveFile933= new FileLoop("plugins/Autodafe/samples/table15-linear/37.wav", true );
FileLoop *waveFile934= new FileLoop("plugins/Autodafe/samples/table15-linear/38.wav", true );
FileLoop *waveFile935= new FileLoop("plugins/Autodafe/samples/table15-linear/39.wav", true );
FileLoop *waveFile936= new FileLoop("plugins/Autodafe/samples/table15-linear/40.wav", true );
FileLoop *waveFile937= new FileLoop("plugins/Autodafe/samples/table15-linear/41.wav", true );
FileLoop *waveFile938= new FileLoop("plugins/Autodafe/samples/table15-linear/42.wav", true );
FileLoop *waveFile939= new FileLoop("plugins/Autodafe/samples/table15-linear/43.wav", true );
FileLoop *waveFile940= new FileLoop("plugins/Autodafe/samples/table15-linear/44.wav", true );
FileLoop *waveFile941= new FileLoop("plugins/Autodafe/samples/table15-linear/45.wav", true );
FileLoop *waveFile942= new FileLoop("plugins/Autodafe/samples/table15-linear/46.wav", true );
FileLoop *waveFile943= new FileLoop("plugins/Autodafe/samples/table15-linear/47.wav", true );
FileLoop *waveFile944= new FileLoop("plugins/Autodafe/samples/table15-linear/48.wav", true );
FileLoop *waveFile945= new FileLoop("plugins/Autodafe/samples/table15-linear/49.wav", true );
FileLoop *waveFile946= new FileLoop("plugins/Autodafe/samples/table15-linear/50.wav", true );
FileLoop *waveFile947= new FileLoop("plugins/Autodafe/samples/table15-linear/51.wav", true );
FileLoop *waveFile948= new FileLoop("plugins/Autodafe/samples/table15-linear/52.wav", true );
FileLoop *waveFile949= new FileLoop("plugins/Autodafe/samples/table15-linear/53.wav", true );
FileLoop *waveFile950= new FileLoop("plugins/Autodafe/samples/table15-linear/54.wav", true );
FileLoop *waveFile951= new FileLoop("plugins/Autodafe/samples/table15-linear/55.wav", true );
FileLoop *waveFile952= new FileLoop("plugins/Autodafe/samples/table15-linear/56.wav", true );
FileLoop *waveFile953= new FileLoop("plugins/Autodafe/samples/table15-linear/57.wav", true );
FileLoop *waveFile954= new FileLoop("plugins/Autodafe/samples/table15-linear/58.wav", true );
FileLoop *waveFile955= new FileLoop("plugins/Autodafe/samples/table15-linear/59.wav", true );
FileLoop *waveFile956= new FileLoop("plugins/Autodafe/samples/table15-linear/60.wav", true );
FileLoop *waveFile957= new FileLoop("plugins/Autodafe/samples/table15-linear/61.wav", true );
FileLoop *waveFile958= new FileLoop("plugins/Autodafe/samples/table15-linear/62.wav", true );
FileLoop *waveFile959= new FileLoop("plugins/Autodafe/samples/table15-linear/63.wav", true );








FileLoop *waveFile960= new FileLoop("plugins/Autodafe/samples/table16-oscchip/00.wav", true );
FileLoop *waveFile961= new FileLoop("plugins/Autodafe/samples/table16-oscchip/01.wav", true );
FileLoop *waveFile962= new FileLoop("plugins/Autodafe/samples/table16-oscchip/02.wav", true );
FileLoop *waveFile963= new FileLoop("plugins/Autodafe/samples/table16-oscchip/03.wav", true );
FileLoop *waveFile964= new FileLoop("plugins/Autodafe/samples/table16-oscchip/04.wav", true );
FileLoop *waveFile965= new FileLoop("plugins/Autodafe/samples/table16-oscchip/05.wav", true );
FileLoop *waveFile966= new FileLoop("plugins/Autodafe/samples/table16-oscchip/06.wav", true );
FileLoop *waveFile967= new FileLoop("plugins/Autodafe/samples/table16-oscchip/07.wav", true );
FileLoop *waveFile968= new FileLoop("plugins/Autodafe/samples/table16-oscchip/08.wav", true );
FileLoop *waveFile969= new FileLoop("plugins/Autodafe/samples/table16-oscchip/09.wav", true );
FileLoop *waveFile970= new FileLoop("plugins/Autodafe/samples/table16-oscchip/10.wav", true );
FileLoop *waveFile971= new FileLoop("plugins/Autodafe/samples/table16-oscchip/11.wav", true );
FileLoop *waveFile972= new FileLoop("plugins/Autodafe/samples/table16-oscchip/12.wav", true );
FileLoop *waveFile973= new FileLoop("plugins/Autodafe/samples/table16-oscchip/13.wav", true );
FileLoop *waveFile974= new FileLoop("plugins/Autodafe/samples/table16-oscchip/14.wav", true );
FileLoop *waveFile975= new FileLoop("plugins/Autodafe/samples/table16-oscchip/15.wav", true );
FileLoop *waveFile976= new FileLoop("plugins/Autodafe/samples/table16-oscchip/16.wav", true );
FileLoop *waveFile977= new FileLoop("plugins/Autodafe/samples/table16-oscchip/17.wav", true );
FileLoop *waveFile978= new FileLoop("plugins/Autodafe/samples/table16-oscchip/18.wav", true );
FileLoop *waveFile979= new FileLoop("plugins/Autodafe/samples/table16-oscchip/19.wav", true );
FileLoop *waveFile980= new FileLoop("plugins/Autodafe/samples/table16-oscchip/20.wav", true );
FileLoop *waveFile981= new FileLoop("plugins/Autodafe/samples/table16-oscchip/21.wav", true );
FileLoop *waveFile982= new FileLoop("plugins/Autodafe/samples/table16-oscchip/22.wav", true );
FileLoop *waveFile983= new FileLoop("plugins/Autodafe/samples/table16-oscchip/23.wav", true );
FileLoop *waveFile984= new FileLoop("plugins/Autodafe/samples/table16-oscchip/24.wav", true );
FileLoop *waveFile985= new FileLoop("plugins/Autodafe/samples/table16-oscchip/25.wav", true );
FileLoop *waveFile986= new FileLoop("plugins/Autodafe/samples/table16-oscchip/26.wav", true );
FileLoop *waveFile987= new FileLoop("plugins/Autodafe/samples/table16-oscchip/27.wav", true );
FileLoop *waveFile988= new FileLoop("plugins/Autodafe/samples/table16-oscchip/28.wav", true );
FileLoop *waveFile989= new FileLoop("plugins/Autodafe/samples/table16-oscchip/29.wav", true );
FileLoop *waveFile990= new FileLoop("plugins/Autodafe/samples/table16-oscchip/30.wav", true );
FileLoop *waveFile991= new FileLoop("plugins/Autodafe/samples/table16-oscchip/31.wav", true );
FileLoop *waveFile992= new FileLoop("plugins/Autodafe/samples/table16-oscchip/32.wav", true );
FileLoop *waveFile993= new FileLoop("plugins/Autodafe/samples/table16-oscchip/33.wav", true );
FileLoop *waveFile994= new FileLoop("plugins/Autodafe/samples/table16-oscchip/34.wav", true );
FileLoop *waveFile995= new FileLoop("plugins/Autodafe/samples/table16-oscchip/35.wav", true );
FileLoop *waveFile996= new FileLoop("plugins/Autodafe/samples/table16-oscchip/36.wav", true );
FileLoop *waveFile997= new FileLoop("plugins/Autodafe/samples/table16-oscchip/37.wav", true );
FileLoop *waveFile998= new FileLoop("plugins/Autodafe/samples/table16-oscchip/38.wav", true );
FileLoop *waveFile999= new FileLoop("plugins/Autodafe/samples/table16-oscchip/39.wav", true );
FileLoop *waveFile1000= new FileLoop("plugins/Autodafe/samples/table16-oscchip/40.wav", true );
FileLoop *waveFile1001= new FileLoop("plugins/Autodafe/samples/table16-oscchip/41.wav", true );
FileLoop *waveFile1002= new FileLoop("plugins/Autodafe/samples/table16-oscchip/42.wav", true );
FileLoop *waveFile1003= new FileLoop("plugins/Autodafe/samples/table16-oscchip/43.wav", true );
FileLoop *waveFile1004= new FileLoop("plugins/Autodafe/samples/table16-oscchip/44.wav", true );
FileLoop *waveFile1005= new FileLoop("plugins/Autodafe/samples/table16-oscchip/45.wav", true );
FileLoop *waveFile1006= new FileLoop("plugins/Autodafe/samples/table16-oscchip/46.wav", true );
FileLoop *waveFile1007= new FileLoop("plugins/Autodafe/samples/table16-oscchip/47.wav", true );
FileLoop *waveFile1008= new FileLoop("plugins/Autodafe/samples/table16-oscchip/48.wav", true );
FileLoop *waveFile1009= new FileLoop("plugins/Autodafe/samples/table16-oscchip/49.wav", true );
FileLoop *waveFile1010= new FileLoop("plugins/Autodafe/samples/table16-oscchip/50.wav", true );
FileLoop *waveFile1011= new FileLoop("plugins/Autodafe/samples/table16-oscchip/51.wav", true );
FileLoop *waveFile1012= new FileLoop("plugins/Autodafe/samples/table16-oscchip/52.wav", true );
FileLoop *waveFile1013= new FileLoop("plugins/Autodafe/samples/table16-oscchip/53.wav", true );
FileLoop *waveFile1014= new FileLoop("plugins/Autodafe/samples/table16-oscchip/54.wav", true );
FileLoop *waveFile1015= new FileLoop("plugins/Autodafe/samples/table16-oscchip/55.wav", true );
FileLoop *waveFile1016= new FileLoop("plugins/Autodafe/samples/table16-oscchip/56.wav", true );
FileLoop *waveFile1017= new FileLoop("plugins/Autodafe/samples/table16-oscchip/57.wav", true );
FileLoop *waveFile1018= new FileLoop("plugins/Autodafe/samples/table16-oscchip/58.wav", true );
FileLoop *waveFile1019= new FileLoop("plugins/Autodafe/samples/table16-oscchip/59.wav", true );
FileLoop *waveFile1020= new FileLoop("plugins/Autodafe/samples/table16-oscchip/60.wav", true );
FileLoop *waveFile1021= new FileLoop("plugins/Autodafe/samples/table16-oscchip/61.wav", true );
FileLoop *waveFile1022= new FileLoop("plugins/Autodafe/samples/table16-oscchip/62.wav", true );
FileLoop *waveFile1023= new FileLoop("plugins/Autodafe/samples/table16-oscchip/63.wav", true );







FileLoop *waveFile1024= new FileLoop("plugins/Autodafe/samples/table17-oscchip2/00.wav", true );
FileLoop *waveFile1025= new FileLoop("plugins/Autodafe/samples/table17-oscchip2/01.wav", true );
FileLoop *waveFile1026= new FileLoop("plugins/Autodafe/samples/table17-oscchip2/02.wav", true );
FileLoop *waveFile1027= new FileLoop("plugins/Autodafe/samples/table17-oscchip2/03.wav", true );
FileLoop *waveFile1028= new FileLoop("plugins/Autodafe/samples/table17-oscchip2/04.wav", true );
FileLoop *waveFile1029= new FileLoop("plugins/Autodafe/samples/table17-oscchip2/05.wav", true );
FileLoop *waveFile1030= new FileLoop("plugins/Autodafe/samples/table17-oscchip2/06.wav", true );
FileLoop *waveFile1031= new FileLoop("plugins/Autodafe/samples/table17-oscchip2/07.wav", true );
FileLoop *waveFile1032= new FileLoop("plugins/Autodafe/samples/table17-oscchip2/08.wav", true );
FileLoop *waveFile1033= new FileLoop("plugins/Autodafe/samples/table17-oscchip2/09.wav", true );
FileLoop *waveFile1034= new FileLoop("plugins/Autodafe/samples/table17-oscchip2/10.wav", true );
FileLoop *waveFile1035= new FileLoop("plugins/Autodafe/samples/table17-oscchip2/11.wav", true );
FileLoop *waveFile1036= new FileLoop("plugins/Autodafe/samples/table17-oscchip2/12.wav", true );
FileLoop *waveFile1037= new FileLoop("plugins/Autodafe/samples/table17-oscchip2/13.wav", true );
FileLoop *waveFile1038= new FileLoop("plugins/Autodafe/samples/table17-oscchip2/14.wav", true );
FileLoop *waveFile1039= new FileLoop("plugins/Autodafe/samples/table17-oscchip2/15.wav", true );
FileLoop *waveFile1040= new FileLoop("plugins/Autodafe/samples/table17-oscchip2/16.wav", true );
FileLoop *waveFile1041= new FileLoop("plugins/Autodafe/samples/table17-oscchip2/17.wav", true );
FileLoop *waveFile1042= new FileLoop("plugins/Autodafe/samples/table17-oscchip2/18.wav", true );
FileLoop *waveFile1043= new FileLoop("plugins/Autodafe/samples/table17-oscchip2/19.wav", true );
FileLoop *waveFile1044= new FileLoop("plugins/Autodafe/samples/table17-oscchip2/20.wav", true );
FileLoop *waveFile1045= new FileLoop("plugins/Autodafe/samples/table17-oscchip2/21.wav", true );
FileLoop *waveFile1046= new FileLoop("plugins/Autodafe/samples/table17-oscchip2/22.wav", true );
FileLoop *waveFile1047= new FileLoop("plugins/Autodafe/samples/table17-oscchip2/23.wav", true );
FileLoop *waveFile1048= new FileLoop("plugins/Autodafe/samples/table17-oscchip2/24.wav", true );
FileLoop *waveFile1049= new FileLoop("plugins/Autodafe/samples/table17-oscchip2/25.wav", true );
FileLoop *waveFile1050= new FileLoop("plugins/Autodafe/samples/table17-oscchip2/26.wav", true );
FileLoop *waveFile1051= new FileLoop("plugins/Autodafe/samples/table17-oscchip2/27.wav", true );
FileLoop *waveFile1052= new FileLoop("plugins/Autodafe/samples/table17-oscchip2/28.wav", true );
FileLoop *waveFile1053= new FileLoop("plugins/Autodafe/samples/table17-oscchip2/29.wav", true );
FileLoop *waveFile1054= new FileLoop("plugins/Autodafe/samples/table17-oscchip2/30.wav", true );
FileLoop *waveFile1055= new FileLoop("plugins/Autodafe/samples/table17-oscchip2/31.wav", true );
FileLoop *waveFile1056= new FileLoop("plugins/Autodafe/samples/table17-oscchip2/32.wav", true );
FileLoop *waveFile1057= new FileLoop("plugins/Autodafe/samples/table17-oscchip2/33.wav", true );
FileLoop *waveFile1058= new FileLoop("plugins/Autodafe/samples/table17-oscchip2/34.wav", true );
FileLoop *waveFile1059= new FileLoop("plugins/Autodafe/samples/table17-oscchip2/35.wav", true );
FileLoop *waveFile1060= new FileLoop("plugins/Autodafe/samples/table17-oscchip2/36.wav", true );
FileLoop *waveFile1061= new FileLoop("plugins/Autodafe/samples/table17-oscchip2/37.wav", true );
FileLoop *waveFile1062= new FileLoop("plugins/Autodafe/samples/table17-oscchip2/38.wav", true );
FileLoop *waveFile1063= new FileLoop("plugins/Autodafe/samples/table17-oscchip2/39.wav", true );
FileLoop *waveFile1064= new FileLoop("plugins/Autodafe/samples/table17-oscchip2/40.wav", true );
FileLoop *waveFile1065= new FileLoop("plugins/Autodafe/samples/table17-oscchip2/41.wav", true );
FileLoop *waveFile1066= new FileLoop("plugins/Autodafe/samples/table17-oscchip2/42.wav", true );
FileLoop *waveFile1067= new FileLoop("plugins/Autodafe/samples/table17-oscchip2/43.wav", true );
FileLoop *waveFile1068= new FileLoop("plugins/Autodafe/samples/table17-oscchip2/44.wav", true );
FileLoop *waveFile1069= new FileLoop("plugins/Autodafe/samples/table17-oscchip2/45.wav", true );
FileLoop *waveFile1070= new FileLoop("plugins/Autodafe/samples/table17-oscchip2/46.wav", true );
FileLoop *waveFile1071= new FileLoop("plugins/Autodafe/samples/table17-oscchip2/47.wav", true );
FileLoop *waveFile1072= new FileLoop("plugins/Autodafe/samples/table17-oscchip2/48.wav", true );
FileLoop *waveFile1073= new FileLoop("plugins/Autodafe/samples/table17-oscchip2/49.wav", true );
FileLoop *waveFile1074= new FileLoop("plugins/Autodafe/samples/table17-oscchip2/50.wav", true );
FileLoop *waveFile1075= new FileLoop("plugins/Autodafe/samples/table17-oscchip2/51.wav", true );
FileLoop *waveFile1076= new FileLoop("plugins/Autodafe/samples/table17-oscchip2/52.wav", true );
FileLoop *waveFile1077= new FileLoop("plugins/Autodafe/samples/table17-oscchip2/53.wav", true );
FileLoop *waveFile1078= new FileLoop("plugins/Autodafe/samples/table17-oscchip2/54.wav", true );
FileLoop *waveFile1079= new FileLoop("plugins/Autodafe/samples/table17-oscchip2/55.wav", true );
FileLoop *waveFile1080= new FileLoop("plugins/Autodafe/samples/table17-oscchip2/56.wav", true );
FileLoop *waveFile1081= new FileLoop("plugins/Autodafe/samples/table17-oscchip2/57.wav", true );
FileLoop *waveFile1082= new FileLoop("plugins/Autodafe/samples/table17-oscchip2/58.wav", true );
FileLoop *waveFile1083= new FileLoop("plugins/Autodafe/samples/table17-oscchip2/59.wav", true );
FileLoop *waveFile1084= new FileLoop("plugins/Autodafe/samples/table17-oscchip2/60.wav", true );
FileLoop *waveFile1085= new FileLoop("plugins/Autodafe/samples/table17-oscchip2/61.wav", true );
FileLoop *waveFile1086= new FileLoop("plugins/Autodafe/samples/table17-oscchip2/62.wav", true );
FileLoop *waveFile1087= new FileLoop("plugins/Autodafe/samples/table17-oscchip2/63.wav", true );


 
	void step();
};
    




WavesModel::WavesModel() {
	params.resize(NUM_PARAMS);
	inputs.resize(NUM_INPUTS);
	outputs.resize(NUM_OUTPUTS);




}










void WavesModel::step() {



 gSampleRate=engineGetSampleRate();




	float pitchFine = 3.0 * quadraticBipolar(params[PARAM_FINE].value);
	float pitchCv = 12.0 * inputs[INPUT_FREQ_CV].value * params[PARAM_FREQ_CV].value;

	
	StkFloat   freq = params[PARAM_FREQ].value+ pitchCv+pitchFine;
	freq = 261.626 * powf(2.0, freq / 12.0);

	if (gSampleRate!=oldSampleRate){waveSquare->setSampleRate(engineGetSampleRate());}


	




	

   
    
    if (bankUp.process(params[BANKUP].value))
    { 
         if (bank<banks) {
        bank++;
            
         }
        else
        {
            bank=banks;
        }
    }



       if (bankDwn.process(params[BANKDWN].value))
    { 
         if (bank>1) {
        bank--;
            
         }
        else
        {
            bank=1;
        }
    }

   


tableSelector=params[PARAM_TAB].value;
paramtableSelector=tableSelector;



	

if(paramtableSelector!=oldtableSelector)
	{inc=-tableincrement;tableincrement=0;} 
	
else  
	{inc=tableincrement;}



tableSelector=params[PARAM_TAB].value + inc +inputs[INPUT_TAB_CV].value;


 
   
    if (trigUp.process(params[TABUP].value))
    {
         if (tableSelector<63) {
        tableincrement+=1;
            
         }
        else
        {
            tableincrement=0;
        }
    }


if (trigDwn.process(params[TABDWN].value))
    {
         if (tableSelector>0) {
        tableincrement-=1;
            
         }
        else
        {
            tableincrement=0;
        }
    }










if(bank==1){


if((int)tableSelector==0) {waveFile0->setFrequency(freq);waveFile0->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile0->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==1) {waveFile1->setFrequency(freq);waveFile1->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile1->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==2) {waveFile2->setFrequency(freq);waveFile2->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile2->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==3) {waveFile3->setFrequency(freq);waveFile3->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile3->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==4) {waveFile4->setFrequency(freq);waveFile4->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile4->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==5) {waveFile5->setFrequency(freq);waveFile5->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile5->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==6) {waveFile6->setFrequency(freq);waveFile6->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile6->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==7) {waveFile7->setFrequency(freq);waveFile7->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile7->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==8) {waveFile8->setFrequency(freq);waveFile8->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile8->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==9) {waveFile9->setFrequency(freq);waveFile9->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile9->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==10) {waveFile10->setFrequency(freq);waveFile10->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile10->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==11) {waveFile11->setFrequency(freq);waveFile11->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile11->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==12) {waveFile12->setFrequency(freq);waveFile12->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile12->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==13) {waveFile13->setFrequency(freq);waveFile13->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile13->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==14) {waveFile14->setFrequency(freq);waveFile14->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile14->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==15) {waveFile15->setFrequency(freq);waveFile15->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile15->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==16) {waveFile16->setFrequency(freq);waveFile16->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile16->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==17) {waveFile17->setFrequency(freq);waveFile17->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile17->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==18) {waveFile18->setFrequency(freq);waveFile18->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile18->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==19) {waveFile19->setFrequency(freq);waveFile19->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile19->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==20) {waveFile20->setFrequency(freq);waveFile20->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile20->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==21) {waveFile21->setFrequency(freq);waveFile21->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile21->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==22) {waveFile22->setFrequency(freq);waveFile22->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile22->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==23) {waveFile23->setFrequency(freq);waveFile23->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile23->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==24) {waveFile24->setFrequency(freq);waveFile24->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile24->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==25) {waveFile25->setFrequency(freq);waveFile25->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile25->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==26) {waveFile26->setFrequency(freq);waveFile26->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile26->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==27) {waveFile27->setFrequency(freq);waveFile27->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile27->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==28) {waveFile28->setFrequency(freq);waveFile28->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile28->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==29) {waveFile29->setFrequency(freq);waveFile29->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile29->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==30) {waveFile30->setFrequency(freq);waveFile30->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile30->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==31) {waveFile31->setFrequency(freq);waveFile31->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile31->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==32) {waveFile32->setFrequency(freq);waveFile32->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile32->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==33) {waveFile33->setFrequency(freq);waveFile33->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile33->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==34) {waveFile34->setFrequency(freq);waveFile34->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile34->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==35) {waveFile35->setFrequency(freq);waveFile35->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile35->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==36) {waveFile36->setFrequency(freq);waveFile36->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile36->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==37) {waveFile37->setFrequency(freq);waveFile37->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile37->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==38) {waveFile38->setFrequency(freq);waveFile38->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile38->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==39) {waveFile39->setFrequency(freq);waveFile39->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile39->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==40) {waveFile40->setFrequency(freq);waveFile40->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile40->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==41) {waveFile41->setFrequency(freq);waveFile41->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile41->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==42) {waveFile42->setFrequency(freq);waveFile42->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile42->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==43) {waveFile43->setFrequency(freq);waveFile43->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile43->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==44) {waveFile44->setFrequency(freq);waveFile44->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile44->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==45) {waveFile45->setFrequency(freq);waveFile45->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile45->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==46) {waveFile46->setFrequency(freq);waveFile46->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile46->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==47) {waveFile47->setFrequency(freq);waveFile47->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile47->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==48) {waveFile48->setFrequency(freq);waveFile48->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile48->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==49) {waveFile49->setFrequency(freq);waveFile49->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile49->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==50) {waveFile50->setFrequency(freq);waveFile50->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile50->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==51) {waveFile51->setFrequency(freq);waveFile51->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile51->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==52) {waveFile52->setFrequency(freq);waveFile52->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile52->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==53) {waveFile53->setFrequency(freq);waveFile53->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile53->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==54) {waveFile54->setFrequency(freq);waveFile54->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile54->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==55) {waveFile55->setFrequency(freq);waveFile55->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile55->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==56) {waveFile56->setFrequency(freq);waveFile56->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile56->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==57) {waveFile57->setFrequency(freq);waveFile57->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile57->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==58) {waveFile58->setFrequency(freq);waveFile58->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile58->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==59) {waveFile59->setFrequency(freq);waveFile59->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile59->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==60) {waveFile60->setFrequency(freq);waveFile60->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile60->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==61) {waveFile61->setFrequency(freq);waveFile61->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile61->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==62) {waveFile62->setFrequency(freq);waveFile62->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile62->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==63) {waveFile63->setFrequency(freq);waveFile63->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile63->lastOut(), lastPlayed, 0.25);}



}





else if(bank==2){

if((int)tableSelector==0) {waveFile64->setFrequency(freq);waveFile64->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile64->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==1) {waveFile65->setFrequency(freq);waveFile65->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile65->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==2) {waveFile66->setFrequency(freq);waveFile66->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile66->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==3) {waveFile67->setFrequency(freq);waveFile67->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile67->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==4) {waveFile68->setFrequency(freq);waveFile68->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile68->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==5) {waveFile69->setFrequency(freq);waveFile69->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile69->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==6) {waveFile70->setFrequency(freq);waveFile70->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile70->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==7) {waveFile71->setFrequency(freq);waveFile71->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile71->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==8) {waveFile72->setFrequency(freq);waveFile72->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile72->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==9) {waveFile73->setFrequency(freq);waveFile73->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile73->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==10) {waveFile74->setFrequency(freq);waveFile74->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile74->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==11) {waveFile75->setFrequency(freq);waveFile75->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile75->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==12) {waveFile76->setFrequency(freq);waveFile76->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile76->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==13) {waveFile77->setFrequency(freq);waveFile77->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile77->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==14) {waveFile78->setFrequency(freq);waveFile78->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile78->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==15) {waveFile79->setFrequency(freq);waveFile79->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile79->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==16) {waveFile80->setFrequency(freq);waveFile80->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile80->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==17) {waveFile81->setFrequency(freq);waveFile81->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile81->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==18) {waveFile82->setFrequency(freq);waveFile82->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile82->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==19) {waveFile83->setFrequency(freq);waveFile83->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile83->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==20) {waveFile84->setFrequency(freq);waveFile84->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile84->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==21) {waveFile85->setFrequency(freq);waveFile85->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile85->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==22) {waveFile86->setFrequency(freq);waveFile86->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile86->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==23) {waveFile87->setFrequency(freq);waveFile87->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile87->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==24) {waveFile88->setFrequency(freq);waveFile88->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile88->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==25) {waveFile89->setFrequency(freq);waveFile89->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile89->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==26) {waveFile90->setFrequency(freq);waveFile90->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile90->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==27) {waveFile91->setFrequency(freq);waveFile91->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile91->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==28) {waveFile92->setFrequency(freq);waveFile92->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile92->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==29) {waveFile93->setFrequency(freq);waveFile93->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile93->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==30) {waveFile94->setFrequency(freq);waveFile94->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile94->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==31) {waveFile95->setFrequency(freq);waveFile95->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile95->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==32) {waveFile96->setFrequency(freq);waveFile96->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile96->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==33) {waveFile97->setFrequency(freq);waveFile97->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile97->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==34) {waveFile98->setFrequency(freq);waveFile98->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile98->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==35) {waveFile99->setFrequency(freq);waveFile99->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile99->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==36) {waveFile100->setFrequency(freq);waveFile100->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile100->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==37) {waveFile101->setFrequency(freq);waveFile101->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile101->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==38) {waveFile102->setFrequency(freq);waveFile102->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile102->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==39) {waveFile103->setFrequency(freq);waveFile103->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile103->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==40) {waveFile104->setFrequency(freq);waveFile104->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile104->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==41) {waveFile105->setFrequency(freq);waveFile105->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile105->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==42) {waveFile106->setFrequency(freq);waveFile106->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile106->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==43) {waveFile107->setFrequency(freq);waveFile107->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile107->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==44) {waveFile108->setFrequency(freq);waveFile108->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile108->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==45) {waveFile109->setFrequency(freq);waveFile109->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile109->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==46) {waveFile110->setFrequency(freq);waveFile110->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile110->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==47) {waveFile111->setFrequency(freq);waveFile111->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile111->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==48) {waveFile112->setFrequency(freq);waveFile112->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile112->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==49) {waveFile113->setFrequency(freq);waveFile113->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile113->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==50) {waveFile114->setFrequency(freq);waveFile114->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile114->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==51) {waveFile115->setFrequency(freq);waveFile115->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile115->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==52) {waveFile116->setFrequency(freq);waveFile116->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile116->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==53) {waveFile117->setFrequency(freq);waveFile117->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile117->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==54) {waveFile118->setFrequency(freq);waveFile118->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile118->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==55) {waveFile119->setFrequency(freq);waveFile119->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile119->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==56) {waveFile120->setFrequency(freq);waveFile120->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile120->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==57) {waveFile121->setFrequency(freq);waveFile121->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile121->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==58) {waveFile122->setFrequency(freq);waveFile122->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile122->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==59) {waveFile123->setFrequency(freq);waveFile123->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile123->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==60) {waveFile124->setFrequency(freq);waveFile124->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile124->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==61) {waveFile125->setFrequency(freq);waveFile125->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile125->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==62) {waveFile126->setFrequency(freq);waveFile126->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile126->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==63) {waveFile127->setFrequency(freq);waveFile127->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile127->lastOut(), lastPlayed, 0.25);}


}

 

else if(bank==3){

if((int)tableSelector==0) {waveFile128->setFrequency(freq);waveFile128->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile128->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==1) {waveFile129->setFrequency(freq);waveFile129->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile129->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==2) {waveFile130->setFrequency(freq);waveFile130->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile130->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==3) {waveFile131->setFrequency(freq);waveFile131->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile131->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==4) {waveFile132->setFrequency(freq);waveFile132->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile132->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==5) {waveFile133->setFrequency(freq);waveFile133->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile133->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==6) {waveFile134->setFrequency(freq);waveFile134->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile134->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==7) {waveFile135->setFrequency(freq);waveFile135->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile135->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==8) {waveFile136->setFrequency(freq);waveFile136->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile136->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==9) {waveFile137->setFrequency(freq);waveFile137->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile137->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==10) {waveFile138->setFrequency(freq);waveFile138->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile138->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==11) {waveFile139->setFrequency(freq);waveFile139->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile139->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==12) {waveFile140->setFrequency(freq);waveFile140->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile140->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==13) {waveFile141->setFrequency(freq);waveFile141->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile141->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==14) {waveFile142->setFrequency(freq);waveFile142->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile142->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==15) {waveFile143->setFrequency(freq);waveFile143->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile143->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==16) {waveFile144->setFrequency(freq);waveFile144->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile144->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==17) {waveFile145->setFrequency(freq);waveFile145->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile145->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==18) {waveFile146->setFrequency(freq);waveFile146->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile146->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==19) {waveFile147->setFrequency(freq);waveFile147->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile147->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==20) {waveFile148->setFrequency(freq);waveFile148->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile148->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==21) {waveFile149->setFrequency(freq);waveFile149->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile149->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==22) {waveFile150->setFrequency(freq);waveFile150->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile150->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==23) {waveFile151->setFrequency(freq);waveFile151->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile151->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==24) {waveFile152->setFrequency(freq);waveFile152->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile152->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==25) {waveFile153->setFrequency(freq);waveFile153->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile153->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==26) {waveFile154->setFrequency(freq);waveFile154->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile154->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==27) {waveFile155->setFrequency(freq);waveFile155->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile155->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==28) {waveFile156->setFrequency(freq);waveFile156->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile156->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==29) {waveFile157->setFrequency(freq);waveFile157->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile157->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==30) {waveFile158->setFrequency(freq);waveFile158->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile158->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==31) {waveFile159->setFrequency(freq);waveFile159->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile159->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==32) {waveFile160->setFrequency(freq);waveFile160->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile160->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==33) {waveFile161->setFrequency(freq);waveFile161->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile161->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==34) {waveFile162->setFrequency(freq);waveFile162->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile162->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==35) {waveFile163->setFrequency(freq);waveFile163->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile163->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==36) {waveFile164->setFrequency(freq);waveFile164->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile164->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==37) {waveFile165->setFrequency(freq);waveFile165->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile165->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==38) {waveFile166->setFrequency(freq);waveFile166->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile166->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==39) {waveFile167->setFrequency(freq);waveFile167->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile167->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==40) {waveFile168->setFrequency(freq);waveFile168->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile168->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==41) {waveFile169->setFrequency(freq);waveFile169->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile169->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==42) {waveFile170->setFrequency(freq);waveFile170->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile170->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==43) {waveFile171->setFrequency(freq);waveFile171->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile171->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==44) {waveFile172->setFrequency(freq);waveFile172->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile172->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==45) {waveFile173->setFrequency(freq);waveFile173->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile173->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==46) {waveFile174->setFrequency(freq);waveFile174->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile174->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==47) {waveFile175->setFrequency(freq);waveFile175->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile175->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==48) {waveFile176->setFrequency(freq);waveFile176->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile176->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==49) {waveFile177->setFrequency(freq);waveFile177->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile177->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==50) {waveFile178->setFrequency(freq);waveFile178->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile178->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==51) {waveFile179->setFrequency(freq);waveFile179->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile179->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==52) {waveFile180->setFrequency(freq);waveFile180->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile180->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==53) {waveFile181->setFrequency(freq);waveFile181->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile181->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==54) {waveFile182->setFrequency(freq);waveFile182->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile182->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==55) {waveFile183->setFrequency(freq);waveFile183->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile183->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==56) {waveFile184->setFrequency(freq);waveFile184->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile184->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==57) {waveFile185->setFrequency(freq);waveFile185->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile185->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==58) {waveFile186->setFrequency(freq);waveFile186->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile186->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==59) {waveFile187->setFrequency(freq);waveFile187->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile187->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==60) {waveFile188->setFrequency(freq);waveFile188->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile188->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==61) {waveFile189->setFrequency(freq);waveFile189->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile189->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==62) {waveFile190->setFrequency(freq);waveFile190->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile190->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==63) {waveFile191->setFrequency(freq);waveFile191->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile191->lastOut(), lastPlayed, 0.25);}


}





if(bank==4){



if((int)tableSelector==0) {waveFile192->setFrequency(freq);waveFile192->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile192->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==1) {waveFile193->setFrequency(freq);waveFile193->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile193->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==2) {waveFile194->setFrequency(freq);waveFile194->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile194->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==3) {waveFile195->setFrequency(freq);waveFile195->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile195->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==4) {waveFile196->setFrequency(freq);waveFile196->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile196->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==5) {waveFile197->setFrequency(freq);waveFile197->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile197->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==6) {waveFile198->setFrequency(freq);waveFile198->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile198->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==7) {waveFile199->setFrequency(freq);waveFile199->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile199->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==8) {waveFile200->setFrequency(freq);waveFile200->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile200->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==9) {waveFile201->setFrequency(freq);waveFile201->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile201->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==10) {waveFile202->setFrequency(freq);waveFile202->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile202->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==11) {waveFile203->setFrequency(freq);waveFile203->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile203->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==12) {waveFile204->setFrequency(freq);waveFile204->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile204->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==13) {waveFile205->setFrequency(freq);waveFile205->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile205->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==14) {waveFile206->setFrequency(freq);waveFile206->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile206->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==15) {waveFile207->setFrequency(freq);waveFile207->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile207->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==16) {waveFile208->setFrequency(freq);waveFile208->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile208->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==17) {waveFile209->setFrequency(freq);waveFile209->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile209->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==18) {waveFile210->setFrequency(freq);waveFile210->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile210->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==19) {waveFile211->setFrequency(freq);waveFile211->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile211->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==20) {waveFile212->setFrequency(freq);waveFile212->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile212->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==21) {waveFile213->setFrequency(freq);waveFile213->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile213->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==22) {waveFile214->setFrequency(freq);waveFile214->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile214->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==23) {waveFile215->setFrequency(freq);waveFile215->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile215->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==24) {waveFile216->setFrequency(freq);waveFile216->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile216->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==25) {waveFile217->setFrequency(freq);waveFile217->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile217->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==26) {waveFile218->setFrequency(freq);waveFile218->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile218->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==27) {waveFile219->setFrequency(freq);waveFile219->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile219->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==28) {waveFile220->setFrequency(freq);waveFile220->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile220->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==29) {waveFile221->setFrequency(freq);waveFile221->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile221->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==30) {waveFile222->setFrequency(freq);waveFile222->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile222->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==31) {waveFile223->setFrequency(freq);waveFile223->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile223->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==32) {waveFile224->setFrequency(freq);waveFile224->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile224->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==33) {waveFile225->setFrequency(freq);waveFile225->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile225->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==34) {waveFile226->setFrequency(freq);waveFile226->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile226->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==35) {waveFile227->setFrequency(freq);waveFile227->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile227->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==36) {waveFile228->setFrequency(freq);waveFile228->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile228->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==37) {waveFile229->setFrequency(freq);waveFile229->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile229->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==38) {waveFile230->setFrequency(freq);waveFile230->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile230->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==39) {waveFile231->setFrequency(freq);waveFile231->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile231->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==40) {waveFile232->setFrequency(freq);waveFile232->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile232->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==41) {waveFile233->setFrequency(freq);waveFile233->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile233->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==42) {waveFile234->setFrequency(freq);waveFile234->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile234->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==43) {waveFile235->setFrequency(freq);waveFile235->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile235->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==44) {waveFile236->setFrequency(freq);waveFile236->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile236->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==45) {waveFile237->setFrequency(freq);waveFile237->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile237->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==46) {waveFile238->setFrequency(freq);waveFile238->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile238->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==47) {waveFile239->setFrequency(freq);waveFile239->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile239->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==48) {waveFile240->setFrequency(freq);waveFile240->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile240->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==49) {waveFile241->setFrequency(freq);waveFile241->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile241->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==50) {waveFile242->setFrequency(freq);waveFile242->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile242->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==51) {waveFile243->setFrequency(freq);waveFile243->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile243->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==52) {waveFile244->setFrequency(freq);waveFile244->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile244->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==53) {waveFile245->setFrequency(freq);waveFile245->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile245->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==54) {waveFile246->setFrequency(freq);waveFile246->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile246->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==55) {waveFile247->setFrequency(freq);waveFile247->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile247->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==56) {waveFile248->setFrequency(freq);waveFile248->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile248->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==57) {waveFile249->setFrequency(freq);waveFile249->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile249->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==58) {waveFile250->setFrequency(freq);waveFile250->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile250->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==59) {waveFile251->setFrequency(freq);waveFile251->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile251->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==60) {waveFile252->setFrequency(freq);waveFile252->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile252->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==61) {waveFile253->setFrequency(freq);waveFile253->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile253->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==62) {waveFile254->setFrequency(freq);waveFile254->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile254->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==63) {waveFile255->setFrequency(freq);waveFile255->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile255->lastOut(), lastPlayed, 0.25);}


}




if(bank==5){

if((int)tableSelector==0) {waveFile256->setFrequency(freq);waveFile256->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile256->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==1) {waveFile257->setFrequency(freq);waveFile257->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile257->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==2) {waveFile258->setFrequency(freq);waveFile258->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile258->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==3) {waveFile259->setFrequency(freq);waveFile259->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile259->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==4) {waveFile260->setFrequency(freq);waveFile260->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile260->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==5) {waveFile261->setFrequency(freq);waveFile261->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile261->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==6) {waveFile262->setFrequency(freq);waveFile262->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile262->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==7) {waveFile263->setFrequency(freq);waveFile263->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile263->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==8) {waveFile264->setFrequency(freq);waveFile264->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile264->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==9) {waveFile265->setFrequency(freq);waveFile265->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile265->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==10) {waveFile266->setFrequency(freq);waveFile266->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile266->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==11) {waveFile267->setFrequency(freq);waveFile267->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile267->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==12) {waveFile268->setFrequency(freq);waveFile268->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile268->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==13) {waveFile269->setFrequency(freq);waveFile269->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile269->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==14) {waveFile270->setFrequency(freq);waveFile270->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile270->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==15) {waveFile271->setFrequency(freq);waveFile271->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile271->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==16) {waveFile272->setFrequency(freq);waveFile272->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile272->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==17) {waveFile273->setFrequency(freq);waveFile273->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile273->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==18) {waveFile274->setFrequency(freq);waveFile274->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile274->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==19) {waveFile275->setFrequency(freq);waveFile275->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile275->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==20) {waveFile276->setFrequency(freq);waveFile276->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile276->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==21) {waveFile277->setFrequency(freq);waveFile277->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile277->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==22) {waveFile278->setFrequency(freq);waveFile278->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile278->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==23) {waveFile279->setFrequency(freq);waveFile279->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile279->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==24) {waveFile280->setFrequency(freq);waveFile280->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile280->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==25) {waveFile281->setFrequency(freq);waveFile281->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile281->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==26) {waveFile282->setFrequency(freq);waveFile282->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile282->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==27) {waveFile283->setFrequency(freq);waveFile283->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile283->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==28) {waveFile284->setFrequency(freq);waveFile284->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile284->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==29) {waveFile285->setFrequency(freq);waveFile285->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile285->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==30) {waveFile286->setFrequency(freq);waveFile286->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile286->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==31) {waveFile287->setFrequency(freq);waveFile287->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile287->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==32) {waveFile288->setFrequency(freq);waveFile288->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile288->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==33) {waveFile289->setFrequency(freq);waveFile289->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile289->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==34) {waveFile290->setFrequency(freq);waveFile290->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile290->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==35) {waveFile291->setFrequency(freq);waveFile291->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile291->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==36) {waveFile292->setFrequency(freq);waveFile292->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile292->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==37) {waveFile293->setFrequency(freq);waveFile293->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile293->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==38) {waveFile294->setFrequency(freq);waveFile294->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile294->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==39) {waveFile295->setFrequency(freq);waveFile295->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile295->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==40) {waveFile296->setFrequency(freq);waveFile296->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile296->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==41) {waveFile297->setFrequency(freq);waveFile297->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile297->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==42) {waveFile298->setFrequency(freq);waveFile298->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile298->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==43) {waveFile299->setFrequency(freq);waveFile299->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile299->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==44) {waveFile300->setFrequency(freq);waveFile300->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile300->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==45) {waveFile301->setFrequency(freq);waveFile301->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile301->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==46) {waveFile302->setFrequency(freq);waveFile302->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile302->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==47) {waveFile303->setFrequency(freq);waveFile303->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile303->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==48) {waveFile304->setFrequency(freq);waveFile304->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile304->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==49) {waveFile305->setFrequency(freq);waveFile305->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile305->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==50) {waveFile306->setFrequency(freq);waveFile306->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile306->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==51) {waveFile307->setFrequency(freq);waveFile307->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile307->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==52) {waveFile308->setFrequency(freq);waveFile308->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile308->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==53) {waveFile309->setFrequency(freq);waveFile309->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile309->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==54) {waveFile310->setFrequency(freq);waveFile310->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile310->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==55) {waveFile311->setFrequency(freq);waveFile311->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile311->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==56) {waveFile312->setFrequency(freq);waveFile312->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile312->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==57) {waveFile313->setFrequency(freq);waveFile313->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile313->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==58) {waveFile314->setFrequency(freq);waveFile314->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile314->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==59) {waveFile315->setFrequency(freq);waveFile315->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile315->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==60) {waveFile316->setFrequency(freq);waveFile316->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile316->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==61) {waveFile317->setFrequency(freq);waveFile317->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile317->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==62) {waveFile318->setFrequency(freq);waveFile318->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile318->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==63) {waveFile319->setFrequency(freq);waveFile319->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile319->lastOut(), lastPlayed, 0.25);}

}








if(bank==6){


if((int)tableSelector==0) {waveFile320->setFrequency(freq);waveFile320->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile320->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==1) {waveFile321->setFrequency(freq);waveFile321->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile321->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==2) {waveFile322->setFrequency(freq);waveFile322->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile322->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==3) {waveFile323->setFrequency(freq);waveFile323->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile323->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==4) {waveFile324->setFrequency(freq);waveFile324->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile324->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==5) {waveFile325->setFrequency(freq);waveFile325->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile325->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==6) {waveFile326->setFrequency(freq);waveFile326->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile326->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==7) {waveFile327->setFrequency(freq);waveFile327->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile327->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==8) {waveFile328->setFrequency(freq);waveFile328->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile328->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==9) {waveFile329->setFrequency(freq);waveFile329->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile329->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==10) {waveFile330->setFrequency(freq);waveFile330->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile330->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==11) {waveFile331->setFrequency(freq);waveFile331->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile331->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==12) {waveFile332->setFrequency(freq);waveFile332->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile332->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==13) {waveFile333->setFrequency(freq);waveFile333->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile333->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==14) {waveFile334->setFrequency(freq);waveFile334->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile334->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==15) {waveFile335->setFrequency(freq);waveFile335->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile335->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==16) {waveFile336->setFrequency(freq);waveFile336->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile336->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==17) {waveFile337->setFrequency(freq);waveFile337->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile337->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==18) {waveFile338->setFrequency(freq);waveFile338->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile338->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==19) {waveFile339->setFrequency(freq);waveFile339->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile339->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==20) {waveFile340->setFrequency(freq);waveFile340->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile340->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==21) {waveFile341->setFrequency(freq);waveFile341->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile341->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==22) {waveFile342->setFrequency(freq);waveFile342->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile342->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==23) {waveFile343->setFrequency(freq);waveFile343->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile343->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==24) {waveFile344->setFrequency(freq);waveFile344->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile344->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==25) {waveFile345->setFrequency(freq);waveFile345->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile345->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==26) {waveFile346->setFrequency(freq);waveFile346->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile346->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==27) {waveFile347->setFrequency(freq);waveFile347->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile347->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==28) {waveFile348->setFrequency(freq);waveFile348->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile348->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==29) {waveFile349->setFrequency(freq);waveFile349->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile349->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==30) {waveFile350->setFrequency(freq);waveFile350->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile350->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==31) {waveFile351->setFrequency(freq);waveFile351->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile351->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==32) {waveFile352->setFrequency(freq);waveFile352->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile352->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==33) {waveFile353->setFrequency(freq);waveFile353->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile353->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==34) {waveFile354->setFrequency(freq);waveFile354->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile354->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==35) {waveFile355->setFrequency(freq);waveFile355->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile355->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==36) {waveFile356->setFrequency(freq);waveFile356->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile356->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==37) {waveFile357->setFrequency(freq);waveFile357->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile357->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==38) {waveFile358->setFrequency(freq);waveFile358->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile358->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==39) {waveFile359->setFrequency(freq);waveFile359->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile359->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==40) {waveFile360->setFrequency(freq);waveFile360->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile360->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==41) {waveFile361->setFrequency(freq);waveFile361->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile361->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==42) {waveFile362->setFrequency(freq);waveFile362->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile362->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==43) {waveFile363->setFrequency(freq);waveFile363->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile363->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==44) {waveFile364->setFrequency(freq);waveFile364->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile364->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==45) {waveFile365->setFrequency(freq);waveFile365->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile365->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==46) {waveFile366->setFrequency(freq);waveFile366->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile366->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==47) {waveFile367->setFrequency(freq);waveFile367->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile367->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==48) {waveFile368->setFrequency(freq);waveFile368->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile368->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==49) {waveFile369->setFrequency(freq);waveFile369->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile369->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==50) {waveFile370->setFrequency(freq);waveFile370->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile370->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==51) {waveFile371->setFrequency(freq);waveFile371->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile371->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==52) {waveFile372->setFrequency(freq);waveFile372->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile372->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==53) {waveFile373->setFrequency(freq);waveFile373->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile373->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==54) {waveFile374->setFrequency(freq);waveFile374->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile374->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==55) {waveFile375->setFrequency(freq);waveFile375->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile375->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==56) {waveFile376->setFrequency(freq);waveFile376->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile376->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==57) {waveFile377->setFrequency(freq);waveFile377->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile377->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==58) {waveFile378->setFrequency(freq);waveFile378->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile378->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==59) {waveFile379->setFrequency(freq);waveFile379->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile379->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==60) {waveFile380->setFrequency(freq);waveFile380->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile380->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==61) {waveFile381->setFrequency(freq);waveFile381->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile381->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==62) {waveFile382->setFrequency(freq);waveFile382->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile382->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==63) {waveFile383->setFrequency(freq);waveFile383->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile383->lastOut(), lastPlayed, 0.25);}


}




if(bank==7)

{
if((int)tableSelector==0) {waveFile384->setFrequency(freq);waveFile384->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile384->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==1) {waveFile385->setFrequency(freq);waveFile385->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile385->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==2) {waveFile386->setFrequency(freq);waveFile386->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile386->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==3) {waveFile387->setFrequency(freq);waveFile387->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile387->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==4) {waveFile388->setFrequency(freq);waveFile388->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile388->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==5) {waveFile389->setFrequency(freq);waveFile389->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile389->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==6) {waveFile390->setFrequency(freq);waveFile390->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile390->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==7) {waveFile391->setFrequency(freq);waveFile391->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile391->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==8) {waveFile392->setFrequency(freq);waveFile392->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile392->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==9) {waveFile393->setFrequency(freq);waveFile393->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile393->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==10) {waveFile394->setFrequency(freq);waveFile394->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile394->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==11) {waveFile395->setFrequency(freq);waveFile395->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile395->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==12) {waveFile396->setFrequency(freq);waveFile396->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile396->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==13) {waveFile397->setFrequency(freq);waveFile397->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile397->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==14) {waveFile398->setFrequency(freq);waveFile398->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile398->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==15) {waveFile399->setFrequency(freq);waveFile399->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile399->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==16) {waveFile400->setFrequency(freq);waveFile400->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile400->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==17) {waveFile401->setFrequency(freq);waveFile401->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile401->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==18) {waveFile402->setFrequency(freq);waveFile402->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile402->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==19) {waveFile403->setFrequency(freq);waveFile403->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile403->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==20) {waveFile404->setFrequency(freq);waveFile404->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile404->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==21) {waveFile405->setFrequency(freq);waveFile405->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile405->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==22) {waveFile406->setFrequency(freq);waveFile406->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile406->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==23) {waveFile407->setFrequency(freq);waveFile407->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile407->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==24) {waveFile408->setFrequency(freq);waveFile408->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile408->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==25) {waveFile409->setFrequency(freq);waveFile409->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile409->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==26) {waveFile410->setFrequency(freq);waveFile410->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile410->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==27) {waveFile411->setFrequency(freq);waveFile411->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile411->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==28) {waveFile412->setFrequency(freq);waveFile412->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile412->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==29) {waveFile413->setFrequency(freq);waveFile413->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile413->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==30) {waveFile414->setFrequency(freq);waveFile414->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile414->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==31) {waveFile415->setFrequency(freq);waveFile415->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile415->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==32) {waveFile416->setFrequency(freq);waveFile416->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile416->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==33) {waveFile417->setFrequency(freq);waveFile417->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile417->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==34) {waveFile418->setFrequency(freq);waveFile418->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile418->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==35) {waveFile419->setFrequency(freq);waveFile419->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile419->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==36) {waveFile420->setFrequency(freq);waveFile420->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile420->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==37) {waveFile421->setFrequency(freq);waveFile421->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile421->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==38) {waveFile422->setFrequency(freq);waveFile422->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile422->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==39) {waveFile423->setFrequency(freq);waveFile423->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile423->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==40) {waveFile424->setFrequency(freq);waveFile424->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile424->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==41) {waveFile425->setFrequency(freq);waveFile425->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile425->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==42) {waveFile426->setFrequency(freq);waveFile426->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile426->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==43) {waveFile427->setFrequency(freq);waveFile427->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile427->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==44) {waveFile428->setFrequency(freq);waveFile428->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile428->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==45) {waveFile429->setFrequency(freq);waveFile429->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile429->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==46) {waveFile430->setFrequency(freq);waveFile430->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile430->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==47) {waveFile431->setFrequency(freq);waveFile431->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile431->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==48) {waveFile432->setFrequency(freq);waveFile432->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile432->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==49) {waveFile433->setFrequency(freq);waveFile433->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile433->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==50) {waveFile434->setFrequency(freq);waveFile434->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile434->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==51) {waveFile435->setFrequency(freq);waveFile435->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile435->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==52) {waveFile436->setFrequency(freq);waveFile436->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile436->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==53) {waveFile437->setFrequency(freq);waveFile437->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile437->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==54) {waveFile438->setFrequency(freq);waveFile438->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile438->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==55) {waveFile439->setFrequency(freq);waveFile439->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile439->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==56) {waveFile440->setFrequency(freq);waveFile440->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile440->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==57) {waveFile441->setFrequency(freq);waveFile441->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile441->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==58) {waveFile442->setFrequency(freq);waveFile442->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile442->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==59) {waveFile443->setFrequency(freq);waveFile443->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile443->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==60) {waveFile444->setFrequency(freq);waveFile444->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile444->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==61) {waveFile445->setFrequency(freq);waveFile445->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile445->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==62) {waveFile446->setFrequency(freq);waveFile446->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile446->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==63) {waveFile447->setFrequency(freq);waveFile447->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile447->lastOut(), lastPlayed, 0.25);}

}



if (bank==8)

{

if((int)tableSelector==0) {waveFile448->setFrequency(freq);waveFile448->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile448->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==1) {waveFile449->setFrequency(freq);waveFile449->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile449->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==2) {waveFile450->setFrequency(freq);waveFile450->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile450->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==3) {waveFile451->setFrequency(freq);waveFile451->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile451->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==4) {waveFile452->setFrequency(freq);waveFile452->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile452->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==5) {waveFile453->setFrequency(freq);waveFile453->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile453->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==6) {waveFile454->setFrequency(freq);waveFile454->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile454->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==7) {waveFile455->setFrequency(freq);waveFile455->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile455->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==8) {waveFile456->setFrequency(freq);waveFile456->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile456->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==9) {waveFile457->setFrequency(freq);waveFile457->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile457->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==10) {waveFile458->setFrequency(freq);waveFile458->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile458->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==11) {waveFile459->setFrequency(freq);waveFile459->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile459->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==12) {waveFile460->setFrequency(freq);waveFile460->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile460->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==13) {waveFile461->setFrequency(freq);waveFile461->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile461->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==14) {waveFile462->setFrequency(freq);waveFile462->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile462->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==15) {waveFile463->setFrequency(freq);waveFile463->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile463->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==16) {waveFile464->setFrequency(freq);waveFile464->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile464->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==17) {waveFile465->setFrequency(freq);waveFile465->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile465->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==18) {waveFile466->setFrequency(freq);waveFile466->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile466->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==19) {waveFile467->setFrequency(freq);waveFile467->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile467->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==20) {waveFile468->setFrequency(freq);waveFile468->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile468->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==21) {waveFile469->setFrequency(freq);waveFile469->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile469->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==22) {waveFile470->setFrequency(freq);waveFile470->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile470->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==23) {waveFile471->setFrequency(freq);waveFile471->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile471->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==24) {waveFile472->setFrequency(freq);waveFile472->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile472->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==25) {waveFile473->setFrequency(freq);waveFile473->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile473->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==26) {waveFile474->setFrequency(freq);waveFile474->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile474->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==27) {waveFile475->setFrequency(freq);waveFile475->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile475->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==28) {waveFile476->setFrequency(freq);waveFile476->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile476->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==29) {waveFile477->setFrequency(freq);waveFile477->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile477->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==30) {waveFile478->setFrequency(freq);waveFile478->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile478->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==31) {waveFile479->setFrequency(freq);waveFile479->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile479->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==32) {waveFile480->setFrequency(freq);waveFile480->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile480->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==33) {waveFile481->setFrequency(freq);waveFile481->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile481->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==34) {waveFile482->setFrequency(freq);waveFile482->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile482->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==35) {waveFile483->setFrequency(freq);waveFile483->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile483->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==36) {waveFile484->setFrequency(freq);waveFile484->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile484->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==37) {waveFile485->setFrequency(freq);waveFile485->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile485->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==38) {waveFile486->setFrequency(freq);waveFile486->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile486->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==39) {waveFile487->setFrequency(freq);waveFile487->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile487->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==40) {waveFile488->setFrequency(freq);waveFile488->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile488->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==41) {waveFile489->setFrequency(freq);waveFile489->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile489->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==42) {waveFile490->setFrequency(freq);waveFile490->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile490->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==43) {waveFile491->setFrequency(freq);waveFile491->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile491->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==44) {waveFile492->setFrequency(freq);waveFile492->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile492->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==45) {waveFile493->setFrequency(freq);waveFile493->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile493->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==46) {waveFile494->setFrequency(freq);waveFile494->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile494->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==47) {waveFile495->setFrequency(freq);waveFile495->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile495->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==48) {waveFile496->setFrequency(freq);waveFile496->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile496->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==49) {waveFile497->setFrequency(freq);waveFile497->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile497->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==50) {waveFile498->setFrequency(freq);waveFile498->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile498->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==51) {waveFile499->setFrequency(freq);waveFile499->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile499->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==52) {waveFile500->setFrequency(freq);waveFile500->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile500->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==53) {waveFile501->setFrequency(freq);waveFile501->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile501->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==54) {waveFile502->setFrequency(freq);waveFile502->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile502->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==55) {waveFile503->setFrequency(freq);waveFile503->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile503->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==56) {waveFile504->setFrequency(freq);waveFile504->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile504->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==57) {waveFile505->setFrequency(freq);waveFile505->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile505->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==58) {waveFile506->setFrequency(freq);waveFile506->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile506->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==59) {waveFile507->setFrequency(freq);waveFile507->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile507->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==60) {waveFile508->setFrequency(freq);waveFile508->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile508->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==61) {waveFile509->setFrequency(freq);waveFile509->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile509->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==62) {waveFile510->setFrequency(freq);waveFile510->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile510->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==63) {waveFile511->setFrequency(freq);waveFile511->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile511->lastOut(), lastPlayed, 0.25);}

}




if (bank==9)


{


if((int)tableSelector==0) {waveFile512->setFrequency(freq);waveFile512->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile512->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==1) {waveFile513->setFrequency(freq);waveFile513->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile513->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==2) {waveFile514->setFrequency(freq);waveFile514->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile514->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==3) {waveFile515->setFrequency(freq);waveFile515->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile515->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==4) {waveFile516->setFrequency(freq);waveFile516->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile516->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==5) {waveFile517->setFrequency(freq);waveFile517->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile517->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==6) {waveFile518->setFrequency(freq);waveFile518->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile518->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==7) {waveFile519->setFrequency(freq);waveFile519->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile519->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==8) {waveFile520->setFrequency(freq);waveFile520->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile520->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==9) {waveFile521->setFrequency(freq);waveFile521->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile521->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==10) {waveFile522->setFrequency(freq);waveFile522->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile522->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==11) {waveFile523->setFrequency(freq);waveFile523->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile523->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==12) {waveFile524->setFrequency(freq);waveFile524->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile524->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==13) {waveFile525->setFrequency(freq);waveFile525->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile525->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==14) {waveFile526->setFrequency(freq);waveFile526->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile526->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==15) {waveFile527->setFrequency(freq);waveFile527->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile527->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==16) {waveFile528->setFrequency(freq);waveFile528->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile528->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==17) {waveFile529->setFrequency(freq);waveFile529->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile529->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==18) {waveFile530->setFrequency(freq);waveFile530->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile530->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==19) {waveFile531->setFrequency(freq);waveFile531->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile531->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==20) {waveFile532->setFrequency(freq);waveFile532->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile532->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==21) {waveFile533->setFrequency(freq);waveFile533->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile533->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==22) {waveFile534->setFrequency(freq);waveFile534->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile534->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==23) {waveFile535->setFrequency(freq);waveFile535->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile535->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==24) {waveFile536->setFrequency(freq);waveFile536->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile536->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==25) {waveFile537->setFrequency(freq);waveFile537->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile537->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==26) {waveFile538->setFrequency(freq);waveFile538->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile538->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==27) {waveFile539->setFrequency(freq);waveFile539->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile539->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==28) {waveFile540->setFrequency(freq);waveFile540->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile540->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==29) {waveFile541->setFrequency(freq);waveFile541->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile541->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==30) {waveFile542->setFrequency(freq);waveFile542->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile542->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==31) {waveFile543->setFrequency(freq);waveFile543->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile543->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==32) {waveFile544->setFrequency(freq);waveFile544->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile544->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==33) {waveFile545->setFrequency(freq);waveFile545->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile545->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==34) {waveFile546->setFrequency(freq);waveFile546->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile546->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==35) {waveFile547->setFrequency(freq);waveFile547->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile547->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==36) {waveFile548->setFrequency(freq);waveFile548->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile548->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==37) {waveFile549->setFrequency(freq);waveFile549->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile549->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==38) {waveFile550->setFrequency(freq);waveFile550->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile550->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==39) {waveFile551->setFrequency(freq);waveFile551->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile551->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==40) {waveFile552->setFrequency(freq);waveFile552->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile552->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==41) {waveFile553->setFrequency(freq);waveFile553->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile553->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==42) {waveFile554->setFrequency(freq);waveFile554->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile554->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==43) {waveFile555->setFrequency(freq);waveFile555->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile555->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==44) {waveFile556->setFrequency(freq);waveFile556->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile556->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==45) {waveFile557->setFrequency(freq);waveFile557->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile557->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==46) {waveFile558->setFrequency(freq);waveFile558->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile558->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==47) {waveFile559->setFrequency(freq);waveFile559->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile559->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==48) {waveFile560->setFrequency(freq);waveFile560->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile560->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==49) {waveFile561->setFrequency(freq);waveFile561->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile561->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==50) {waveFile562->setFrequency(freq);waveFile562->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile562->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==51) {waveFile563->setFrequency(freq);waveFile563->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile563->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==52) {waveFile564->setFrequency(freq);waveFile564->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile564->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==53) {waveFile565->setFrequency(freq);waveFile565->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile565->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==54) {waveFile566->setFrequency(freq);waveFile566->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile566->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==55) {waveFile567->setFrequency(freq);waveFile567->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile567->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==56) {waveFile568->setFrequency(freq);waveFile568->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile568->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==57) {waveFile569->setFrequency(freq);waveFile569->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile569->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==58) {waveFile570->setFrequency(freq);waveFile570->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile570->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==59) {waveFile571->setFrequency(freq);waveFile571->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile571->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==60) {waveFile572->setFrequency(freq);waveFile572->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile572->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==61) {waveFile573->setFrequency(freq);waveFile573->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile573->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==62) {waveFile574->setFrequency(freq);waveFile574->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile574->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==63) {waveFile575->setFrequency(freq);waveFile575->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile575->lastOut(), lastPlayed, 0.25);}

}




if(bank==10)

{


if((int)tableSelector==0) {waveFile576->setFrequency(freq);waveFile576->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile576->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==1) {waveFile577->setFrequency(freq);waveFile577->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile577->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==2) {waveFile578->setFrequency(freq);waveFile578->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile578->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==3) {waveFile579->setFrequency(freq);waveFile579->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile579->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==4) {waveFile580->setFrequency(freq);waveFile580->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile580->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==5) {waveFile581->setFrequency(freq);waveFile581->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile581->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==6) {waveFile582->setFrequency(freq);waveFile582->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile582->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==7) {waveFile583->setFrequency(freq);waveFile583->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile583->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==8) {waveFile584->setFrequency(freq);waveFile584->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile584->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==9) {waveFile585->setFrequency(freq);waveFile585->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile585->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==10) {waveFile586->setFrequency(freq);waveFile586->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile586->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==11) {waveFile587->setFrequency(freq);waveFile587->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile587->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==12) {waveFile588->setFrequency(freq);waveFile588->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile588->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==13) {waveFile589->setFrequency(freq);waveFile589->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile589->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==14) {waveFile590->setFrequency(freq);waveFile590->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile590->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==15) {waveFile591->setFrequency(freq);waveFile591->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile591->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==16) {waveFile592->setFrequency(freq);waveFile592->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile592->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==17) {waveFile593->setFrequency(freq);waveFile593->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile593->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==18) {waveFile594->setFrequency(freq);waveFile594->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile594->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==19) {waveFile595->setFrequency(freq);waveFile595->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile595->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==20) {waveFile596->setFrequency(freq);waveFile596->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile596->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==21) {waveFile597->setFrequency(freq);waveFile597->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile597->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==22) {waveFile598->setFrequency(freq);waveFile598->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile598->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==23) {waveFile599->setFrequency(freq);waveFile599->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile599->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==24) {waveFile600->setFrequency(freq);waveFile600->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile600->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==25) {waveFile601->setFrequency(freq);waveFile601->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile601->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==26) {waveFile602->setFrequency(freq);waveFile602->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile602->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==27) {waveFile603->setFrequency(freq);waveFile603->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile603->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==28) {waveFile604->setFrequency(freq);waveFile604->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile604->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==29) {waveFile605->setFrequency(freq);waveFile605->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile605->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==30) {waveFile606->setFrequency(freq);waveFile606->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile606->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==31) {waveFile607->setFrequency(freq);waveFile607->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile607->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==32) {waveFile608->setFrequency(freq);waveFile608->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile608->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==33) {waveFile609->setFrequency(freq);waveFile609->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile609->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==34) {waveFile610->setFrequency(freq);waveFile610->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile610->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==35) {waveFile611->setFrequency(freq);waveFile611->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile611->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==36) {waveFile612->setFrequency(freq);waveFile612->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile612->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==37) {waveFile613->setFrequency(freq);waveFile613->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile613->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==38) {waveFile614->setFrequency(freq);waveFile614->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile614->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==39) {waveFile615->setFrequency(freq);waveFile615->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile615->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==40) {waveFile616->setFrequency(freq);waveFile616->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile616->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==41) {waveFile617->setFrequency(freq);waveFile617->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile617->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==42) {waveFile618->setFrequency(freq);waveFile618->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile618->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==43) {waveFile619->setFrequency(freq);waveFile619->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile619->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==44) {waveFile620->setFrequency(freq);waveFile620->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile620->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==45) {waveFile621->setFrequency(freq);waveFile621->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile621->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==46) {waveFile622->setFrequency(freq);waveFile622->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile622->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==47) {waveFile623->setFrequency(freq);waveFile623->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile623->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==48) {waveFile624->setFrequency(freq);waveFile624->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile624->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==49) {waveFile625->setFrequency(freq);waveFile625->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile625->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==50) {waveFile626->setFrequency(freq);waveFile626->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile626->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==51) {waveFile627->setFrequency(freq);waveFile627->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile627->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==52) {waveFile628->setFrequency(freq);waveFile628->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile628->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==53) {waveFile629->setFrequency(freq);waveFile629->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile629->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==54) {waveFile630->setFrequency(freq);waveFile630->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile630->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==55) {waveFile631->setFrequency(freq);waveFile631->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile631->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==56) {waveFile632->setFrequency(freq);waveFile632->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile632->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==57) {waveFile633->setFrequency(freq);waveFile633->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile633->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==58) {waveFile634->setFrequency(freq);waveFile634->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile634->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==59) {waveFile635->setFrequency(freq);waveFile635->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile635->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==60) {waveFile636->setFrequency(freq);waveFile636->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile636->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==61) {waveFile637->setFrequency(freq);waveFile637->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile637->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==62) {waveFile638->setFrequency(freq);waveFile638->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile638->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==63) {waveFile639->setFrequency(freq);waveFile639->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile639->lastOut(), lastPlayed, 0.25);}


}



if (bank==11)

{

if((int)tableSelector==0) {waveFile640->setFrequency(freq);waveFile640->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile640->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==1) {waveFile641->setFrequency(freq);waveFile641->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile641->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==2) {waveFile642->setFrequency(freq);waveFile642->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile642->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==3) {waveFile643->setFrequency(freq);waveFile643->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile643->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==4) {waveFile644->setFrequency(freq);waveFile644->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile644->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==5) {waveFile645->setFrequency(freq);waveFile645->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile645->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==6) {waveFile646->setFrequency(freq);waveFile646->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile646->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==7) {waveFile647->setFrequency(freq);waveFile647->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile647->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==8) {waveFile648->setFrequency(freq);waveFile648->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile648->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==9) {waveFile649->setFrequency(freq);waveFile649->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile649->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==10) {waveFile650->setFrequency(freq);waveFile650->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile650->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==11) {waveFile651->setFrequency(freq);waveFile651->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile651->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==12) {waveFile652->setFrequency(freq);waveFile652->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile652->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==13) {waveFile653->setFrequency(freq);waveFile653->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile653->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==14) {waveFile654->setFrequency(freq);waveFile654->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile654->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==15) {waveFile655->setFrequency(freq);waveFile655->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile655->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==16) {waveFile656->setFrequency(freq);waveFile656->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile656->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==17) {waveFile657->setFrequency(freq);waveFile657->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile657->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==18) {waveFile658->setFrequency(freq);waveFile658->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile658->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==19) {waveFile659->setFrequency(freq);waveFile659->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile659->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==20) {waveFile660->setFrequency(freq);waveFile660->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile660->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==21) {waveFile661->setFrequency(freq);waveFile661->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile661->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==22) {waveFile662->setFrequency(freq);waveFile662->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile662->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==23) {waveFile663->setFrequency(freq);waveFile663->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile663->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==24) {waveFile664->setFrequency(freq);waveFile664->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile664->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==25) {waveFile665->setFrequency(freq);waveFile665->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile665->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==26) {waveFile666->setFrequency(freq);waveFile666->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile666->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==27) {waveFile667->setFrequency(freq);waveFile667->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile667->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==28) {waveFile668->setFrequency(freq);waveFile668->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile668->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==29) {waveFile669->setFrequency(freq);waveFile669->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile669->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==30) {waveFile670->setFrequency(freq);waveFile670->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile670->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==31) {waveFile671->setFrequency(freq);waveFile671->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile671->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==32) {waveFile672->setFrequency(freq);waveFile672->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile672->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==33) {waveFile673->setFrequency(freq);waveFile673->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile673->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==34) {waveFile674->setFrequency(freq);waveFile674->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile674->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==35) {waveFile675->setFrequency(freq);waveFile675->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile675->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==36) {waveFile676->setFrequency(freq);waveFile676->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile676->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==37) {waveFile677->setFrequency(freq);waveFile677->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile677->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==38) {waveFile678->setFrequency(freq);waveFile678->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile678->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==39) {waveFile679->setFrequency(freq);waveFile679->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile679->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==40) {waveFile680->setFrequency(freq);waveFile680->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile680->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==41) {waveFile681->setFrequency(freq);waveFile681->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile681->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==42) {waveFile682->setFrequency(freq);waveFile682->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile682->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==43) {waveFile683->setFrequency(freq);waveFile683->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile683->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==44) {waveFile684->setFrequency(freq);waveFile684->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile684->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==45) {waveFile685->setFrequency(freq);waveFile685->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile685->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==46) {waveFile686->setFrequency(freq);waveFile686->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile686->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==47) {waveFile687->setFrequency(freq);waveFile687->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile687->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==48) {waveFile688->setFrequency(freq);waveFile688->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile688->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==49) {waveFile689->setFrequency(freq);waveFile689->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile689->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==50) {waveFile690->setFrequency(freq);waveFile690->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile690->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==51) {waveFile691->setFrequency(freq);waveFile691->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile691->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==52) {waveFile692->setFrequency(freq);waveFile692->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile692->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==53) {waveFile693->setFrequency(freq);waveFile693->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile693->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==54) {waveFile694->setFrequency(freq);waveFile694->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile694->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==55) {waveFile695->setFrequency(freq);waveFile695->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile695->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==56) {waveFile696->setFrequency(freq);waveFile696->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile696->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==57) {waveFile697->setFrequency(freq);waveFile697->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile697->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==58) {waveFile698->setFrequency(freq);waveFile698->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile698->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==59) {waveFile699->setFrequency(freq);waveFile699->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile699->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==60) {waveFile700->setFrequency(freq);waveFile700->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile700->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==61) {waveFile701->setFrequency(freq);waveFile701->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile701->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==62) {waveFile702->setFrequency(freq);waveFile702->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile702->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==63) {waveFile703->setFrequency(freq);waveFile703->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile703->lastOut(), lastPlayed, 0.25);}


}


if(bank==12)

{


if((int)tableSelector==0) {waveFile704->setFrequency(freq);waveFile704->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile704->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==1) {waveFile705->setFrequency(freq);waveFile705->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile705->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==2) {waveFile706->setFrequency(freq);waveFile706->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile706->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==3) {waveFile707->setFrequency(freq);waveFile707->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile707->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==4) {waveFile708->setFrequency(freq);waveFile708->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile708->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==5) {waveFile709->setFrequency(freq);waveFile709->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile709->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==6) {waveFile710->setFrequency(freq);waveFile710->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile710->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==7) {waveFile711->setFrequency(freq);waveFile711->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile711->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==8) {waveFile712->setFrequency(freq);waveFile712->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile712->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==9) {waveFile713->setFrequency(freq);waveFile713->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile713->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==10) {waveFile714->setFrequency(freq);waveFile714->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile714->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==11) {waveFile715->setFrequency(freq);waveFile715->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile715->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==12) {waveFile716->setFrequency(freq);waveFile716->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile716->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==13) {waveFile717->setFrequency(freq);waveFile717->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile717->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==14) {waveFile718->setFrequency(freq);waveFile718->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile718->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==15) {waveFile719->setFrequency(freq);waveFile719->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile719->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==16) {waveFile720->setFrequency(freq);waveFile720->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile720->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==17) {waveFile721->setFrequency(freq);waveFile721->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile721->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==18) {waveFile722->setFrequency(freq);waveFile722->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile722->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==19) {waveFile723->setFrequency(freq);waveFile723->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile723->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==20) {waveFile724->setFrequency(freq);waveFile724->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile724->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==21) {waveFile725->setFrequency(freq);waveFile725->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile725->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==22) {waveFile726->setFrequency(freq);waveFile726->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile726->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==23) {waveFile727->setFrequency(freq);waveFile727->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile727->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==24) {waveFile728->setFrequency(freq);waveFile728->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile728->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==25) {waveFile729->setFrequency(freq);waveFile729->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile729->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==26) {waveFile730->setFrequency(freq);waveFile730->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile730->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==27) {waveFile731->setFrequency(freq);waveFile731->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile731->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==28) {waveFile732->setFrequency(freq);waveFile732->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile732->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==29) {waveFile733->setFrequency(freq);waveFile733->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile733->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==30) {waveFile734->setFrequency(freq);waveFile734->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile734->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==31) {waveFile735->setFrequency(freq);waveFile735->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile735->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==32) {waveFile736->setFrequency(freq);waveFile736->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile736->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==33) {waveFile737->setFrequency(freq);waveFile737->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile737->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==34) {waveFile738->setFrequency(freq);waveFile738->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile738->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==35) {waveFile739->setFrequency(freq);waveFile739->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile739->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==36) {waveFile740->setFrequency(freq);waveFile740->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile740->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==37) {waveFile741->setFrequency(freq);waveFile741->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile741->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==38) {waveFile742->setFrequency(freq);waveFile742->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile742->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==39) {waveFile743->setFrequency(freq);waveFile743->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile743->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==40) {waveFile744->setFrequency(freq);waveFile744->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile744->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==41) {waveFile745->setFrequency(freq);waveFile745->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile745->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==42) {waveFile746->setFrequency(freq);waveFile746->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile746->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==43) {waveFile747->setFrequency(freq);waveFile747->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile747->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==44) {waveFile748->setFrequency(freq);waveFile748->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile748->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==45) {waveFile749->setFrequency(freq);waveFile749->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile749->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==46) {waveFile750->setFrequency(freq);waveFile750->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile750->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==47) {waveFile751->setFrequency(freq);waveFile751->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile751->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==48) {waveFile752->setFrequency(freq);waveFile752->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile752->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==49) {waveFile753->setFrequency(freq);waveFile753->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile753->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==50) {waveFile754->setFrequency(freq);waveFile754->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile754->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==51) {waveFile755->setFrequency(freq);waveFile755->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile755->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==52) {waveFile756->setFrequency(freq);waveFile756->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile756->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==53) {waveFile757->setFrequency(freq);waveFile757->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile757->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==54) {waveFile758->setFrequency(freq);waveFile758->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile758->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==55) {waveFile759->setFrequency(freq);waveFile759->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile759->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==56) {waveFile760->setFrequency(freq);waveFile760->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile760->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==57) {waveFile761->setFrequency(freq);waveFile761->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile761->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==58) {waveFile762->setFrequency(freq);waveFile762->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile762->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==59) {waveFile763->setFrequency(freq);waveFile763->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile763->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==60) {waveFile764->setFrequency(freq);waveFile764->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile764->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==61) {waveFile765->setFrequency(freq);waveFile765->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile765->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==62) {waveFile766->setFrequency(freq);waveFile766->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile766->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==63) {waveFile767->setFrequency(freq);waveFile767->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile767->lastOut(), lastPlayed, 0.25);}


}


if(bank==13)

{


if((int)tableSelector==0) {waveFile768->setFrequency(freq);waveFile768->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile768->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==1) {waveFile769->setFrequency(freq);waveFile769->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile769->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==2) {waveFile770->setFrequency(freq);waveFile770->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile770->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==3) {waveFile771->setFrequency(freq);waveFile771->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile771->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==4) {waveFile772->setFrequency(freq);waveFile772->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile772->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==5) {waveFile773->setFrequency(freq);waveFile773->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile773->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==6) {waveFile774->setFrequency(freq);waveFile774->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile774->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==7) {waveFile775->setFrequency(freq);waveFile775->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile775->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==8) {waveFile776->setFrequency(freq);waveFile776->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile776->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==9) {waveFile777->setFrequency(freq);waveFile777->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile777->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==10) {waveFile778->setFrequency(freq);waveFile778->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile778->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==11) {waveFile779->setFrequency(freq);waveFile779->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile779->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==12) {waveFile780->setFrequency(freq);waveFile780->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile780->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==13) {waveFile781->setFrequency(freq);waveFile781->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile781->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==14) {waveFile782->setFrequency(freq);waveFile782->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile782->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==15) {waveFile783->setFrequency(freq);waveFile783->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile783->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==16) {waveFile784->setFrequency(freq);waveFile784->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile784->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==17) {waveFile785->setFrequency(freq);waveFile785->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile785->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==18) {waveFile786->setFrequency(freq);waveFile786->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile786->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==19) {waveFile787->setFrequency(freq);waveFile787->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile787->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==20) {waveFile788->setFrequency(freq);waveFile788->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile788->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==21) {waveFile789->setFrequency(freq);waveFile789->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile789->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==22) {waveFile790->setFrequency(freq);waveFile790->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile790->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==23) {waveFile791->setFrequency(freq);waveFile791->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile791->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==24) {waveFile792->setFrequency(freq);waveFile792->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile792->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==25) {waveFile793->setFrequency(freq);waveFile793->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile793->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==26) {waveFile794->setFrequency(freq);waveFile794->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile794->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==27) {waveFile795->setFrequency(freq);waveFile795->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile795->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==28) {waveFile796->setFrequency(freq);waveFile796->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile796->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==29) {waveFile797->setFrequency(freq);waveFile797->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile797->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==30) {waveFile798->setFrequency(freq);waveFile798->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile798->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==31) {waveFile799->setFrequency(freq);waveFile799->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile799->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==32) {waveFile800->setFrequency(freq);waveFile800->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile800->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==33) {waveFile801->setFrequency(freq);waveFile801->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile801->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==34) {waveFile802->setFrequency(freq);waveFile802->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile802->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==35) {waveFile803->setFrequency(freq);waveFile803->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile803->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==36) {waveFile804->setFrequency(freq);waveFile804->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile804->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==37) {waveFile805->setFrequency(freq);waveFile805->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile805->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==38) {waveFile806->setFrequency(freq);waveFile806->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile806->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==39) {waveFile807->setFrequency(freq);waveFile807->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile807->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==40) {waveFile808->setFrequency(freq);waveFile808->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile808->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==41) {waveFile809->setFrequency(freq);waveFile809->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile809->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==42) {waveFile810->setFrequency(freq);waveFile810->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile810->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==43) {waveFile811->setFrequency(freq);waveFile811->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile811->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==44) {waveFile812->setFrequency(freq);waveFile812->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile812->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==45) {waveFile813->setFrequency(freq);waveFile813->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile813->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==46) {waveFile814->setFrequency(freq);waveFile814->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile814->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==47) {waveFile815->setFrequency(freq);waveFile815->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile815->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==48) {waveFile816->setFrequency(freq);waveFile816->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile816->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==49) {waveFile817->setFrequency(freq);waveFile817->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile817->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==50) {waveFile818->setFrequency(freq);waveFile818->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile818->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==51) {waveFile819->setFrequency(freq);waveFile819->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile819->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==52) {waveFile820->setFrequency(freq);waveFile820->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile820->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==53) {waveFile821->setFrequency(freq);waveFile821->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile821->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==54) {waveFile822->setFrequency(freq);waveFile822->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile822->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==55) {waveFile823->setFrequency(freq);waveFile823->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile823->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==56) {waveFile824->setFrequency(freq);waveFile824->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile824->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==57) {waveFile825->setFrequency(freq);waveFile825->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile825->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==58) {waveFile826->setFrequency(freq);waveFile826->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile826->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==59) {waveFile827->setFrequency(freq);waveFile827->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile827->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==60) {waveFile828->setFrequency(freq);waveFile828->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile828->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==61) {waveFile829->setFrequency(freq);waveFile829->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile829->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==62) {waveFile830->setFrequency(freq);waveFile830->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile830->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==63) {waveFile831->setFrequency(freq);waveFile831->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile831->lastOut(), lastPlayed, 0.25);}



}



if (bank==14)
{
if((int)tableSelector==0) {waveFile832->setFrequency(freq);waveFile832->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile832->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==1) {waveFile833->setFrequency(freq);waveFile833->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile833->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==2) {waveFile834->setFrequency(freq);waveFile834->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile834->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==3) {waveFile835->setFrequency(freq);waveFile835->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile835->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==4) {waveFile836->setFrequency(freq);waveFile836->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile836->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==5) {waveFile837->setFrequency(freq);waveFile837->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile837->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==6) {waveFile838->setFrequency(freq);waveFile838->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile838->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==7) {waveFile839->setFrequency(freq);waveFile839->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile839->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==8) {waveFile840->setFrequency(freq);waveFile840->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile840->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==9) {waveFile841->setFrequency(freq);waveFile841->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile841->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==10) {waveFile842->setFrequency(freq);waveFile842->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile842->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==11) {waveFile843->setFrequency(freq);waveFile843->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile843->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==12) {waveFile844->setFrequency(freq);waveFile844->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile844->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==13) {waveFile845->setFrequency(freq);waveFile845->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile845->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==14) {waveFile846->setFrequency(freq);waveFile846->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile846->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==15) {waveFile847->setFrequency(freq);waveFile847->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile847->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==16) {waveFile848->setFrequency(freq);waveFile848->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile848->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==17) {waveFile849->setFrequency(freq);waveFile849->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile849->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==18) {waveFile850->setFrequency(freq);waveFile850->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile850->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==19) {waveFile851->setFrequency(freq);waveFile851->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile851->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==20) {waveFile852->setFrequency(freq);waveFile852->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile852->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==21) {waveFile853->setFrequency(freq);waveFile853->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile853->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==22) {waveFile854->setFrequency(freq);waveFile854->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile854->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==23) {waveFile855->setFrequency(freq);waveFile855->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile855->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==24) {waveFile856->setFrequency(freq);waveFile856->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile856->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==25) {waveFile857->setFrequency(freq);waveFile857->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile857->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==26) {waveFile858->setFrequency(freq);waveFile858->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile858->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==27) {waveFile859->setFrequency(freq);waveFile859->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile859->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==28) {waveFile860->setFrequency(freq);waveFile860->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile860->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==29) {waveFile861->setFrequency(freq);waveFile861->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile861->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==30) {waveFile862->setFrequency(freq);waveFile862->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile862->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==31) {waveFile863->setFrequency(freq);waveFile863->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile863->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==32) {waveFile864->setFrequency(freq);waveFile864->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile864->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==33) {waveFile865->setFrequency(freq);waveFile865->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile865->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==34) {waveFile866->setFrequency(freq);waveFile866->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile866->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==35) {waveFile867->setFrequency(freq);waveFile867->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile867->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==36) {waveFile868->setFrequency(freq);waveFile868->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile868->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==37) {waveFile869->setFrequency(freq);waveFile869->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile869->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==38) {waveFile870->setFrequency(freq);waveFile870->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile870->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==39) {waveFile871->setFrequency(freq);waveFile871->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile871->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==40) {waveFile872->setFrequency(freq);waveFile872->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile872->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==41) {waveFile873->setFrequency(freq);waveFile873->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile873->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==42) {waveFile874->setFrequency(freq);waveFile874->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile874->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==43) {waveFile875->setFrequency(freq);waveFile875->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile875->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==44) {waveFile876->setFrequency(freq);waveFile876->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile876->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==45) {waveFile877->setFrequency(freq);waveFile877->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile877->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==46) {waveFile878->setFrequency(freq);waveFile878->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile878->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==47) {waveFile879->setFrequency(freq);waveFile879->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile879->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==48) {waveFile880->setFrequency(freq);waveFile880->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile880->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==49) {waveFile881->setFrequency(freq);waveFile881->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile881->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==50) {waveFile882->setFrequency(freq);waveFile882->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile882->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==51) {waveFile883->setFrequency(freq);waveFile883->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile883->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==52) {waveFile884->setFrequency(freq);waveFile884->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile884->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==53) {waveFile885->setFrequency(freq);waveFile885->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile885->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==54) {waveFile886->setFrequency(freq);waveFile886->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile886->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==55) {waveFile887->setFrequency(freq);waveFile887->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile887->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==56) {waveFile888->setFrequency(freq);waveFile888->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile888->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==57) {waveFile889->setFrequency(freq);waveFile889->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile889->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==58) {waveFile890->setFrequency(freq);waveFile890->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile890->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==59) {waveFile891->setFrequency(freq);waveFile891->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile891->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==60) {waveFile892->setFrequency(freq);waveFile892->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile892->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==61) {waveFile893->setFrequency(freq);waveFile893->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile893->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==62) {waveFile894->setFrequency(freq);waveFile894->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile894->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==63) {waveFile895->setFrequency(freq);waveFile895->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile895->lastOut(), lastPlayed, 0.25);}


}



if (bank==15)
{

if((int)tableSelector==0) {waveFile896->setFrequency(freq);waveFile896->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile896->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==1) {waveFile897->setFrequency(freq);waveFile897->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile897->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==2) {waveFile898->setFrequency(freq);waveFile898->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile898->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==3) {waveFile899->setFrequency(freq);waveFile899->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile899->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==4) {waveFile900->setFrequency(freq);waveFile900->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile900->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==5) {waveFile901->setFrequency(freq);waveFile901->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile901->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==6) {waveFile902->setFrequency(freq);waveFile902->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile902->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==7) {waveFile903->setFrequency(freq);waveFile903->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile903->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==8) {waveFile904->setFrequency(freq);waveFile904->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile904->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==9) {waveFile905->setFrequency(freq);waveFile905->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile905->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==10) {waveFile906->setFrequency(freq);waveFile906->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile906->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==11) {waveFile907->setFrequency(freq);waveFile907->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile907->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==12) {waveFile908->setFrequency(freq);waveFile908->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile908->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==13) {waveFile909->setFrequency(freq);waveFile909->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile909->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==14) {waveFile910->setFrequency(freq);waveFile910->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile910->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==15) {waveFile911->setFrequency(freq);waveFile911->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile911->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==16) {waveFile912->setFrequency(freq);waveFile912->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile912->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==17) {waveFile913->setFrequency(freq);waveFile913->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile913->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==18) {waveFile914->setFrequency(freq);waveFile914->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile914->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==19) {waveFile915->setFrequency(freq);waveFile915->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile915->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==20) {waveFile916->setFrequency(freq);waveFile916->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile916->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==21) {waveFile917->setFrequency(freq);waveFile917->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile917->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==22) {waveFile918->setFrequency(freq);waveFile918->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile918->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==23) {waveFile919->setFrequency(freq);waveFile919->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile919->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==24) {waveFile920->setFrequency(freq);waveFile920->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile920->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==25) {waveFile921->setFrequency(freq);waveFile921->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile921->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==26) {waveFile922->setFrequency(freq);waveFile922->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile922->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==27) {waveFile923->setFrequency(freq);waveFile923->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile923->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==28) {waveFile924->setFrequency(freq);waveFile924->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile924->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==29) {waveFile925->setFrequency(freq);waveFile925->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile925->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==30) {waveFile926->setFrequency(freq);waveFile926->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile926->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==31) {waveFile927->setFrequency(freq);waveFile927->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile927->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==32) {waveFile928->setFrequency(freq);waveFile928->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile928->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==33) {waveFile929->setFrequency(freq);waveFile929->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile929->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==34) {waveFile930->setFrequency(freq);waveFile930->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile930->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==35) {waveFile931->setFrequency(freq);waveFile931->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile931->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==36) {waveFile932->setFrequency(freq);waveFile932->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile932->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==37) {waveFile933->setFrequency(freq);waveFile933->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile933->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==38) {waveFile934->setFrequency(freq);waveFile934->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile934->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==39) {waveFile935->setFrequency(freq);waveFile935->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile935->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==40) {waveFile936->setFrequency(freq);waveFile936->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile936->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==41) {waveFile937->setFrequency(freq);waveFile937->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile937->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==42) {waveFile938->setFrequency(freq);waveFile938->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile938->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==43) {waveFile939->setFrequency(freq);waveFile939->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile939->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==44) {waveFile940->setFrequency(freq);waveFile940->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile940->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==45) {waveFile941->setFrequency(freq);waveFile941->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile941->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==46) {waveFile942->setFrequency(freq);waveFile942->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile942->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==47) {waveFile943->setFrequency(freq);waveFile943->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile943->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==48) {waveFile944->setFrequency(freq);waveFile944->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile944->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==49) {waveFile945->setFrequency(freq);waveFile945->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile945->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==50) {waveFile946->setFrequency(freq);waveFile946->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile946->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==51) {waveFile947->setFrequency(freq);waveFile947->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile947->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==52) {waveFile948->setFrequency(freq);waveFile948->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile948->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==53) {waveFile949->setFrequency(freq);waveFile949->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile949->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==54) {waveFile950->setFrequency(freq);waveFile950->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile950->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==55) {waveFile951->setFrequency(freq);waveFile951->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile951->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==56) {waveFile952->setFrequency(freq);waveFile952->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile952->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==57) {waveFile953->setFrequency(freq);waveFile953->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile953->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==58) {waveFile954->setFrequency(freq);waveFile954->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile954->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==59) {waveFile955->setFrequency(freq);waveFile955->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile955->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==60) {waveFile956->setFrequency(freq);waveFile956->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile956->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==61) {waveFile957->setFrequency(freq);waveFile957->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile957->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==62) {waveFile958->setFrequency(freq);waveFile958->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile958->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==63) {waveFile959->setFrequency(freq);waveFile959->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile959->lastOut(), lastPlayed, 0.25);}
	
}



if (bank==16)
{

if((int)tableSelector==0) {waveFile960->setFrequency(freq);waveFile960->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile960->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==1) {waveFile961->setFrequency(freq);waveFile961->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile961->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==2) {waveFile962->setFrequency(freq);waveFile962->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile962->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==3) {waveFile963->setFrequency(freq);waveFile963->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile963->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==4) {waveFile964->setFrequency(freq);waveFile964->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile964->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==5) {waveFile965->setFrequency(freq);waveFile965->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile965->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==6) {waveFile966->setFrequency(freq);waveFile966->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile966->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==7) {waveFile967->setFrequency(freq);waveFile967->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile967->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==8) {waveFile968->setFrequency(freq);waveFile968->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile968->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==9) {waveFile969->setFrequency(freq);waveFile969->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile969->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==10) {waveFile970->setFrequency(freq);waveFile970->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile970->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==11) {waveFile971->setFrequency(freq);waveFile971->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile971->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==12) {waveFile972->setFrequency(freq);waveFile972->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile972->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==13) {waveFile973->setFrequency(freq);waveFile973->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile973->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==14) {waveFile974->setFrequency(freq);waveFile974->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile974->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==15) {waveFile975->setFrequency(freq);waveFile975->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile975->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==16) {waveFile976->setFrequency(freq);waveFile976->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile976->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==17) {waveFile977->setFrequency(freq);waveFile977->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile977->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==18) {waveFile978->setFrequency(freq);waveFile978->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile978->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==19) {waveFile979->setFrequency(freq);waveFile979->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile979->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==20) {waveFile980->setFrequency(freq);waveFile980->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile980->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==21) {waveFile981->setFrequency(freq);waveFile981->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile981->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==22) {waveFile982->setFrequency(freq);waveFile982->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile982->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==23) {waveFile983->setFrequency(freq);waveFile983->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile983->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==24) {waveFile984->setFrequency(freq);waveFile984->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile984->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==25) {waveFile985->setFrequency(freq);waveFile985->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile985->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==26) {waveFile986->setFrequency(freq);waveFile986->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile986->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==27) {waveFile987->setFrequency(freq);waveFile987->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile987->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==28) {waveFile988->setFrequency(freq);waveFile988->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile988->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==29) {waveFile989->setFrequency(freq);waveFile989->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile989->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==30) {waveFile990->setFrequency(freq);waveFile990->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile990->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==31) {waveFile991->setFrequency(freq);waveFile991->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile991->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==32) {waveFile992->setFrequency(freq);waveFile992->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile992->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==33) {waveFile993->setFrequency(freq);waveFile993->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile993->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==34) {waveFile994->setFrequency(freq);waveFile994->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile994->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==35) {waveFile995->setFrequency(freq);waveFile995->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile995->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==36) {waveFile996->setFrequency(freq);waveFile996->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile996->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==37) {waveFile997->setFrequency(freq);waveFile997->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile997->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==38) {waveFile998->setFrequency(freq);waveFile998->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile998->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==39) {waveFile999->setFrequency(freq);waveFile999->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile999->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==40) {waveFile1000->setFrequency(freq);waveFile1000->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile1000->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==41) {waveFile1001->setFrequency(freq);waveFile1001->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile1001->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==42) {waveFile1002->setFrequency(freq);waveFile1002->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile1002->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==43) {waveFile1003->setFrequency(freq);waveFile1003->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile1003->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==44) {waveFile1004->setFrequency(freq);waveFile1004->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile1004->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==45) {waveFile1005->setFrequency(freq);waveFile1005->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile1005->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==46) {waveFile1006->setFrequency(freq);waveFile1006->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile1006->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==47) {waveFile1007->setFrequency(freq);waveFile1007->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile1007->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==48) {waveFile1008->setFrequency(freq);waveFile1008->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile1008->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==49) {waveFile1009->setFrequency(freq);waveFile1009->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile1009->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==50) {waveFile1010->setFrequency(freq);waveFile1010->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile1010->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==51) {waveFile1011->setFrequency(freq);waveFile1011->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile1011->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==52) {waveFile1012->setFrequency(freq);waveFile1012->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile1012->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==53) {waveFile1013->setFrequency(freq);waveFile1013->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile1013->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==54) {waveFile1014->setFrequency(freq);waveFile1014->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile1014->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==55) {waveFile1015->setFrequency(freq);waveFile1015->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile1015->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==56) {waveFile1016->setFrequency(freq);waveFile1016->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile1016->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==57) {waveFile1017->setFrequency(freq);waveFile1017->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile1017->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==58) {waveFile1018->setFrequency(freq);waveFile1018->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile1018->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==59) {waveFile1019->setFrequency(freq);waveFile1019->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile1019->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==60) {waveFile1020->setFrequency(freq);waveFile1020->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile1020->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==61) {waveFile1021->setFrequency(freq);waveFile1021->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile1021->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==62) {waveFile1022->setFrequency(freq);waveFile1022->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile1022->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==63) {waveFile1023->setFrequency(freq);waveFile1023->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile1023->lastOut(), lastPlayed, 0.25);}
	
}



if (bank==17)
{

if((int)tableSelector==0) {waveFile1024->setFrequency(freq);waveFile1024->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile1024->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==1) {waveFile1025->setFrequency(freq);waveFile1025->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile1025->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==2) {waveFile1026->setFrequency(freq);waveFile1026->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile1026->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==3) {waveFile1027->setFrequency(freq);waveFile1027->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile1027->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==4) {waveFile1028->setFrequency(freq);waveFile1028->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile1028->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==5) {waveFile1029->setFrequency(freq);waveFile1029->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile1029->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==6) {waveFile1030->setFrequency(freq);waveFile1030->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile1030->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==7) {waveFile1031->setFrequency(freq);waveFile1031->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile1031->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==8) {waveFile1032->setFrequency(freq);waveFile1032->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile1032->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==9) {waveFile1033->setFrequency(freq);waveFile1033->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile1033->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==10) {waveFile1034->setFrequency(freq);waveFile1034->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile1034->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==11) {waveFile1035->setFrequency(freq);waveFile1035->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile1035->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==12) {waveFile1036->setFrequency(freq);waveFile1036->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile1036->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==13) {waveFile1037->setFrequency(freq);waveFile1037->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile1037->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==14) {waveFile1038->setFrequency(freq);waveFile1038->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile1038->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==15) {waveFile1039->setFrequency(freq);waveFile1039->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile1039->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==16) {waveFile1040->setFrequency(freq);waveFile1040->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile1040->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==17) {waveFile1041->setFrequency(freq);waveFile1041->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile1041->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==18) {waveFile1042->setFrequency(freq);waveFile1042->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile1042->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==19) {waveFile1043->setFrequency(freq);waveFile1043->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile1043->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==20) {waveFile1044->setFrequency(freq);waveFile1044->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile1044->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==21) {waveFile1045->setFrequency(freq);waveFile1045->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile1045->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==22) {waveFile1046->setFrequency(freq);waveFile1046->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile1046->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==23) {waveFile1047->setFrequency(freq);waveFile1047->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile1047->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==24) {waveFile1048->setFrequency(freq);waveFile1048->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile1048->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==25) {waveFile1049->setFrequency(freq);waveFile1049->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile1049->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==26) {waveFile1050->setFrequency(freq);waveFile1050->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile1050->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==27) {waveFile1051->setFrequency(freq);waveFile1051->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile1051->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==28) {waveFile1052->setFrequency(freq);waveFile1052->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile1052->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==29) {waveFile1053->setFrequency(freq);waveFile1053->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile1053->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==30) {waveFile1054->setFrequency(freq);waveFile1054->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile1054->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==31) {waveFile1055->setFrequency(freq);waveFile1055->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile1055->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==32) {waveFile1056->setFrequency(freq);waveFile1056->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile1056->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==33) {waveFile1057->setFrequency(freq);waveFile1057->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile1057->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==34) {waveFile1058->setFrequency(freq);waveFile1058->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile1058->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==35) {waveFile1059->setFrequency(freq);waveFile1059->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile1059->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==36) {waveFile1060->setFrequency(freq);waveFile1060->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile1060->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==37) {waveFile1061->setFrequency(freq);waveFile1061->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile1061->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==38) {waveFile1062->setFrequency(freq);waveFile1062->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile1062->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==39) {waveFile1063->setFrequency(freq);waveFile1063->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile1063->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==40) {waveFile1064->setFrequency(freq);waveFile1064->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile1064->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==41) {waveFile1065->setFrequency(freq);waveFile1065->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile1065->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==42) {waveFile1066->setFrequency(freq);waveFile1066->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile1066->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==43) {waveFile1067->setFrequency(freq);waveFile1067->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile1067->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==44) {waveFile1068->setFrequency(freq);waveFile1068->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile1068->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==45) {waveFile1069->setFrequency(freq);waveFile1069->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile1069->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==46) {waveFile1070->setFrequency(freq);waveFile1070->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile1070->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==47) {waveFile1071->setFrequency(freq);waveFile1071->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile1071->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==48) {waveFile1072->setFrequency(freq);waveFile1072->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile1072->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==49) {waveFile1073->setFrequency(freq);waveFile1073->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile1073->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==50) {waveFile1074->setFrequency(freq);waveFile1074->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile1074->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==51) {waveFile1075->setFrequency(freq);waveFile1075->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile1075->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==52) {waveFile1076->setFrequency(freq);waveFile1076->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile1076->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==53) {waveFile1077->setFrequency(freq);waveFile1077->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile1077->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==54) {waveFile1078->setFrequency(freq);waveFile1078->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile1078->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==55) {waveFile1079->setFrequency(freq);waveFile1079->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile1079->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==56) {waveFile1080->setFrequency(freq);waveFile1080->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile1080->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==57) {waveFile1081->setFrequency(freq);waveFile1081->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile1081->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==58) {waveFile1082->setFrequency(freq);waveFile1082->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile1082->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==59) {waveFile1083->setFrequency(freq);waveFile1083->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile1083->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==60) {waveFile1084->setFrequency(freq);waveFile1084->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile1084->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==61) {waveFile1085->setFrequency(freq);waveFile1085->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile1085->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==62) {waveFile1086->setFrequency(freq);waveFile1086->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile1086->lastOut(), lastPlayed, 0.25);}
if((int)tableSelector==63) {waveFile1087->setFrequency(freq);waveFile1087->tick(0);outputs[OUT_WAVEFILE].value= CosineInterpolateWaves(waveFile1087->lastOut(), lastPlayed, 0.25);}
	
}






bq->setBiquad(bq_type_peak, 8000.0 / engineGetSampleRate(), 5, 0);

outputs[OUT_WAVEFILE].value = bq->process(outputs[OUT_WAVEFILE].value);



outputs[OUT_WAVEFILE].value*=params[PARAM_VOL].value*5;

oldSampleRate=engineGetSampleRate();
oldtableSelector=paramtableSelector;
	


}







struct WavesModelDisplay : TransparentWidget {
  int *value;

  std::shared_ptr<Font> font;

  WavesModelDisplay() {
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
	
	//ADD LEADING ZEROS
	std::string z;
	if(to_display.length()==1){z="00"+to_display;}
		else {z="0"+to_display;}

    nvgText(vg, textPos.x, textPos.y, z.c_str(), NULL);
  }
};






struct WavesModelDisplayFromZero : TransparentWidget {
  int *value;

  std::shared_ptr<Font> font;

  WavesModelDisplayFromZero() {
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

    std::string to_display = std::to_string(*value+1);
    Vec textPos = Vec(7.0f, 35.0f);

    NVGcolor textColor = nvgRGB(0xdf, 0xd2, 0x2c);
    nvgFillColor(vg, nvgTransRGBA(textColor, 16));
    nvgText(vg, textPos.x, textPos.y, "~~~", NULL);

    textColor = nvgRGB(0xda, 0xe9, 0x29);
    nvgFillColor(vg, nvgTransRGBA(textColor, 16));
    nvgText(vg, textPos.x, textPos.y, "\\\\\\", NULL);

    textColor = nvgRGB(0xf0, 0x00, 0x00);
    nvgFillColor(vg, textColor);
	
	//ADD LEADING ZEROS
	std::string z;
	if(to_display.length()==1){z="00"+to_display;}
		else {z="0"+to_display;}

    nvgText(vg, textPos.x, textPos.y, z.c_str(), NULL);
  }
};


WavesModelWidget::WavesModelWidget() {
	WavesModel *module = new WavesModel();
	setModule(module);
	box.size = Vec(15 * 18 ,380); 

	{
		SVGPanel *panel = new SVGPanel();
		panel->box.size = box.size;
		
        panel->setBackground(SVG::load(assetPlugin(plugin, "res/WAVESVCO.svg")));
		addChild(panel);

	}

{
    WavesModelDisplay *displayBank = new WavesModelDisplay();
    displayBank->box.pos = Vec(140,55);
    displayBank->box.size = Vec(82, 42);


    displayBank->value = &module->bank;
    addChild(displayBank);
  }



{
    WavesModelDisplayFromZero *displayTable = new WavesModelDisplayFromZero();
    displayTable->box.pos = Vec(140, 260);
    displayTable->box.size = Vec(82, 42);
 


    displayTable->value = &module->tableSelector;
   
    addChild(displayTable);
  }

 

	addChild(createScrew<ScrewSilver>(Vec(1, 0)));
	addChild(createScrew<ScrewSilver>(Vec(box.size.x - 20, 0)));
	addChild(createScrew<ScrewSilver>(Vec(1, 365)));
	addChild(createScrew<ScrewSilver>(Vec(box.size.x - 20, 365)));

	//addParam(createParam<LEDButton>(Vec(235, 65), module, WavesModel::BANKNUM, 0.0, 1.0, 0.0));
	//addChild(createValueLight<SmallLight<RedValueLight>>(Vec(240,70), &module->light));

addParam(createParam<BtnUp>(Vec(225, 58), module, WavesModel::BANKUP, 0.0, 1.0, 0.0));
addParam(createParam<BtnDwn>(Vec(225, 76), module, WavesModel::BANKDWN, 0.0, 1.0, 0.0));


	addParam(createParam<AutodafeKnobRedBig>(Vec(18, 50), module, WavesModel::PARAM_FREQ, -40.0, 0.0, -20.0));
	addParam(createParam<AutodafeKnobRed>(Vec(25, 120), module, WavesModel::PARAM_FINE, -1.0, 1.0, 0.0));
	

	addParam(createParam<AutodafeKnobRed>(Vec(25, 190), module, WavesModel::PARAM_FREQ_CV, -1, 1, 0));
	addInput(createInput<PJ301MPort>(Vec(90, 195), module, WavesModel::INPUT_FREQ_CV));

	
	addParam(createParam<AutodafeKnobRed>(Vec(85, 120 ), module, WavesModel::PARAM_VOL, 0.0, 1.0, 1.0));


addParam(createParam<AutodafeKnobRed>(Vec(25, 260), module, WavesModel::PARAM_TAB, 0, 64,0));
	addInput(createInput<PJ301MPort>(Vec(90, 265), module, WavesModel::INPUT_TAB_CV));




addParam(createParam<BtnUp>(Vec(225, 263), module, WavesModel::TABUP, 0.0, 1.0, 0.0));
addParam(createParam<BtnDwn>(Vec(225, 281), module, WavesModel::TABDWN, 0.0, 1.0, 0.0));
//addChild(createValueLight<SmallLight<RedValueLight>>(Vec(240,265), &module->lightUp));
//addChild(createValueLight<SmallLight<RedValueLight>>(Vec(240,289), &module->lightDwn));



	
addOutput(createOutput<PJ301MPort>(Vec(90, 65), module, WavesModel::OUT_WAVEFILE));






	
}
