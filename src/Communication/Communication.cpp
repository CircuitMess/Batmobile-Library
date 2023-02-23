#include "Communication.h"
#include <WiFi.h>
#include <iterator>

Communication Com;

Communication::Communication(){}

Communication::~Communication(){}

void Communication::begin(){
	infoSender.begin();
}

bool Communication::isWiFiConnected(){
	return WiFi.status() == WL_CONNECTED;
}

void Communication::sendBattery(uint8_t percent, bool charging){
	if(percent > 100) return;
	if(charging) percent = UINT8_MAX;
	ControlPacket packet{ ComType::Battery, percent };
	sendPacket(packet);
}

void Communication::sendSignalStrength(uint8_t percent){
	ControlPacket packet{ ComType::SignalStrength, percent };
	sendPacket(packet);
}

void Communication::sendShutdownAck(){
	ControlPacket packet{ ComType::ShutdownAck, 0 };
	sendPacket(packet);
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
	for(const auto& entry: listeners){
		removeListener(entry.first, listener);
	}
}

void Communication::processPacket(const ControlPacket& packet){
	switch(packet.type){
		case ComType::BallHue:
			for(auto& listener: listeners[ComType::BallHue]){
				listener->onBallHue(packet.data);
			}
			break;
		case ComType::Boost:
			for(auto& listener: listeners[ComType::Boost]){
				listener->onBoost(packet.data);
			}
			break;
		case ComType::DriveDir:
			for(auto& listener: listeners[ComType::DriveDir]){
				listener->onDriveDir(packet.data & 0b1111, packet.data >> 4);
			}
			break;
		case ComType::DriveMode:
			for(auto& listener: listeners[ComType::DriveMode]){
				listener->onDriveMode((DriveMode) packet.data);
			}
			break;
		case ComType::DriveSpeed:
			for(auto& listener: listeners[ComType::DriveSpeed]){
				listener->onDriveSpeed(packet.data);
			}
			break;
		case ComType::Honk:
			for(auto& listener: listeners[ComType::Honk]){
				listener->onHonk();
			}
			break;
		case ComType::Volume:
			for(auto& listener: listeners[ComType::Volume]){
				listener->onVolume(packet.data);
			}
			break;
		case ComType::Shutdown:
			for(auto& listener: listeners[ComType::Shutdown]){
				listener->onShutdown();
			}
			break;
		case ComType::SettingsSound:
			for(auto& listener: listeners[ComType::SettingsSound]){
				listener->onSettingsSound();
			}
			break;
		case ComType::Disconnect:
			for(auto& listener: listeners[ComType::Disconnect]){
				listener->onDisconnectRequest();
			}
			break;
		case ComType::Headlights:
			for(auto& listener: listeners[ComType::Headlights]){
				listener->onHeadlights(packet.data);
			}
			break;
		case ComType::Taillights:
			for(auto& listener: listeners[ComType::Taillights]){
				listener->onTaillights(packet.data);
			}
			break;
		case ComType::Underlights:
			for(auto& listener: listeners[ComType::Underlights]){
				listener->onUnderlights(packet.data);
			}
			break;
		case ComType::SoundEffect:
			for(auto& listener: listeners[ComType::SoundEffect]){
				listener->onSoundEffect(packet.data);
			}
			break;
		case ComType::Dance:
			for(auto& listener: listeners[ComType::Dance]){
				listener->onDance((DanceType) packet.data);
			}
			break;
		case ComType::OverrideSound:
			for(auto& listener: listeners[ComType::OverrideSound]){
				listener->onOverrideSound(packet.data);
			}
			break;
		case ComType::MotorsTimeout:
			for(auto& listener: listeners[ComType::MotorsTimeout]){
				listener->onMotorsTimeout(packet.data);
			}
			break;
		case ComType::MotorsTimeoutClear:
			for(auto& listener: listeners[ComType::MotorsTimeoutClear]){
				listener->onMotorsTimeoutClear();
			}
			break;
		case ComType::IdleSounds:
			for(auto& listener: listeners[ComType::IdleSounds]){
				listener->onIdleSounds(packet.data);
			}
			break;
		default:
			break;
	}
}


