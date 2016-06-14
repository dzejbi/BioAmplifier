// 
// 
// 

#include "Filter.h"

void Filter::setFrequency(Settings s)
{
	R1 = s.R1;
	R2 = s.R2;
	R3 = s.R3;
	R4 = s.R4;

	setPotValues();
}

void Filter::begin()
{
	SPI.begin();
	
	R1 = 50;
	R2 = 50;
	R3 = 50;
	R4 = 50;

	pinMode(CS_Filter, OUTPUT);
}

void Filter::setResistance(int adress, int value)
{
	digitalWrite(CS_Filter, LOW);
	SPI.transfer(adress);
	SPI.transfer(value);
	digitalWrite(CS_Filter, HIGH);
}

void Filter::setPotValues()
{
	setResistance(0, R3);
	setResistance(1, R2);
	setResistance(2, R4);
	setResistance(3, R1);

}
