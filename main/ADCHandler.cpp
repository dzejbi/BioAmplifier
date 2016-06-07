// 
// 
// 

#include "ADCHandler.h"

extern ADCHandler* adc;

void ADCHandler::begin()
{
	pValueVolts = &valueVolts;
	analogPin = A2;
	resolution = 12;
	freq = 1;
	flag = false;
	referenceVoltage = 3.3;

	setAveraging(32, ADC_1);
	setResolution(resolution);
	setConversionSpeed(ADC_HIGH_SPEED, ADC_1);
	setSamplingSpeed(ADC_HIGH_SPEED, ADC_1);
	enableInterrupts(ADC_1);
	enableCompare(getMaxValue(ADC_1), 0, ADC_1);
	analogRead(analogPin, ADC_1); 

	adc1->stopPDB();
	adc1->startPDB(freq);
	Serial.println("ADC setup complete");
}

void ADCHandler::stop()
{
	adc1->stopPDB();
}

void ADCHandler::updatePDB(uint16_t frequency)
{	
	setFrequency(frequency);
	adc1->stopPDB();
	adc1->startPDB(freq);
	Serial.print("PDB frequency is set to ");
	Serial.println(freq);
}


void ADCHandler::convertToVolts()
{
	valueVolts = double((value*referenceVoltage) / getMaxValue(ADC_1));
}


volatile float ADCHandler::getNewValue()
{
	return value;
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

void adc1_isr()
{
	adc->flag = true;
	adc->value = (uint16_t)adc->analogReadContinuous(ADC_1);
}


void pdb_isr(void) {
	PDB0_SC &= ~PDB_SC_PDBIF;
}
