#ifndef BATMOBILE_LIBRARY_COMMUNICATION_H
#define BATMOBILE_LIBRARY_COMMUNICATION_H

#include <BatCommon.h>
#include <AsyncTCP.h>
#include <ComType.h>
#include "ComListener.h"
#include "SignalSender.h"
#include <map>
#include <set>

class Communication : public CommunicationCommon {
public:
	Communication();
	~Communication() override;

	void begin();

	void sendBattery(uint8_t percent);
	void sendSignalStrength(uint8_t percent);
	void sendShutdown(std::function<void()> ackCallback);

	void addListener(ComType type, ComListener* listener);
    void addListener(std::initializer_list<ComType> type,ComListener* listener);
	void removeListener(ComType type, ComListener* listener);
	void removeListener(ComListener* listener);

private:
	bool isWiFiConnected() override;
	void processPacket(const ControlPacket& packet) override;

	std::map<ComType, std::unordered_set<ComListener*>> listeners;
	SignalSender signalSender;
};

extern Communication Com;

#endif //BATMOBILE_LIBRARY_COMMUNICATION_H
