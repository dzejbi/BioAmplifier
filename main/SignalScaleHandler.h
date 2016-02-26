#ifndef SIGNAL_SCALE_H
#define SIGNAL_SCALE_H

#include<WProgram.h>

class SignalScaleHandler
{
private:
	uint16_t frequencyScale;
	uint16_t frequencyLowerLimit;
	uint16_t frequencyUpperLimit;
	uint16_t frequencyScaleStep;
	int16_t offset;
	int16_t offsetLowerLimit;
	uint16_t offsetUpperLimit;
	uint16_t offsetStep;
	float amplitudeScale;
	float amplitudeLowerLimit;
	float amplitudeUpperLimit;
	float amplitudeScaleStep;

public:
	SignalScaleHandler();
	void decreaseOffset();
	void increaseOffset();
	void decreaseFrequency();
	void increaseFrequency();
	void decreaseAmplitude();
	void increaseAmplitude();
	void throwLimitInfo();
	uint16_t adjustAmplitude(uint16_t amplitudeReading);
	void measurmentDelay();
	void begin();
};

#endif

