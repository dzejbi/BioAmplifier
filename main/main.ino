#include <ILI9341_t3.h>
#include <font_Arial.h> // from ILI9341_t3
#include <XPT2046_Touchscreen.h>
#include <SPI.h>
#include "signalDrawer.h"

#define CS_PIN  8
#define TFT_DC  9
#define TFT_CS 10
// MOSI=11, MISO=12, SCK=13

XPT2046_Touchscreen ts(CS_PIN);
signalDrawer sigDraw = signalDrawer(TFT_CS, TFT_DC);


void setup() {
	Serial.begin(38400);
	ts.begin();
	while (!Serial && (millis() <= 1000));
}



void loop() {

	sigDraw.getNewPoint();
	sigDraw.drawSignal();
	sigDraw.addPointToHistory();

	if (ts.touched()) {
		sigDraw.drawMenu();
		delay(500);
		for (int i = 0; i < 3000; i++) {
			if (ts.touched()) {
				TS_Point p = ts.getPoint();
				sigDraw.menuAction(p);
				break;
			}
			delay(1);
		}
	sigDraw.drawBlank();
	}
	
}
