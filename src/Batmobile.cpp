#include "Batmobile.h"
#include <SPIFFS.h>
#include <Loop/LoopManager.h>

BatmobileImpl Batmobile;

BatmobileImpl::BatmobileImpl() : display(160, 128, -1, -1){

}

void BatmobileImpl::begin(){
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
		for(;;);
	}

	display.begin();
}

Display* BatmobileImpl::getDisplay(){
	return &display;
}

