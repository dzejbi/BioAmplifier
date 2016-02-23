#include <ILI9341_t3.h>
#include <font_Arial.h> // from ILI9341_t3
#include <XPT2046_Touchscreen.h>
#include <SPI.h>
#include "signalDrawer.h"


signalDrawer::signalDrawer(uint8_t tft_cs, uint8_t tft_dc){
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
  this->tft = ILI9341_t3(tft_cs, tft_dc);
  for (int i = 0; i < 320; i++) {
	  this->pointsHistory[i]= 0;
  }
  tft.begin();
  tft.setRotation(1);
  drawBlank();
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

void signalDrawer::setScale(uint16_t frequencyScale, float amplitudeScale, int16_t offset){
  this->frequencyScale = frequencyScale;
  this->amplitudeScale = amplitudeScale;
  this->offset = offset;
}

void signalDrawer::getNewPoint() {

	x1Point = x2Point;
	y1Point = y2Point;

	y2Point = (float)(analogRead(analogPin) / amplitudeScale) - offset;

	if (x2Point < xMax) {
		x2Point = x1Point + 1;
	}
	else {
		x2Point = xMin + 1;
		x1Point = xMin;
	}

	delay(frequencyScale);
}

void signalDrawer::drawSignal() {

	if (x1Point == xMin) {
		drawBlank();
	}
	tft.drawLine(x1Point, y1Point, x2Point, y2Point, signalColor);
	// tft.drawPixel(x2Point, y2Point, signalColor);

}

void signalDrawer::drawSignal(uint16_t* signal) {

	signal[0] = signal[1];
	for (int i = 0; i < x2Point; i++) {
		tft.drawLine(i, signal[i], i+1, signal[i+1], ILI9341_RED);
	}
}

void signalDrawer::addPointToHistory() {
	pointsHistory[x2Point-1] = y2Point;
}



void signalDrawer::drawMenu() {
  
	drawBlank();
	tft.drawFastVLine(100, 0, 160, ILI9341_CYAN);
	tft.drawFastVLine(220, 0, 160, ILI9341_CYAN);
	tft.drawFastVLine(160, 160, 80, ILI9341_CYAN);
	tft.drawFastHLine(0, 80, 320, ILI9341_CYAN);
	tft.drawFastHLine(0, 160, 320, ILI9341_CYAN);
	tft.setTextColor(ILI9341_DARKGREEN);
	tft.setTextSize(8);
	tft.setCursor(30, 175);
	tft.print("F-");
	tft.setCursor(200, 175);
	tft.print("F+");
	tft.setTextColor(ILI9341_RED);
	tft.setTextSize(4);
	tft.setCursor(115, 105);
	tft.print("MENU");
	tft.setTextColor(ILI9341_WHITE);
	tft.setCursor(30, 105);
	tft.print("O-");
	tft.setCursor(250, 105);
	tft.print("A-");
	tft.setTextColor(ILI9341_BLUE);
	tft.setCursor(250, 25);
	tft.print("A+");
	tft.setCursor(30, 25);
	tft.print("O+");
	tft.setTextColor(ILI9341_YELLOW);
	tft.setCursor(115, 25);
	tft.print("SNAP");

}

void signalDrawer::drawLimitInfo(){
	tft.fillScreen(ILI9341_BLACK);
	tft.setCursor(50, 105);
	tft.setTextColor(ILI9341_RED);
	tft.print("Limit Reached");
	delay(1000);
}

void signalDrawer::decreaseOffset() {

	if (offset - 10 > -500) {
		offset -= 10;
	}
	else {
		drawLimitInfo();
	}
}
void signalDrawer::increaseOffset() {

	if (offset + 10 < 1000) {
		offset += 10;
	}
	else {
		drawLimitInfo();
	}
}
void signalDrawer::decreaseFrequency(){

	if (frequencyScale - 10 > 0) {
		frequencyScale -= 10;
	}
	else if (frequencyScale - 1 > 0) {
		frequencyScale -= 1;
	}
	else {
		drawLimitInfo();
	}
}
void signalDrawer::increaseFrequency(){

	if (frequencyScale + 1 < 10) {
		frequencyScale += 1;
	}
	else if (frequencyScale + 10 < 1000) {
		frequencyScale += 10;
	}
	else {
		drawLimitInfo();
	}
}
void signalDrawer::decreaseAmplitude(){

	if (amplitudeScale + 0.2 < 10) {
		amplitudeScale += 0.2;
	}
	else {
		drawLimitInfo();
	}
}
void signalDrawer::increaseAmplitude(){

	if (amplitudeScale - 0.2 > 0) {
		amplitudeScale -= 0.2;
	}
	else {
		drawLimitInfo();
	}
}

void signalDrawer::menuAction(TS_Point p) {
	if (p.x > 2700) {
		if (p.y <= 1300) {
			increaseOffset();
			delay(200);
		}
		else if(p.y <= 2600) {
			//TODO snapshot
			drawBlank();
			drawSignal(getPointsHistory());
			delay(200);
			reset();
		}
		else {
			increaseAmplitude();
			delay(200);
		}
	}
	else if (p.x >= 1400) {
		if (p.y <= 1300) {
			decreaseOffset();
			delay(200);
		}
		else if (p.y >= 2600) {
			decreaseAmplitude();
			delay(200);
		}
		else {
			//TODO: Handle menu 
			setScale(50, 5, 0);
			tft.fillScreen(ILI9341_WHITE);
			tft.setTextSize(8);
			tft.print("MENU");
			delay(200);
		}
	}
	else if (p.x < 1400) {
		if (p.y < 1900) {
			decreaseFrequency();
			delay(200);
		}
		else {
			increaseFrequency();
			delay(200);
		}
	}
	reset();
}

uint16_t* signalDrawer::getPointsHistory() {
	return pointsHistory;
}

void signalDrawer::drawBlank(){
  tft.fillScreen(backgroundColor);
}

void signalDrawer::reset() {
	drawBlank();
	x1Point = 0;
	x2Point = 0;
}


