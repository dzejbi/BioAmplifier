#include <ILI9341_t3.h>
#include <font_Arial.h> // from ILI9341_t3
#include "XPT2046_Touchscreen_v1.h"
#include <SPI.h>
#include "SignalScaleHandler.h"
#include "BasicScreenProperties.h"
#include "signalDrawer.h"


SignalDrawer::SignalDrawer(ILI9341_t3* tft){
  this->signalColor = ILI9341_GREEN;
  this->previousXPoint = 0;
  this->currentXPoint = 0;
  this->previousYPoint = 0;
  this->currentYPoint = 0;
  this->tft = tft;
  for (int i = 0; i < 320; i++) {
	  this->pointsHistory[i]= 0;
  }
  this->tft->begin();
  this->tft->setRotation(1);
  signalScaleHandler.begin();
  drawBlank();
}

void SignalDrawer::menuAction(TS_Point p) {
		if (p.x > 2700) {
			if (p.y <= 1300) {
				signalScaleHandler.increaseOffset();
				delay(200);
			}
			else if (p.y <= 2600) {
				//TODO snapshot
				drawBlank();
				drawSignal(getPointsHistory());
				delay(200);
				reset();
			}
			else {
				signalScaleHandler.increaseAmplitude();
				delay(200);
			}
		}
		else if (p.x >= 1400) {
			if (p.y <= 1300) {
				signalScaleHandler.decreaseOffset();
				delay(200);
			}
			else if (p.y >= 2600) {
				signalScaleHandler.decreaseAmplitude();
				delay(200);
			}
			else {
				//TODO: Handle menu 
				signalScaleHandler.begin();
				tft->fillScreen(ILI9341_WHITE);
				tft->setTextSize(8);
				tft->print("MENU");
				delay(200);
			}
		}
		else if (p.x < 1400) {
			if (p.y <= 1300) {
				signalScaleHandler.decreaseFrequency();
				delay(200);
			}
			else if (p.y >= 2600) {
				signalScaleHandler.increaseFrequency();
				delay(200);
			}
			else {
				//TODO scale menu
				//scaleMenu();
				delay(200);
			}
		}
	reset();
}


void SignalDrawer::setAnalogPin(char analogPin){
  this->analogPin = analogPin;
}

void SignalDrawer::setSignalColor(uint16_t signalColor){
  this->signalColor = signalColor;
}


void SignalDrawer::getNewPoint() {

	previousXPoint = currentXPoint;
	previousYPoint = currentYPoint;
	//TODO 16bit ADC
	currentYPoint = signalScaleHandler.adjustAmplitude(analogRead(analogPin));

	if (!basicScreenProperties.isOutOfRangeX(currentXPoint)) {
		currentXPoint = previousXPoint + 1;
	}
	else {
		previousXPoint = basicScreenProperties.getXMin();
		currentXPoint = previousXPoint + 1;
	}
	signalScaleHandler.measurmentDelay();
}

void SignalDrawer::drawSignal() {

	if (basicScreenProperties.isFirstPointInLine(previousXPoint)) {
		drawBlank();
	}
	tft->drawLine(previousXPoint, previousYPoint, currentXPoint, currentYPoint, signalColor);
	// tft.drawPixel(x2Point, y2Point, signalColor);
}

void SignalDrawer::drawSignal(uint16_t* signal) {

	signal[0] = signal[1];
	for (int i = 0; i < currentXPoint; i++) {
		tft->drawLine(i, signal[i], i+1, signal[i+1], ILI9341_RED);
	}
}

void SignalDrawer::addPointToHistory() {
	pointsHistory[currentXPoint-1] = currentYPoint;
}

uint16_t* SignalDrawer::getPointsHistory() {
	return pointsHistory;
}

void SignalDrawer::drawMenu() {
  
	drawBlank();
	drawMenu3x3(ILI9341_BLACK);
	tft->setTextSize(4);


	tft->setTextColor(ILI9341_DARKGREEN);
	tft->setCursor(30, 185);
	tft->print("F-");

	tft->setCursor(250, 185);
	tft->print("F+");

	tft->setTextColor(ILI9341_RED);
	tft->setCursor(115, 105);
	tft->print("MENU");

	tft->setTextColor(ILI9341_WHITE);
	tft->setCursor(30, 105);
	tft->print("O-");

	tft->setCursor(250, 105);
	tft->print("A-");

	tft->setTextColor(ILI9341_BLUE);
	tft->setCursor(250, 25);
	tft->print("A+");

	tft->setCursor(30, 25);
	tft->print("O+");

	tft->setTextColor(ILI9341_YELLOW);
	tft->setCursor(115, 25);
	tft->print("SNAP");

	tft->setTextColor(ILI9341_PURPLE);
	tft->setCursor(115, 190);
	tft->setTextSize(3);
	tft->print("SCALE");
  

}

void SignalDrawer::drawScaleMenu() {


}

void SignalDrawer::drawInfo(String info){
	tft->fillScreen(ILI9341_BLACK);
	tft->setCursor(50, 105);
	tft->setTextColor(ILI9341_RED);
	tft->print(info);
	delay(1000);
}


void SignalDrawer::reset() {
	drawBlank();
	previousXPoint = 0;
	currentXPoint = 0;
}

void SignalDrawer::drawBlank()
{
	tft->fillScreen(basicScreenProperties.getBackgroundColor());
}

void SignalDrawer::drawMenu3x3(uint16_t color) {

	tft->fillScreen(ILI9341_LIGHTGREY);

	tft->fillRoundRect(8, 8, 90, 71, 15, color);
	tft->fillRoundRect(8, 84, 90, 71, 15, color);
	tft->fillRoundRect(8, 160, 90, 71, 15, color);

	tft->fillRoundRect(103, 8, 115, 71, 15, color);
	tft->fillRoundRect(103, 84, 115, 71, 15, color);
	tft->fillRoundRect(103, 160, 115, 71, 15, color);

	tft->fillRoundRect(223, 8, 90, 71, 15, color);
	tft->fillRoundRect(223, 84, 90, 71, 15, color);
	tft->fillRoundRect(223, 160, 90, 71, 15,color);

	tft->drawFastVLine(100, 0, 240, color);
	tft->drawFastVLine(220, 0, 240, color);
	tft->drawFastHLine(0, 80, 320, color);
	tft->drawFastHLine(0, 160, 320, color);

}

void SignalDrawer::drawMenuNumbers(uint16_t color) {

	tft->fillScreen(ILI9341_LIGHTGREY);

	tft->setTextSize(4);
	tft->setTextColor(ILI9341_WHITE);

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			tft->fillRoundRect(10 + i * 75, 10 + j * 55, 70, 50, 10, color);
			tft->setCursor(40 + i * 75, 20 + j * 55);
			if (i < 3) {
				tft->print(i - 2 + j * 3);
			}
		}
	}

	tft->fillRect(10, 10, 220, 50, color);

	tft->setCursor(265, 75);
	tft->print(".");
	tft->setCursor(265, 130);
	tft->print("0");

	tft->fillRoundRect(235, 10, 70, 50, 10, ILI9341_YELLOW);
	tft->setCursor(245 , 20);
	tft->print("<-");
	tft->fillRoundRect(235, 175, 70, 50, 10, ILI9341_GREEN);
	tft->setCursor(245, 185);
	tft->print("OK");

}

void SignalDrawer::drawMenuScale(uint16_t color) {

	tft->fillScreen(ILI9341_LIGHTGREY);

	tft->setTextSize(4);
	tft->setTextColor(ILI9341_WHITE);

	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 4; j++) {
			tft->fillRoundRect(10 + i * 150, 10 + j * 55, 140, 50, 10, color);
		}
	}

}
