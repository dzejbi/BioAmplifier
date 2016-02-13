#include <ILI9341_t3.h>
#include <font_Arial.h> // from ILI9341_t3
#include <XPT2046_Touchscreen.h>
#include <SPI.h>
#include "signalDrawer.h"


signalDrawer::signalDrawer(){
  this->xMin = 0;
  this->xMax = ILI9341_TFTHEIGHT;
  this->yMin = 0;
  this->yMax = ILI9341_TFTWIDTH;
  this->backgroundColor = ILI9341_BLACK;
  this->signalColor = ILI9341_GREEN;
  this->frequencyScale = 50;
  this->amplitudeScale = 5;
  this->x1Point = 0;
  this->x2Point = 0;
  this->y1Point = 0;
  this->y2Point = 0;
  this->offset = 0;
}

void signalDrawer::setScreenDimension(uint16_t xmin, uint16_t xmax, uint16_t ymin, uint16_t ymax){
  this->xMin = xmin;
  this->xMax = xmax;
  this->yMin = ymin;
  this->yMax = ymax;
}

void signalDrawer::setAnalogPin(char analogPin){
  this->analogPin = analogPin;
}

void signalDrawer::setColors(uint16_t backgroundColor, uint16_t signalColor){
  this->backgroundColor = backgroundColor;
  this->signalColor = signalColor;
}

void signalDrawer::setScale(uint16_t frequencyScale, uint16_t amplitudeScale, uint16_t offset){
  this->frequencyScale = frequencyScale;
  this->amplitudeScale = amplitudeScale;
  this->offset = offset;
}

void signalDrawer::drawSignal(ILI9341_t3 & tft) {

	y2Point = analogRead(analogPin)/amplitudeScale - offset;

	if (x2Point < xMax) {
		x2Point = x1Point + 1;
	}else {
		x2Point = xMin;
		//TODO Set navigation
		tft.fillScreen(backgroundColor);
	}

	Serial.print("x1 = ");
	Serial.print(x1Point);
	Serial.print(" x2 = ");
	Serial.print(x2Point);
	Serial.print(" y1 = ");
	Serial.print(y1Point);
	Serial.print(" y2 = ");
	Serial.println(y2Point);

	if(x2Point < x1Point) {
		x1Point = 0;
		x2Point = 1;
	}

	tft.drawLine(x1Point, y1Point, x2Point, y2Point, signalColor);
	// tft.drawPixel(x2Point, y2Point, signalColor);

	x1Point = x2Point;
	y1Point = y2Point;
	delay(frequencyScale);
}

void signalDrawer::drawMenu(ILI9341_t3 & tft) {

	tft.drawFastVLine(160, 0, 80, ILI9341_CYAN);
	tft.drawFastVLine(160, 160, 80, ILI9341_CYAN);
	tft.drawFastVLine(100, 80, 80, ILI9341_CYAN);
	tft.drawFastVLine(220, 80, 80, ILI9341_CYAN);
	tft.drawFastHLine(0, 80, 320, ILI9341_CYAN);
	tft.drawFastHLine(0, 160, 320, ILI9341_CYAN);
	tft.setTextColor(ILI9341_DARKGREEN);
	tft.setTextSize(8);
	tft.setCursor(30, 10);
	tft.print("O+");
	tft.setCursor(30, 175);
	tft.print("O-");
	tft.setTextColor(ILI9341_BLUE);
	tft.setCursor(200, 10);
	tft.print("A+");
	tft.setCursor(200, 175);
	tft.print("A-");
  tft.setTextColor(ILI9341_RED);
	tft.setTextSize(4);
	tft.setCursor(115, 105);
	tft.print("MENU");
	tft.setTextColor(ILI9341_WHITE);
	tft.setCursor(30, 105);
	tft.print("F-");
	tft.setCursor(250, 105);
	tft.print("F+");

}


