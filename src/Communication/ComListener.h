#ifndef BATMOBILE_LIBRARY_COMLISTENER_H
#define BATMOBILE_LIBRARY_COMLISTENER_H

#include <Arduino.h>
#include <DriveMode.h>
#include <DriveDirection.h>

class ComListener {
public:
	/**
	 * @param hue HSV format hue divided by 2 [0-180]
	 */
	virtual void onBallHue(uint8_t hue);
	virtual void onBoost(bool boost);
	virtual void onDriveDir(DriveDirection dir);
	virtual void onDriveMode(DriveMode mode);
	/**
	 * @param speed [0-100]
	 */
	virtual void onDriveSpeed(uint8_t speed);
	virtual void onHonk();
	/**
	 * @param volume [0-100]
	 */
	virtual void onVolume(uint8_t volume);
};


#endif //BATMOBILE_LIBRARY_COMLISTENER_H
