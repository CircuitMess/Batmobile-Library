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

class BatmobileImpl {
public:
	BatmobileImpl();
	void begin();

private:


};

extern BatmobileImpl Batmobile;
extern S3Interface S3;


#endif //BATMOBILE_LIBRARY_BATMOBILE_H
