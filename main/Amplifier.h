// Amplifier.h

#ifndef _AMPLIFIER_h
#define _AMPLIFIER_h

#include <SPI.h>

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

class Amplifier {

public:
	void setGain(int RGain);
	void begin();

private:
	void setResistance(int adress, int value);
	const int CS_Amplifier = 10;
	int R;
};

#endif

