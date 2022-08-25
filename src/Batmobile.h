#ifndef BATMOBILE_LIBRARY_BATMOBILE_H
#define BATMOBILE_LIBRARY_BATMOBILE_H

#include <Display/Display.h>
#include <Input/InputShift.h>
#include "Pins.hpp"
#include <Audio/Piezo.h>

class BatmobileImpl {
public:
	BatmobileImpl();
	void begin();

	Display* getDisplay();
	Input* getInput();

private:
	Display display;
	InputShift input;
};

extern BatmobileImpl Batmobile;


#endif //BATMOBILE_LIBRARY_BATMOBILE_H
