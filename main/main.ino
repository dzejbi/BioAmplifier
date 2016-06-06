

#include "ADCHandler.h"
#include <ADC.h>
#include <SPI.h>

//Objects initialization


ADCHandler* adc = new ADCHandler();


//Variables used in State Machine
volatile float* adcValue;
String buffer = "";
int count = 0;


//Debug variables
unsigned long mic;
unsigned long mic2;



void setup() {
	Serial.begin(9600);
	while(!Serial);
	adc->begin();
	Serial.println("Setup done");
	adc->updatePDB(5000);
}

void loop() {
	
		adcValue = adc->getNewValue();
		if (adcValue != nullptr) {
			buffer += String(*adcValue, 3) ;
			buffer += ",";
			count++;
		//	Serial.println(*adcValue,5);
		}
		if (count == 200) {
			Serial.print(buffer);
			buffer = "";
			count = 0;
		}

}

