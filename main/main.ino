

#include "ADCHandler.h"
#include <ADC.h>
#include <SPI.h>

//Objects initialization


ADCHandler* adc = new ADCHandler();


String buffer = "";
int count = 0;


void setup() {
	Serial.begin(9600);
	while(!Serial);
	adc->begin();
	Serial.println("Setup done");
	adc->updatePDB(5000);
}

void loop() {
	
		if (adc->flag) {
			buffer += String(adc->getNewValue(), 3) ;
			buffer += ",";
			count++;
		}

		if (count == 200) {
			Serial.print(buffer);
			buffer = "";
			count = 0;
		}

}

