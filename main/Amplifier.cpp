// 
// 
// 

#include "Amplifier.h"

void Amplifier::setGain(int RGain)
{
	R = RGain;
	setResistance(0, R);
}

void Amplifier::begin()
{
	SPI.begin();
	R = 200;
	pinMode(CS_Amplifier, OUTPUT);

}

void Amplifier::setResistance(int adress, int value)
{
	digitalWrite(CS_Amplifier, LOW);
	SPI.transfer(adress);
	SPI.transfer(value);
	digitalWrite(CS_Amplifier, HIGH);
}