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
	float referenceVoltage;
	uint8_t analogPin;
	char resolution;
	uint16_t freq;
	float valueVolts;
	float *pValueVolts;
	void convertToVolts();
public:
	uint16_t value;
	bool volatile flag;
	void start();
	void stop();
	float* getNewValue();
	void setFrequency(uint16_t freq);
	void setResolution(char resolution);
	void setAnalogPin(uint8_t pin);
};

#endif

