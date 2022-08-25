#include "Batmobile.h"
#include <SPIFFS.h>
#include <Loop/LoopManager.h>

BatmobileImpl Batmobile;

BatmobileImpl::BatmobileImpl() : display(160, 128, -1, 3), input(INPUT_DATA, INPUT_CLOCK, INPUT_LOAD, 16){

}

void BatmobileImpl::begin(){
	pinMode(PIN_BL, OUTPUT);
	digitalWrite(PIN_BL, false);

	Piezo.begin(PIN_BUZZ);
	Piezo.noTone();

	display.begin();
	display.getTft()->setRotation(1);
	display.swapBytes(false);
	display.getBaseSprite()->clear(TFT_BLACK);
	display.commit();

	if(!SPIFFS.begin()){
		Serial.println("SPIFFS failed");
	}


	input.begin();

	Vector<uint8_t> buttons;
	for(int i = 0; i < 16; i++){
		buttons.push_back(i);
	}
	input.preregisterButtons(buttons);

	LoopManager::addListener(&input);
}

Display* BatmobileImpl::getDisplay(){
	return &display;
}

Input* BatmobileImpl::getInput(){
	return &input;
}
