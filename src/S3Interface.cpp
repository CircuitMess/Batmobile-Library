#include "S3Interface.h"

void S3Interface::begin(){

}

void S3Interface::setMode(DriveMode mode){
	state = mode;
}

std::unique_ptr<S3Interface::DriveInfo> S3Interface::getFrame(){
	auto info = std::make_unique<DriveInfo>();
	info->mode = state;

	return info;
}
