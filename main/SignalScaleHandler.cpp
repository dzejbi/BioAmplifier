#include "SignalScaleHandler.h"

SignalScaleHandler::SignalScaleHandler(ILI9341_t3* tft, ADCHandler* adc)
{
	this->tft = tft;
	this->adc = adc;
}

String SignalScaleHandler::decreaseOffset() {

	if (offset - offsetStep > offsetLowerLimit) {
		offset -= offsetStep;
		return "OK";
	}
	else {
		return "Limit Reached";
	}
}

String SignalScaleHandler::increaseOffset() {

	if (offset + offsetStep < offsetUpperLimit) {
		offset += offsetStep;
		return "OK";
	}
	else {
		return "Limit Reached";
	}
}

String SignalScaleHandler::decreaseFrequency() {

	if (frequency - frequencyStep > frequencyLowerLimit) {
		frequency -= frequencyStep;
		adc->updatePDB(frequency);
		return "OK";
	}
	else {
		return "Limit Reached";
	}
}

String SignalScaleHandler::increaseFrequency() {

	if (frequency + frequencyStep < frequencyUpperLimit) {
		frequency += frequencyStep;
		adc->updatePDB(frequency);
		return "OK";
	}
	else {
		return "Limit Reached";
	}
}

String SignalScaleHandler::decreaseAmplitude() {

	if (amplitudeScale + amplitudeScaleStep < amplitudeUpperLimit) {
		amplitudeScale += amplitudeScaleStep;
		return "OK";
	}
	else {
		return "Limit Reached";
	}
}

String SignalScaleHandler::increaseAmplitude() {

	if (amplitudeScale - amplitudeScaleStep > amplitudeLowerLimit) {
		amplitudeScale -= amplitudeScaleStep;
		return "OK";
	}
	else {
		return "Limit Reached";
	}
}


uint16_t SignalScaleHandler::adjustAmplitude(float amplitudeReading)
{
	return (amplitudeReading * amplitudeScale) - offset;
}


void SignalScaleHandler::begin() {
	this->frequency = 50;
	this->amplitudeScale = 100;
	this->offset = 0;
	this->amplitudeScaleStep = 5;
	this->frequencyStep = 10;
	this->offsetStep = 100;
	this->frequencyLowerLimit = 1;
	this->frequencyUpperLimit = 5000;
	this->offsetLowerLimit = -500;
	this->offsetUpperLimit = 1000;
	this->amplitudeLowerLimit = 1;
	this->amplitudeUpperLimit = 100;
}

String SignalScaleHandler::action(SignalScaleEnum action)
{
	String info;
	switch (action)
	{
	case INCREASE_AMPLITUDE:
		info = increaseAmplitude();
		break;
	case DECREASE_AMPLITUDE:
		info = decreaseAmplitude();
		break;
	case INCREASE_FREQUENCY:
		info = increaseFrequency();
		break;
	case DECREASE_FREQUENCY:
		 info = decreaseFrequency();
		break;
	case INCREASE_OFFSET:
		info = increaseOffset();
		break;
	case DECREASE_OFFSET:
		info = decreaseOffset();
		break;
	default:
		break;
	}
	return info;
}