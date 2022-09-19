#ifndef BATMOBILE_LIBRARY_BATMOBILE_H
#define BATMOBILE_LIBRARY_BATMOBILE_H

#include <Arduino.h>
#include <CircuitOS.h>
#include <Display/Display.h>
#include <WiFi.h>
#include <SPIFFS.h>
#include <Loop/LoopManager.h>

class BatmobileImpl {
public:
	BatmobileImpl();
	void begin();

	Display* getDisplay();

private:
	Display display;
};

extern BatmobileImpl Batmobile;


#endif //BATMOBILE_LIBRARY_BATMOBILE_H
