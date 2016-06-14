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
