#include "Batmobile.h"
#include <SPIFFS.h>
#include <Loop/LoopManager.h>

BatmobileImpl Batmobile;
MotorControl Motors;
S3Interface S3;
SingleLEDController Headlights(LED_FRONT, 0);
SingleLEDController Taillights(LED_BACK, 1);
RGBLEDController Underlights({ LED_R, LED_G, LED_B }, { 2, 3, 4 });

BatmobileImpl::BatmobileImpl(){

}

void BatmobileImpl::begin(){
	Motors.begin();

	if(psramFound()){
		Serial.printf("PSRAM init: %s, free: %d B\n", psramInit() ? "Yes" : "No", ESP.getFreePsram());
	}else{
		Serial.println("No PSRAM detected");
	}

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

	S3.begin();
}

