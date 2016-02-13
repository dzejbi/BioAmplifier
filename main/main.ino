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
ILI9341_t3 tft = ILI9341_t3(TFT_CS, TFT_DC);
signalDrawer sigDraw;


void setup() {
	Serial.begin(38400);
	tft.begin();
	tft.setRotation(1);
	tft.fillScreen(ILI9341_BLACK);
	ts.begin();
	while (!Serial && (millis() <= 1000));
}



void loop() {


	sigDraw.drawSignal(tft);
	if (ts.touched()) {
		sigDraw.drawMenu(tft);
		delay(100);
		for (int i = 0; i < 3000; i++) {
			if (ts.touched()) {
				TS_Point p = ts.getPoint();
				tft.setTextSize(16);
				tft.setCursor(60, 80);
				tft.fillScreen(ILI9341_DARKGREY);
				if (p.x > 2700) {
					if (p.y < 1900) {
						tft.print("0+");
						delay(200);
						break;
					}
					else {
						tft.print("A+");
						delay(200);
						break;
					}
				}
				else if (p.x <= 2700 && p.x >= 1400) {
					if (p.y <= 1300) {
						tft.print("F-");
						delay(200);
						break;
					}
					else if (p.y >= 2600) {
						tft.print("F+");
						delay(200);
						break;
					}
					else {
						tft.setTextSize(8);
						tft.print("MENU");
						delay(200);
						break;
					}
				}
				else if (p.x < 1400) {
					if (p.y < 1900) {
						tft.print("O-");
						delay(200);
						break;
					}
					else {
						tft.print("A-");
						delay(200);
						break;
					}
				}
			}
			delay(1);
		}
		tft.fillScreen(ILI9341_BLACK);
	}
}



/*  boolean istouched = ts.touched();
  
  if (istouched) {
    TS_Point p = ts.getPoint();
    if(p.x > 1500){
      tft.fillScreen(ILI9341_YELLOW);
    }
    else{
      tft.fillScreen(ILI9341_BLACK);
    }
  delay(100);
  }
  */
