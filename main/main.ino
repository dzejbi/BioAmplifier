#include <ILI9341_t3.h>
#include <font_Arial.h> // from ILI9341_t3
#include <SPI.h>
#include "XPT2046_Touchscreen_v1.h"
#include "BasicScreenProperties.h"
#include "SignalScaleHandler.h"
#include "SignalDrawer.h"

#define TFT_RST 7
#define CS_PIN  8
#define TFT_DC  9
#define TFT_CS 10
// MOSI=11, MISO=12, SCK=13

XPT2046_Touchscreen ts(CS_PIN);
ILI9341_t3* tft = new ILI9341_t3(TFT_CS, TFT_DC, TFT_RST);
SignalDrawer sigDraw = SignalDrawer(tft);

void setup() {
	Serial.begin(38400);
	ts.begin();
	sigDraw.drawMenuScale(ILI9341_BLACK);
}



void loop() {

	/*sigDraw.getNewPoint();
	sigDraw.drawSignal();
	sigDraw.addPointToHistory();

	if (ts.touched()) {
		sigDraw.drawMenu();
		delay(100);
		for (int i = 0; i < 3000; i++) {
			if (ts.touched()) {
				TS_Point p = ts.getPoint();
				sigDraw.menuAction(p);
				break;
			}
			delay(1);
		}
	sigDraw.drawBlank();
	}*/

}
