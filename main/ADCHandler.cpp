// 
// 
// 

#include "ADCHandler.h"

//Debug variables
extern unsigned long mic;
extern unsigned long mic2;

void ADCHandler::convertToVolts()
{
	valueVolts = float((value*referenceVoltage) /getMaxValue(ADC_1));
}


void ADCHandler::start()
{
	pValueVolts = &valueVolts;
	analogPin = A2;
	resolution = 12;
	freq = 1;
	flag = false;
	referenceVoltage = 3.3;

	setAveraging(16, ADC_1);
	setResolution(resolution);
	setConversionSpeed(ADC_LOW_SPEED, ADC_1);
	setSamplingSpeed(ADC_LOW_SPEED, ADC_1);
	enableInterrupts(ADC_1);
	enableCompare(getMaxValue(ADC_1), 0, ADC_1);
	analogRead(analogPin, ADC_1); // call this to setup everything before the pdb starts

	adc1->stopPDB();
	adc1->startPDB(freq);
}

void ADCHandler::stop()
{
	adc1->stopPDB();
}

float* ADCHandler::getNewValue()
{	
	convertToVolts();
	if (flag) {
		flag = false;
		return pValueVolts;
	}
	else {
		return nullptr;
	}
}

void ADCHandler::setFrequency(uint16_t freq)
{
	this->freq = freq;
}

void ADCHandler::setResolution(char resolution)
{
	this->resolution = resolution;
}

void ADCHandler::setAnalogPin(uint8_t pin)
{
	this->analogPin = pin;
}

extern ADCHandler* adc;

void adc1_isr()
{
	adc->flag = true;
	adc->value = (uint16_t)adc->analogReadContinuous(ADC_1);
	mic2 = micros() - mic;
	Serial.println(mic2);
	mic = micros();
}


void pdb_isr(void) {
	PDB0_SC &= ~PDB_SC_PDBIF;
}
