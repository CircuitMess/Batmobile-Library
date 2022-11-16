#ifndef BATMOBILE_LIBRARY_SIGNALSENDER_H
#define BATMOBILE_LIBRARY_SIGNALSENDER_H


#include <Loop/LoopListener.h>
#include <esp_wifi_types.h>

class SignalSender : private LoopListener {

public:
	SignalSender();
	~SignalSender() override;

	void begin();

private:
	void loop(uint micros) override;
	uint8_t getStrength();

	uint32_t microCounter = 0;
	static constexpr uint32_t interval = 1000000;
	static constexpr int8_t maxSS = -50;
	static constexpr int8_t minSS = -90;
};


#endif //BATMOBILE_LIBRARY_SIGNALSENDER_H
