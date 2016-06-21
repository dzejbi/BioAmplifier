// Settings.h

#ifndef _SETTINGS_h
#define _SETTINGS_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include <EEPROM.h>

struct Settings{
	int R1, R2, R3, R4;
	int RGain;
	int bufferSizeSave;
	int frequency;
	int resolution;
	int averaging;
	int samplingSpeed;
	int bufferSize;
};

class SettingsHandler {
public:
	void save(Settings settings);
	Settings load();
	Settings reciveData();
};

#endif

