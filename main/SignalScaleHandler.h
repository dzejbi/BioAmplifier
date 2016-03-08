#ifndef SIGNAL_SCALE_H
#define SIGNAL_SCALE_H

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif

#include <ILI9341_t3.h>
#include "SignalScaleActionsEnum.h"

class SignalScaleHandler
{
private:
	ILI9341_t3* tft;
	uint16_t frequencyScale;
	uint16_t frequencyLowerLimit;
	uint32_t frequencyUpperLimit;
	uint16_t frequencyScaleStep;

	int16_t offset;
	int16_t offsetLowerLimit;
	uint16_t offsetUpperLimit;
	uint16_t offsetStep;

	uint16_t amplitudeScale;
	uint16_t amplitudeLowerLimit;
	uint16_t amplitudeUpperLimit;
	uint16_t amplitudeScaleStep;

	void decreaseOffset();
	void increaseOffset();
	void decreaseFrequency();
	void increaseFrequency();
	void decreaseAmplitude();
	void increaseAmplitude();
	//TODO return enumem StateMachnieEnum i  stringiem Info
	void drawLimitInfo();

public:
	SignalScaleHandler(ILI9341_t3 * tft);
	uint16_t adjustAmplitude(float amplitudeReading);
	void measurmentDelay();
	void begin();
	void action(SignalScaleEnum action);
};

#endif

