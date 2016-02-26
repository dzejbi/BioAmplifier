#include "SignalScaleHandler.h"

SignalScaleHandler::SignalScaleHandler()
{
}

void SignalScaleHandler::decreaseOffset(){

	if (offset - offsetStep > offsetLowerLimit) {
		offset -= offsetStep;
	}
	else {
		throwLimitInfo();
	}
}

void SignalScaleHandler::increaseOffset() {

	if (offset + offsetStep < offsetUpperLimit) {
		offset += offsetStep;
	}
	else {
		throwLimitInfo();
	}
}

void SignalScaleHandler::decreaseFrequency() {

	if (frequencyScale - frequencyScaleStep > frequencyLowerLimit) {
		frequencyScale -= frequencyScaleStep;
	}
	else {
		throwLimitInfo();
	}
}

void SignalScaleHandler::increaseFrequency() {

	if (frequencyScale + frequencyScaleStep < frequencyUpperLimit) {
		frequencyScale += frequencyScaleStep;
	}
	else {
		throwLimitInfo();
	}
}

void SignalScaleHandler::decreaseAmplitude() {

	if (amplitudeScale + amplitudeScaleStep < amplitudeLowerLimit) {
		amplitudeScale += amplitudeScaleStep;
	}
	else {
		throwLimitInfo();
	}
}

void SignalScaleHandler::increaseAmplitude() {

	if (amplitudeScale - amplitudeScaleStep > amplitudeUpperLimit) {
		amplitudeScale -= amplitudeScaleStep;
	}
	else {
		throwLimitInfo();
	}
}

void SignalScaleHandler::throwLimitInfo()
{
}

uint16_t SignalScaleHandler::adjustAmplitude(uint16_t amplitudeReading)
{
	return (float(amplitudeReading) / amplitudeScale) - offset;
}

void SignalScaleHandler::measurmentDelay()
{
	delayMicroseconds(frequencyScale);
}

void SignalScaleHandler::begin() {
	this->frequencyScale = 50000;
	this->amplitudeScale = 5;
	this->offset = 0;
	this->amplitudeScaleStep = 0.5;
	this->frequencyScaleStep = 100;
	this->offsetStep = 100;
	this->frequencyLowerLimit = 0;
	this->frequencyUpperLimit = 1000000;
	this->offsetLowerLimit = -500;
	this->offsetUpperLimit = 1000;
	this->amplitudeLowerLimit = 0;
	this->amplitudeUpperLimit = 10;
}