
#include "DigitMenuHandler.h"
#include "ADCHandler.h"
#include <ADC.h>
#include <ILI9341_t3.h>
#include <SPI.h>
#include <XPT2046_Touchscreen.h>
#include "BasicScreenProperties.h"
#include "SignalScaleHandler.h"
#include "SignalDrawer.h"
#include "SignalDrawerMenuHandler.h"
#include "StateMachineEnum.h"
#include "SignalScaleActionsEnum.h"

#define TFT_RST 7
#define CS_PIN  8
#define TFT_DC  9
#define TFT_CS 10
// MOSI=11, MISO=12, SCK=13

//Objects initialization
XPT2046_Touchscreen* ts = new XPT2046_Touchscreen(CS_PIN);
ILI9341_t3* tft = new ILI9341_t3(TFT_CS, TFT_DC, TFT_RST);
SignalScaleHandler* signalScaleHandler = new SignalScaleHandler(tft);
SignalDrawer* signalDrawer = new SignalDrawer(tft, signalScaleHandler);
ADCHandler* adc = new ADCHandler();
SignalDrawerMenuHandler* signalDrawerMenuHandler = new SignalDrawerMenuHandler(tft);
DigitMenuHandler* digitMenuHandler = new DigitMenuHandler(tft);

//State machine enums
StateMachineEnum state = SIGNAL_DRAW;
StateMachineEnum menu;
StateMachineEnum notTouched;
MenuAction menuAction;

//Variables used in State Machine
float* adcValue;
TS_Point point;
uint16_t* snapshot;
MenuHandler* menuHandler;


//Debug variables
unsigned long mic;
unsigned long mic2;



void setup() {
	Serial.begin(9600);
	ts->begin();
	//while(!Serial);
	adc->start();
	Serial.println("Setup done");
}

void loop() {
	switch (state)
	{
	case SIGNAL_DRAW:
		//mic = micros();
		adcValue = adc->getNewValue();
		if (adcValue != nullptr) {
			signalDrawer->drawSignal(*adcValue);
		}
		menu = SIGNAL_DRAW_MENU_HANDLE;
		notTouched = SIGNAL_DRAW;
		state = CHECK_TOUCH;
		menuHandler = signalDrawerMenuHandler;
		//mic2 = micros() - mic;
		//Serial.print("czas wykonania signal_draw: ");
		//Serial.println(mic2);
		break;

	case CHECK_TOUCH:
		//mic = micros();
		if (ts->touched()) {
			//TODO
			state = DRAW_MENU;
		}
		else {
			state = notTouched;
		}
		//mic2 = micros() - mic;
		//Serial.print("czas wykonania check_touch: ");
		//Serial.println(mic2);
		break;

	case DRAW_MENU:
		menuHandler->drawMenu();
		delay(100);
		state = WAIT_FOR_TOUCH;
		break;

	case WAIT_FOR_TOUCH:
		for (int i = 0; i < 100000; i++) {
			if (ts->touched()) {
				point = ts->getPoint();
				state = menu;
				break;
			}
			else {
				state = notTouched;
			}
		}
		signalDrawer->drawBlank();
		break;

	case SIGNAL_DRAW_MENU_HANDLE:
		menuAction = signalDrawerMenuHandler->handleTouch(point);
		state = menuAction.stateMachineEnum;
		break;

	case MAIN_MENU:
		//TODO main menu
		state = SIGNAL_DRAW;
		break;

	case SNAPSHOT:
		snapshot = signalDrawer->getPointsHistory();
		state = SIGNAL_DRAW;
		break;

	case SIGNAL_SCALE:
		signalScaleHandler->action(menuAction.signalScaleEnum);
		delay(10);
		state = SIGNAL_DRAW;
		break;

	case SCALE_MENU:
		//TODO
		state = SIGNAL_DRAW;
		break;

	default:
		Serial.println("Error");
		break;
	}
}

