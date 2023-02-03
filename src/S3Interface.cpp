#include "S3Interface.h"
#include "Pins.hpp"

#define COMM_ID (0x1)
#define DATA_ID (0x15)

#define COMM_MODE (0x2)
#define COMM_FRAME (0x3)
#define COMM_PROXI (0x4)
#define COMM_FRAME_GRAY (0x5)
#define COMM_HUE (0x6)

S3Interface::S3Interface() : SPI(VSPI), SS(20000000, SPI_MSBFIRST, SPI_MODE3), recvBuf((uint8_t*) malloc(MaxFrameSize)), recvRing(MaxFrameSize){

}

bool S3Interface::begin(){
	reset();

	send(COMM_ID);

	return recv() == DATA_ID;
}

void S3Interface::initPins(){
	for(auto pin : { S3_MISO, S3_CLK, S3_CS, S3_RST }){
		pinMode(pin, OUTPUT);
		digitalWrite(pin, HIGH);
	}

	pinMode(S3_INT, INPUT_PULLDOWN);

	// S3 GPIO2 is input-low during boot. The line on the WROOM side should be high-impedance while the S3 is booting
	pinMode(S3_MOSI, INPUT);
}

void S3Interface::reset(){
	SPI.end(); // free SPI pins so MOSI line can be put into high-impedance (input mode)
	initPins();

	digitalWrite(S3_RST, LOW);
	delay(5);

	digitalWrite(S3_RST, HIGH);
	delay(5);

	waitReady();

	pinMode(S3_MOSI, OUTPUT);
	SPI.begin(S3_CLK, S3_MISO, S3_MOSI, S3_CS);
	SPI.setHwCs(false);
}

void S3Interface::setMode(DriveMode mode){
	send(COMM_MODE, (uint8_t) mode);
}

std::unique_ptr<DriveInfo> S3Interface::getFrame(){
	send(COMM_FRAME);
	waitReady();

	SPITransaction trans(SPI, SS);

	size_t size;
	trans.recv(&size, sizeof(size));

	size_t dataSize = size;
	if(dataSize%4 != 0){
		dataSize += 4 - (dataSize%4);
	}

	if(dataSize > MaxFrameSize){
		// Clear S3's send buffer
		trans.clear(dataSize);
		return { };
	}

	if(size == 0){
		return { };
	}

	trans.recv(recvBuf.get(), dataSize);
	recvRing.clear();
	recvRing.write(static_cast<uint8_t*>(recvBuf.get()), size);

	return DriveInfo::deserialize(recvRing, size);
}

void S3Interface::getFrameGray(uint8_t* buffer){
	send(COMM_FRAME_GRAY);
	waitReady();

	SPITransaction trans(SPI, SS);

	trans.recv(buffer, 160*120);
}

ProximityData S3Interface::getProximity(){
	send(COMM_PROXI);
	waitReady();

	uint8_t data[8];
	recvData(data, 8);

	ProximityData proximityData {};
	memcpy(&proximityData, data, 6);

	return proximityData;
}

void S3Interface::setHue(uint8_t hue){
	send(COMM_HUE, hue);
}

void S3Interface::send(uint8_t byte1, uint8_t byte2, uint8_t byte3, uint8_t byte4){
	uint8_t bytes[4] = { byte1, byte2, byte3, byte4 };
	sendData(bytes, 4);
}

void S3Interface::sendData(const void* data, size_t size){
	waitReady();

	SPITransaction trans(SPI, SS);
	trans.send(data, size);
}

uint8_t S3Interface::recv(){
	uint8_t byte[4];
	recvData(byte, 4);
	return byte[0];
}

void S3Interface::recvData(void* data, size_t count){
	waitReady();

	SPITransaction trans(SPI, SS);
	trans.recv(data, count);
}

void S3Interface::clearRecv(size_t size){
	waitReady();

	SPITransaction trans(SPI, SS);
	trans.clear(size);
}

void S3Interface::waitReady(){
	delayMicroseconds(50);
	while(digitalRead(S3_INT) == LOW){
		delayMicroseconds(50);
	}
}

S3Interface::SPITransaction::SPITransaction(SPIClass& spi, const SPISettings SS) : SPI(spi){
	SPI.beginTransaction(SS);
	digitalWrite(S3_CS, LOW);
}

S3Interface::SPITransaction::~SPITransaction(){
	end();
}

void S3Interface::SPITransaction::send(const void* data, size_t size){
	SPI.transferBytes((uint8_t*) data, nullptr, size);
}

void S3Interface::SPITransaction::recv(void* data, size_t size){
	SPI.transferBytes(nullptr, static_cast<uint8_t*>(data), size);
}

void S3Interface::SPITransaction::clear(size_t size){
	SPI.transferBytes(nullptr, nullptr, size);
}

void S3Interface::SPITransaction::end(){
	if(!active) return;
	active = false;
	digitalWrite(S3_CS, HIGH);
	SPI.endTransaction();
}
