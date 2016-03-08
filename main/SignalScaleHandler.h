#ifndef SIGNAL_SCALE_H
#define SIGNAL_SCALE_H

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif

#include <ILI9341_t3.h>
#include "SignalScaleActionsEnum.h"
#include "ADCHandler.h"

class SignalScaleHandler
{
private:
	ILI9341_t3* tft;
	ADCHandler* adc;
	uint16_t frequency;
	uint16_t frequencyLowerLimit;
	uint32_t frequencyUpperLimit;
	uint16_t frequencyStep;

	int16_t offset;
	int16_t offsetLowerLimit;
	uint16_t offsetUpperLimit;
	uint16_t offsetStep;

	uint16_t amplitudeScale;
	uint16_t amplitudeLowerLimit;
	uint16_t amplitudeUpperLimit;
	uint16_t amplitudeScaleStep;

	String decreaseOffset();
	String increaseOffset();
	String decreaseFrequency();
	String increaseFrequency();
	String decreaseAmplitude();
	String increaseAmplitude();

public:
	SignalScaleHandler(ILI9341_t3 * tft, ADCHandler * adc);
	uint16_t adjustAmplitude(float amplitudeReading);
	void begin();
	String action(SignalScaleEnum action);
};

#endif

