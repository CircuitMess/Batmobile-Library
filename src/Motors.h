#ifndef BATMOBILE_LIBRARY_MOTORS_H
#define BATMOBILE_LIBRARY_MOTORS_H

#include <Arduino.h>
#include "Pins.hpp"

struct MotorsState {
	int8_t frontRight, frontLeft, backRight, backLeft;
};

class MotorControl {
public:
	void begin();

	void setFR(int8_t value);
	void setFL(int8_t value);
	void setBR(int8_t value);
	void setBL(int8_t value);

	void setAll(MotorsState state);
	MotorsState getAll();

	void stopAll();

private:
	enum Motor : uint8_t { FrontRight, FrontLeft, BackRight, BackLeft };

	static const uint8_t PWM[4];
	static const std::pair<int8_t, int8_t> Pins[4];

	union {
		MotorsState val;
		uint8_t raw[4];
	} state = { .val = { 0, 0, 0, 0 } };

	void setMotor(Motor motor, int8_t value);

};


#endif //BATMOBILE_LIBRARY_MOTORS_H
