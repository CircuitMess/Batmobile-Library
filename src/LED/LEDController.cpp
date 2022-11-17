#include "LEDController.h"
#include <Loop/LoopManager.h>

static constexpr uint PWMFreq = 5000;
static constexpr uint8_t PWMResolution = 8;


template<typename T>
void LEDController<T>::begin(){
	init();
	LoopManager::addListener(this);

}

template<typename T>
void LEDController<T>::setValue(T color){

	LEDcolor = color;

	if(LEDstate == Solid){
		write(color);
	}
}

template<typename T>
void LEDController<T>::clear(){
	LEDstate = Solid;
	blinkState = false;
	blinkColor = T();
	blinkStartTime = 0;
	glm::vec3 vec;
	LEDcolor = T();

	write(LEDcolor);

}

template<typename T>
void LEDController<T>::setSolid(T color){
	LEDstate = Solid;
	setValue(color);
}

template<typename T>
void LEDController<T>::blink(T color){

	LEDstate = Once;
	blinkColor = color;
	blinkStartTime = millis();
	blinkState = true;

	write(color);
}

template<typename T>
void LEDController<T>::blinkTwice(T color){
	blink(color);
	LEDstate = Twice;
}

template<typename T>
void LEDController<T>::blinkContinuous(T color){
	blink(color);
	LEDstate = Continuous;
}

template<typename T>
void LEDController<T>::loop(uint micros){
	if(LEDstate == Solid) return;
	if(millis() - blinkStartTime < blinkDuration) return;

	bool push = false;
	T pushVal{};

	if(LEDstate == Continuous){
		if(millis() - blinkStartTime < blinkContinuousDuration) return;

		blinkState = !blinkState;
		blinkStartTime = millis();
		pushVal = blinkState ? blinkColor : T();
		push = true;
	}else if(LEDstate == Twice && blinkState){
		blinkState = false;
		blinkStartTime = millis();
		pushVal = T();
		push = true;
	}else if(LEDstate == Twice && !blinkState){
		blinkState = true;
		blinkStartTime = millis();
		LEDstate = Once;
		pushVal = blinkColor;
		push = true;
	}else if(LEDstate == Once){
		blinkState = false;
		blinkStartTime = 0;
		blinkColor = T();
		LEDstate = Solid;
		pushVal = LEDcolor;
		push = true;
	}

	if(push){
		write(pushVal);
	}
}

template
class LEDController<uint8_t>;

template
class LEDController<glm::vec<3, uint8_t>>;

SingleLEDController::SingleLEDController(uint8_t pin, uint8_t channel) : pin(pin), channel(channel){

}

void SingleLEDController::init(){
	ledcSetup(channel, PWMFreq, PWMResolution);
	ledcAttachPin(pin, channel);
}

void SingleLEDController::write(uint8_t val){
	ledcWrite(channel, val);
}

RGBLEDController::RGBLEDController(std::initializer_list<uint8_t> pins, std::initializer_list<uint8_t> channels) : pins(pins), channels(channels){}

void RGBLEDController::init(){
	for(uint8_t i = 0; i < 3; i++){
		ledcSetup(channels[i], PWMFreq, PWMResolution);
		ledcAttachPin(pins[i], channels[i]);
	}
}

void RGBLEDController::write(glm::vec<3, uint8_t> val){
	for(uint8_t i = 0; i < 3; i++){
		ledcWrite(channels[i], val[i]);
	}
}
