
#include "Settings.h"
#include "Amplifier.h"
#include "Filter.h"
#include "ADCHandler.h"
#include <ADC.h>
#include <SPI.h>

//Objects initialization


enum StateMachine
{
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
	CHECK_DATA
};


//Debug
long m1 = 0;
long m2 = 0;

volatile StateMachine SM = LOAD_SETTINGS;

ADCHandler* adc = new ADCHandler();
Filter* filter = new Filter();
Amplifier* amplifier = new Amplifier();
SettingsHandler* SH = new SettingsHandler();

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
int biofeedbackStrength = 0;
float biofeedbackThreshold;

bool isBiofeedback = true;


void setup() {
	pinMode(motor, OUTPUT);
	Serial.begin(9600);
	Serial.setTimeout(1);
	filter->begin();
	amplifier->begin();
	adc->begin();
	// TODO: Attach interrupt to pin 
	attachInterrupt(0, buttonPressed, CHANGE);
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
		bufferSize = settings.bufferSize;
		bufferSizeSave = settings.bufferSizeSave;
		SM = CHECK_CONNECTION;
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
			SM = CHECK_DATA;
		//	Serial.println(micros() - m1);
		}
		break;

	case CHECK_DATA:
		if (Serial.available()) {
			SM = READ_DATA;
		}
		else {
			SM = SEND;
		}
		break;

	case SEND:
		//m2 = micros();
		Serial.println(buffer);
		buffer = "";
		count = 0;
		//Serial.println(micros() - m2);
		SM = ACQUIRE;
		break;

	case READ_DATA:
		//TODO Labview send data 0/1, change function reciveData
		isBiofeedback = Serial.parseInt();
		if (isBiofeedback) {
			SM = SUPPLY_MOTOR;
		}
		else {
			settings = reciveData();
			buffer = "";
			count = 0;
			SM = UPDATE_SETTINGS;
		}
		break;

	case UPDATE_SETTINGS:
		//TODO update all settings
		filter->setFrequency(settings);
		if (settings.RGain) {
			amplifier->setGain(settings.RGain);
		}
		adc->setFrequency(settings.frequency);
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
		Serial.println(micros() - m1);
		break;

	case ACQUIRE_NC:
		//TODO separate buffersize?
		if (adc->flag) {
			value = adc->getNewValue();
			sum += value;
			buffer += String(value);
			buffer += ",";
			count++;

		}
		if (count == bufferSizeSave) {
			SM = BIOFEEDBACK_CALC;
		}
		break;

	case BIOFEEDBACK_CALC:
		sum = sum / count;
		if (sum >= biofeedbackThreshold) {
			biofeedbackStrength = 255;
		}
		else {
			biofeedbackStrength = 0;
		}
		SM = SUPPLY_MOTOR_NC;
		break;

	case SAVE:
		//TODO: microsd save
		SM = ACQUIRE_NC;
		break;

	case SUPPLY_MOTOR_NC:
		analogWrite(motor, biofeedbackStrength);
		SM = SAVE;
		break;
	}
}

Settings reciveData() {

	long settings[10];
	Settings temp;

	Serial.setTimeout(1000);

	for (int i = 0; i<8; i++) {
		settings[i] = Serial.parseInt();
	}
	// TODO check 
	temp.R1 = settings[0];
	temp.R2 = settings[1];
	temp.R3 = settings[2];
	temp.R4 = settings[3];
	temp.RGain = settings[4];
	temp.bufferSizeSave = settings[5];
	temp.frequency = settings[6];
	temp.averaging = settings[7];
	temp.resolution = settings[8];
	temp.bufferSize = settings[9];

	Serial.setTimeout(1);

	return temp;
}

void buttonPressed() {
	//TODO Save parameters of 
	if (SM == ACQUIRE_NC || SM == BIOFEEDBACK_CALC || SM == SUPPLY_MOTOR_NC || SM == SAVE) {
		SM = ACQUIRE;
	}
	else {
		SM = ACQUIRE_NC;
	}
}
