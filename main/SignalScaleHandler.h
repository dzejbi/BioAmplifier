#ifndef SIGNAL_SCALE_H
#define SIGNAL_SCALE_H

#include<WProgram.h>
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
	float amplitudeScale;
	float amplitudeLowerLimit;
	float amplitudeUpperLimit;
	float amplitudeScaleStep;
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
	uint16_t adjustAmplitude(uint16_t amplitudeReading);
	void measurmentDelay();
	void begin();
	void action(SignalScaleEnum action);
};

#endif

