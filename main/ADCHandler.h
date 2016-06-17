// ADCHandler.h

#ifndef _ADCHANDLER_h
#define _ADCHANDLER_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include <ADC.h>

class ADCHandler : public ADC
{
private:
	uint8_t analogPin;
	char resolution;
	uint16_t frequency;
	uint16_t value;
	void update();

public:
	bool volatile flag;
	void begin();
	void stop();

	void setNewValue(uint16_t value);
	volatile uint16_t getNewValue();

	void setFrequency(uint16_t freq);
	void setResolutionADC(char resolution);
	void setAnalogPin(uint8_t pin);
};

#endif

