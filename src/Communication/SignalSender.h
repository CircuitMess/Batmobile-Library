#ifndef BATMOBILE_LIBRARY_SIGNALSENDER_H
#define BATMOBILE_LIBRARY_SIGNALSENDER_H


#include <Loop/LoopListener.h>

class SignalSender {
public:
	[[nodiscard]] static uint8_t getStrength();

private:
	static constexpr int8_t maxSS = -50;
	static constexpr int8_t minSS = -90;
};


#endif //BATMOBILE_LIBRARY_SIGNALSENDER_H
