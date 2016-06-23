
#include <SdVolume.h>
#include <SdStream.h>
#include <SdInfo.h>
#include <SdFile.h>
#include <SdFatUtil.h>
#include <SdFatStructs.h>
#include <SdFatmainpage.h>
#include <SdFatConfig.h>
#include <SdFat.h>
#include <SdBaseFile.h>
#include <Sd2Card.h>
#include <ostream.h>
#include <MinimumSerial.h>
#include <istream.h>
#include <iostream.h>
#include <ios.h>
#include <bufstream.h>
#include <ArduinoStream.h>
#include "SDSaver.h"
#include "Settings.h"
#include "Amplifier.h"
#include "Filter.h"
#include "ADCHandler.h"
#include <ADC.h>
#include <SPI.h>

//Objects initialization


enum StateMachine
{
	CARD_DETECTION,
	LOAD_SETTINGS,
	CHECK_CONNECTION,
	ACQUIRE,
	BIOFEEDBACK_CALC,
	SUPPLY_MOTOR,
	SEND,
	SAVE,
	READ_DATA,
	UPDATE_SETTINGS,
	SAVE_SETTINGS, 
	ACQUIRE_NC,
	SUPPLY_MOTOR_NC,
	CHECK_SERIAL
};


//Debug
long m1 = 0;
long m2 = 0;

volatile StateMachine SM = LOAD_SETTINGS;

ADCHandler* adc = new ADCHandler();
Filter* filter = new Filter();
Amplifier* amplifier = new Amplifier();
SettingsHandler* SH = new SettingsHandler();
SDSaver* SD = new SDSaver();

Settings settings;
String buffer = "";
uint16_t bufferSize = 200;
uint16_t bufferSizeSave = 200;
uint16_t sum = 0;
uint16_t value = 0;
int count = 0;

//TODO which pin?
const int motor = 8;
bool isBiofeedbackOn = false;
float biofeedbackThreshold;
bool isBiofeedback = false;


void setup() {
	pinMode(motor, OUTPUT);
	Serial.begin(9600);
	Serial.setTimeout(1);
	filter->begin();
	amplifier->begin();
	adc->begin();	
}

void loop() {

	switch (SM)
	{
	case LOAD_SETTINGS:
		settings = SH->load();
		filter->setFrequency(settings);
		if (settings.RGain) {
			amplifier->setGain(settings.RGain);
		}
		adc->setFrequency(settings.frequency);
		adc->setResolutionADC(settings.resolution);
		adc->setAveragingADC(settings.averaging);
		adc->setSamplingADC(settings.samplingSpeed);
		bufferSize = settings.bufferSize;
		bufferSizeSave = settings.bufferSizeSave;
		SM = CARD_DETECTION;
		break;

	case CARD_DETECTION:
		if (SD->begin()) {
			SM = ACQUIRE_NC;
		}
		else {
			SM = CHECK_CONNECTION;
		}
		break;

	case CHECK_CONNECTION:
		SM = ACQUIRE;
		while (!Serial)
		break;

	case ACQUIRE:
		if (adc->flag) {
			buffer += String(adc->getNewValue());
			buffer += ",";
			count++;
		}

		if (count == bufferSize) {
			SM = CHECK_SERIAL;
		}
		break;

	case CHECK_SERIAL:
		if (Serial.available()) {
			SM = READ_DATA;
		}
		else {
			SM = SEND;
		}
		break;

	case SEND:
		Serial.println(buffer);
		buffer = "";
		count = 0;
		SM = ACQUIRE;
		break;

	case READ_DATA:
		isBiofeedback = Serial.parseInt();
		if (isBiofeedback) {
			SM = SUPPLY_MOTOR;
		}
		else {
			settings = SH->reciveData();
			buffer = "";
			count = 0;
			SM = UPDATE_SETTINGS;
		}
		break;

	case UPDATE_SETTINGS:
		filter->setFrequency(settings);
		if (settings.RGain) {
			amplifier->setGain(settings.RGain);
		}
		adc->setFrequency(settings.frequency);
		adc->setResolutionADC(settings.resolution);
		adc->setAveragingADC(settings.averaging);
		adc->setSamplingADC(settings.samplingSpeed);
		bufferSize = settings.bufferSize;
		bufferSizeSave = settings.bufferSizeSave;
		SM = SAVE_SETTINGS;
		break;

	case SAVE_SETTINGS:
		SH->save(settings);
		SM = ACQUIRE;
		break;

	case SUPPLY_MOTOR:
		isBiofeedbackOn = !isBiofeedbackOn;
		if (isBiofeedbackOn) {
			digitalWriteFast(motor, HIGH);
		}
		else {
			digitalWriteFast(motor, LOW);
		}
		SM = SEND;
		break;

	case ACQUIRE_NC:
		if (adc->flag) {
			value = adc->getNewValue();
			SD->save(value);
			sum += value;
			buffer += String(value);
			buffer += ",";
			count++;

		}
		if (count == bufferSizeSave) {
			Serial.println(micros() - m1);
			m1 = micros();
			SM = BIOFEEDBACK_CALC;
		}
		break;

	case BIOFEEDBACK_CALC:
		/*sum = sum / count;
		if (sum >= biofeedbackThreshold) {
			isBiofeedback = true;
		}
		else {
			isBiofeedback = false;
		}*/
		SM = SUPPLY_MOTOR_NC;
		break;

	case SAVE:
		static int a = 1;
		if (a < 100) {
			a++;
		}
		else {
			m1 = micros();
			SD->sync();
			Serial.print("sync: ");
			Serial.println(micros() - m1);
		}
		buffer = "";
		count = 0;
		SM = ACQUIRE_NC;
		break;

	case SUPPLY_MOTOR_NC:
		if (isBiofeedback) {
			digitalWriteFast(motor, HIGH);
		}
		else {
			digitalWriteFast(motor, LOW);
		}
		SM = SAVE;
		break;
	}
}


