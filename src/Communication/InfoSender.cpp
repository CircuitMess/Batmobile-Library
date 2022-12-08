#include "InfoSender.h"
#include "Communication.h"
#include "../Batmobile.h"
#include "SignalSender.h"
#include <Loop/LoopManager.h>

void InfoSender::begin(){
	LoopManager::addListener(this);
}

InfoSender::~InfoSender(){
	LoopManager::removeListener(this);
}

void InfoSender::loop(uint micros){
	batteryTime += micros;
	signalTime += micros;

	if(batteryTime >= batteryInterval){
		batteryTime = 0;
		Com.sendBattery(Battery.getPercentage(), Battery.charging());
	}

	if(signalTime >= signalInterval){
		signalTime = 0;
		Com.sendSignalStrength(SignalSender::getStrength());
	}
}
