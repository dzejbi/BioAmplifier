#include "SignalScaleHandler.h"

SignalScaleHandler::SignalScaleHandler(ILI9341_t3* tft)
{
	this->tft = tft;
}

void SignalScaleHandler::decreaseOffset(){

	if (offset - offsetStep > offsetLowerLimit) {
		offset -= offsetStep;
	}
	else {
		drawLimitInfo();
	}
}

void SignalScaleHandler::increaseOffset() {

	if (offset + offsetStep < offsetUpperLimit) {
		offset += offsetStep;
	}
	else {
		drawLimitInfo();
	}
}

void SignalScaleHandler::decreaseFrequency() {

	if (frequencyScale - frequencyScaleStep > frequencyLowerLimit) {
		frequencyScale -= frequencyScaleStep;
	}
	else {
		drawLimitInfo();
	}
}

void SignalScaleHandler::increaseFrequency() {

	if (frequencyScale + frequencyScaleStep < frequencyUpperLimit) {
		frequencyScale += frequencyScaleStep;
	}
	else {
		drawLimitInfo();
	}
}

void SignalScaleHandler::decreaseAmplitude() {

	if (amplitudeScale + amplitudeScaleStep < amplitudeUpperLimit) {
		amplitudeScale += amplitudeScaleStep;
	}
	else {
		drawLimitInfo();
	}
}

void SignalScaleHandler::increaseAmplitude() {

	if (amplitudeScale - amplitudeScaleStep > amplitudeLowerLimit) {
		amplitudeScale -= amplitudeScaleStep;
	}
	else {
		drawLimitInfo();
	}
}

void SignalScaleHandler::drawLimitInfo()
{
	tft->fillScreen(ILI9341_BLACK);
	tft->setCursor(50, 105);
	tft->setTextColor(ILI9341_RED);
	tft->setTextSize(3);
	tft->print("LIMIT REACHED");
	delay(1000);
}

uint16_t SignalScaleHandler::adjustAmplitude(float amplitudeReading)
{
	return (amplitudeReading * amplitudeScale) - offset;
}

void SignalScaleHandler::measurmentDelay()
{
	delayMicroseconds(frequencyScale);
}

void SignalScaleHandler::begin() {
	this->frequencyScale = 50000;
	this->amplitudeScale = 100;
	this->offset = 0;
	this->amplitudeScaleStep = 5;
	this->frequencyScaleStep = 1000;
	this->offsetStep = 100;
	this->frequencyLowerLimit = 0;
	this->frequencyUpperLimit = 1000000;
	this->offsetLowerLimit = -500;
	this->offsetUpperLimit = 1000;
	this->amplitudeLowerLimit = 1;
	this->amplitudeUpperLimit = 100;
}

void SignalScaleHandler::action(SignalScaleEnum action)
{
	switch (action)
	{
	case INCREASE_AMPLITUDE:
		increaseAmplitude();
		break;
	case DECREASE_AMPLITUDE:
		decreaseAmplitude();
		break;
	case INCREASE_FREQUENCY:
		increaseFrequency();
		break;
	case DECREASE_FREQUENCY:
		decreaseFrequency();
		break;
	case INCREASE_OFFSET:
		increaseOffset();
		break;
	case DECREASE_OFFSET:
		decreaseOffset();
		break;
	default:
		break;
	}
}
