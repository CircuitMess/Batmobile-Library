#include "Communication.h"
#include <WiFi.h>
#include <iterator>

Communication Com;

Communication::Communication(){}

Communication::~Communication(){}

bool Communication::isWiFiConnected(){
	return WiFi.status() == WL_CONNECTED;
}

void Communication::sendBattery(uint8_t percent){

}

void Communication::sendShutdown(std::function<void()> ackCallback){

}

void Communication::addListener(ComType type, ComListener* listener){
	listeners[type].insert(listener);
}

void Communication::addListener(std::initializer_list<ComType> types, ComListener* listener){
	for(auto type: types){
		addListener(type, listener);
	}
}

void Communication::removeListener(ComType type, ComListener* listener){
	listeners[type].erase(listener);
}

void Communication::removeListener(ComListener* listener){
	for(auto entry: listeners){
		entry.second.erase(listener);
	}
}

void Communication::processPacket(const ControlPacket& packet){
	switch(packet.type){
		case ComType::BallHue:
			for(auto& listener: listeners[ComType::BallHue]){
				listener->onBallHue();
			}
			break;
		case ComType::Boost:
			for(auto& listener: listeners[ComType::Boost]){
				listener->onBoost();
			}
			break;
		case ComType::DriveDir:
			for(auto& listener: listeners[ComType::DriveDir]){
				listener->onDriveDir();
			}
			break;
		case ComType::DriveMode:
			for(auto& listener: listeners[ComType::DriveMode]){
				listener->onDriveMode();
			}
			break;
		case ComType::DriveSpeed:
			for(auto& listener: listeners[ComType::DriveSpeed]){
				listener->onDriveSpeed();
			}
			break;
		case ComType::Honk:
			for(auto& listener: listeners[ComType::Honk]){
				listener->onHonk();
			}
			break;
		case ComType::Volume:
			for(auto& listener: listeners[ComType::Volume]){
				listener->onVolume();
			}
			break;
	}
}


