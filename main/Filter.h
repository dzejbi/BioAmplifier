// Filter.h

#ifndef _FILTER_h
#define _FILTER_h

#include <SPI.h>

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "Settings.h"

class Filter {

public:
	void setFrequency(Settings s);
	void begin();

private:
	int R1, R2, R3, R4;
	const int CS_Filter = 9;
	void setResistance(int adress, int value);
	void setPotValues();

};

#endif

