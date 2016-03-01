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

XPT2046_Touchscreen* ts = new XPT2046_Touchscreen(CS_PIN);
ILI9341_t3* tft = new ILI9341_t3(TFT_CS, TFT_DC, TFT_RST);
SignalScaleHandler* signalScaleHandler = new SignalScaleHandler(tft);
SignalDrawer sigDraw = SignalDrawer(tft, signalScaleHandler);
StateMachineEnum state = SIGNAL_DRAW;
StateMachineEnum menu;
StateMachineEnum notTouched;
TS_Point point;
SignalScaleEnum signalScaleAction;
SignalDrawerMenuHandler signalDrawMenuHandler = SignalDrawerMenuHandler(tft);
uint16_t* snapshot;
MenuHandler* menuHandler;


void setup() {
	Serial.begin(9600);
	ts->begin();
}

void loop() {
	switch (state)
	{
	case SIGNAL_DRAW:
		sigDraw.getNewPoint();
		sigDraw.drawSignal();
		sigDraw.addPointToHistory();
		menu = SIGNAL_DRAW_MENU_HANDLE;
		notTouched = SIGNAL_DRAW;
		state = CHECK_TOUCH;
		menuHandler = &signalDrawMenuHandler;
		break;

	case CHECK_TOUCH:
		if (ts->touched()) {
			//TODO
			state = DRAW_MENU;
		}
		else {
			state = SIGNAL_DRAW;
		}
		break;

	case DRAW_MENU:
		menuHandler->drawMenu();
		delay(100);
		state = WAIT_FOR_TOUCH;
		break;

	case WAIT_FOR_TOUCH:
		for (int i = 0; i < 3000; i++) {
			if (ts->touched()) {
				point = ts->getPoint();
				state = menu;
				break;
			}
			else {
				state = notTouched;
			}
			delay(1);
		}
		sigDraw.drawBlank();
		break;

	case SIGNAL_DRAW_MENU_HANDLE:
		Serial.println(point.x);
		signalScaleAction = signalDrawMenuHandler.handleTouch(point).signalScaleEnum;
		state = signalDrawMenuHandler.handleTouch(point).stateMachineEnum;
		Serial.println(signalScaleAction);
		break;

	case MAIN_MENU:
		//TODO main menu
		state = SIGNAL_DRAW;
		break;

	case SNAPSHOT:
		snapshot = sigDraw.getPointsHistory();
		state = SIGNAL_DRAW;
		break;

	case SIGNAL_SCALE:
		signalScaleHandler->action(signalScaleAction);
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
