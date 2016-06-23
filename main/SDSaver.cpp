// 
// 
// 

#include "SDSaver.h"
extern long m1;

bool SDSaver::begin()
{
	if (sd.begin(chipSelect, SPI_HALF_SPEED)) {
		file.open(name, O_WRITE | O_CREAT | O_AT_END);
		return true;
	}
	else {
		return false;
	}
}

void SDSaver::save(uint16_t &sample)
{	
	file.printField(sample,',');
}

void SDSaver::sync()
{
	file.sync();
}

