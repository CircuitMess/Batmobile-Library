#ifndef BATMOBILE_LIBRARY_BATMOBILE_H
#define BATMOBILE_LIBRARY_BATMOBILE_H

#include <Arduino.h>
#include <CircuitOS.h>
#include <BatCommon.h>
#include <Display/Display.h>
#include <WiFi.h>
#include <SPIFFS.h>
#include <Loop/LoopManager.h>
#include "S3Interface.h"
#include "Motors.h"
#include "LED/LEDController.h"

class BatmobileImpl {
public:
	BatmobileImpl();
	void begin();

private:


};

extern SingleLEDController Headlights;
extern SingleLEDController Taillights;
extern RGBLEDController Underlights;

extern BatmobileImpl Batmobile;
extern MotorControl Motors;
extern S3Interface S3;


#endif //BATMOBILE_LIBRARY_BATMOBILE_H
