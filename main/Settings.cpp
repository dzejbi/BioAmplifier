// 
// 
// 

#include "Settings.h"

void SettingsHandler::save(Settings settings)
{	
	EEPROM.put(0, settings);
}

Settings SettingsHandler::load()
{
	Settings temp;
	EEPROM.get(0, temp);
	return temp;
}

Settings SettingsHandler::reciveData() {

	long settings[11];
	Settings temp;

	Serial.setTimeout(1000);

	for (int i = 0; i<11; i++) {
		settings[i] = Serial.parseInt();
	}

	temp.R1 = settings[0];
	temp.R2 = settings[1];
	temp.R3 = settings[2];
	temp.R4 = settings[3];
	temp.RGain = settings[4];
	temp.bufferSizeSave = settings[5];
	temp.frequency = settings[6];
	temp.averaging = settings[7];
	temp.resolution = settings[8];
	temp.samplingSpeed = settings[9];
	temp.bufferSize = settings[10];

	Serial.setTimeout(1);

	return temp;
}
