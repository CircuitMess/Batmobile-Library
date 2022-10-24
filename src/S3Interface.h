#ifndef BATMOBILE_LIBRARY_S3INTERFACE_H
#define BATMOBILE_LIBRARY_S3INTERFACE_H

#include <Arduino.h>
#include <SPI.h>
#include <DriveInfo.h>
#include <memory>
#include <FS.h>

class S3Interface {
public:
	void begin();

	void setMode(DriveMode mode);
	std::unique_ptr<DriveInfo> getFrame();

private:

	DriveMode state = DriveMode::Idle;

};


#endif //BATMOBILE_LIBRARY_S3INTERFACE_H
