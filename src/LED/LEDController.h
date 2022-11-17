#ifndef BATMOBILE_FIRMWARE_LEDCONTROLLER_H
#define BATMOBILE_FIRMWARE_LEDCONTROLLER_H

#include <Loop/LoopListener.h>
#include <glm.h>
#include <Arduino.h>
#include <vector>

template<typename T>
class LEDController : public LoopListener {
public:
	void begin();

	void setValue(T color);
	void clear();
	void setSolid(T color);
	void blink(T color);
	void blinkTwice(T color);
	void blinkContinuous(T color);

	virtual void write(T val) = 0;

	void loop(uint micros) final;

protected:
	virtual void init() = 0;

private:
	enum {
		Solid, Once, Twice, Continuous
	} LEDstate = Solid;

	T LEDcolor{};

	T blinkColor{};
	uint32_t blinkStartTime = 0;
	bool blinkState = false;
	static constexpr uint32_t blinkDuration = 100; //[ms]
	static constexpr uint32_t blinkContinuousDuration = 500; //[ms]
};

class SingleLEDController : public LEDController<uint8_t> {
public:
	SingleLEDController(uint8_t pin, uint8_t channel);
	void write(uint8_t val) override;

private:
	void init() override;
	const uint8_t pin;
	const uint8_t channel;
};

class RGBLEDController : public LEDController<glm::vec<3, uint8_t>> {
public:
	RGBLEDController(std::initializer_list<uint8_t> pins, std::initializer_list<uint8_t> channels);
	void write(glm::vec<3, uint8_t> val) override;

private:
	void init() override;
	const std::vector<uint8_t> pins;
	const std::vector<uint8_t> channels;
};


#endif //BATMOBILE_FIRMWARE_LEDCONTROLLER_H
