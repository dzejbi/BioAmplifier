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
	volatile float valueVolts;
	volatile float *pValueVolts;
	void convertToVolts();
public:
	bool volatile flag;

	void begin();
	void stop();
	void updatePDB(uint16_t resolution);

	uint16_t value;
	volatile float* getNewValue();

	void setFrequency(uint16_t freq);
	void setResolution(char resolution);
	void setAnalogPin(uint8_t pin);
};

#endif

