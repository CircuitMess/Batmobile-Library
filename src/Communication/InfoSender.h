#ifndef BATMOBILE_LIBRARY_INFOSENDER_H
#define BATMOBILE_LIBRARY_INFOSENDER_H

#include <Loop/LoopListener.h>

class InfoSender : private LoopListener {
public:
	void begin();
	~InfoSender() override;

private:
	void loop(uint micros) override;

	uint32_t signalTime = 0, batteryTime = 0;
	static constexpr uint32_t SignalInterval = 2000000;
	static constexpr uint32_t BatteryInterval = 2000000;
};


#endif //BATMOBILE_LIBRARY_INFOSENDER_H
