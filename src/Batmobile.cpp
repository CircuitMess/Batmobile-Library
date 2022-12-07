#include "Batmobile.h"
#include <Loop/LoopManager.h>

BatmobileImpl Batmobile;
MotorControl Motors;
S3Interface S3;
AudioSystem Audio;
SingleLEDController Headlights(LED_FRONT, 0);
SingleLEDController Taillights(LED_BACK, 1);
RGBLEDController Underlights({ LED_R, LED_G, LED_B }, { 2, 3, 4 });

BatmobileImpl::BatmobileImpl(){

}

void BatmobileImpl::begin(){
	Motors.begin();

	disableCore0WDT();
	disableCore1WDT();

	WiFi.mode(WIFI_OFF);
	btStop();

	if(!SPIFFS.begin()){
		Serial.println("SPIFFS error");
	}

	Headlights.begin();
	Taillights.begin();
	Underlights.begin();

	Audio.begin();

	if(!S3.begin()){
		printf("S3 begin failed\n");
	}
}

