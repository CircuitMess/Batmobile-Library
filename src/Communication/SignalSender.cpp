#include <Loop/LoopManager.h>
#include <esp_wifi.h>
#include "SignalSender.h"
#include "Communication.h"

SignalSender::SignalSender(){}

SignalSender::~SignalSender(){
	LoopManager::removeListener(this);
}

void SignalSender::begin(){
	LoopManager::addListener(this);
}

void SignalSender::loop(uint micros){
	microCounter += micros;
	if(microCounter >= interval){
		microCounter = 0;
		Com.sendSignalStrength(getStrength());
	}
}

uint8_t SignalSender::getStrength(){
	wifi_ap_record_t info;
	uint8_t percentage = 0;

	if(!esp_wifi_sta_get_ap_info(&info)) {
		for (int x = 0; x < 100; x = x + 1){
			if(signalDecibel[x] == info.rssi){
				percentage = signalPercent[x];
				break;
			}
		}
	}
	return percentage;
}
