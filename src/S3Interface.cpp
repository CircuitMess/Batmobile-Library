#include "S3Interface.h"

void S3Interface::begin(){

}

void S3Interface::setMode(DriveMode mode){
	state = mode;
}

std::unique_ptr<DriveInfo> S3Interface::getFrame(){
	auto info = std::make_unique<DriveInfo>();
	info->mode = state;

	if(state == DriveMode::Idle) return info;

	extern const uint8_t Frame[];
	extern const size_t FrameSize;

	info->frame.size = FrameSize;
	info->frame.data = malloc(FrameSize);
	memcpy(info->frame.data, Frame, FrameSize);

	return info;
}
