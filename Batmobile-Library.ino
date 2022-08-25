#include <Arduino.h>
#include <CircuitOS.h>
#include "src/Batmobile.h"

void setup(){
	Batmobile.begin();
	Batmobile.getDisplay()->clear(TFT_RED);
	Batmobile.getDisplay()->commit();
}

void loop(){
}