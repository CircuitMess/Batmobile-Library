#ifndef BATMOBILE_LIBRARY_S3INTERFACE_H
#define BATMOBILE_LIBRARY_S3INTERFACE_H

#include <Arduino.h>
#include <SPI.h>
#include <DriveMode.h>
#include <memory>
#include <FS.h>

class S3Interface {
private:
	// TODO: use correct model
	struct MotorInfo {};

	struct CamFrame {
		void* data;
		size_t size;
	};

	struct DriveInfo {
		DriveMode mode;
		MotorInfo motors;
		CamFrame frame;
	};

public:
	void begin();

	void setMode(DriveMode mode);
	std::unique_ptr<DriveInfo> getFrame();

private:

	DriveMode state = Idle;

};


#endif //BATMOBILE_LIBRARY_S3INTERFACE_H
