// 
// 
// 

#include "ADCHandler.h"

extern ADCHandler* adc;

void ADCHandler::update()
{
	setAveraging(averaging, ADC_1);
	setResolution(resolution, ADC_1);
	setConversionSpeed(ADC_HIGH_SPEED, ADC_1);
	setSamplingSpeed(sampling, ADC_1);
	enableInterrupts(ADC_1);
	enableCompare(getMaxValue(ADC_1), 0, ADC_1);
	analogRead(analogPin, ADC_1);

	adc1->stopPDB();
	adc1->startPDB(frequency);
}

void ADCHandler::begin()
{
	analogPin = A2;
	resolution = 12;
	frequency = 1;
	sampling = 2;
	averaging = 32;
	flag = false;
	update();
}

void ADCHandler::stop()
{
	adc1->stopPDB();
}


void ADCHandler::setFrequency(uint16_t frequency)
{	
	this->frequency = frequency;
	adc1->stopPDB();
	adc1->startPDB(frequency);
}


void ADCHandler::setNewValue(uint16_t value)
{
	this->value = value;
}

volatile uint16_t ADCHandler::getNewValue()
{
	flag = false;
	return value;
}


void ADCHandler::setResolutionADC(char resolution)
{
	this->resolution = resolution;
	this->update();
}

void ADCHandler::setAveragingADC(char averaging)
{
	this->averaging = averaging;
	this->update();
}

void ADCHandler::setSamplingADC(char sampling)
{
	this->sampling = sampling;
	this->update();
}

void ADCHandler::setAnalogPin(uint8_t pin)
{
	this->analogPin = pin;
	this->update();
}

void adc1_isr()
{
	adc->flag = true;
	adc->setNewValue((uint16_t)adc->analogReadContinuous(ADC_1));
}


void pdb_isr(void) {
	PDB0_SC &= ~PDB_SC_PDBIF;
}
