#include <ILI9341_t3.h>
#include <XPT2046_Touchscreen.h>
#include <SPI.h>
#include "SignalScaleHandler.h"
#include "BasicScreenProperties.h"
#include "signalDrawer.h"


SignalDrawer::SignalDrawer(ILI9341_t3* tft, SignalScaleHandler* ssh){
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
  this->signalScaleHandler = ssh;
  this->basicScreenProperties = new BasicScreenProperties();
  signalScaleHandler->begin();
  drawBlank();
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
	currentYPoint = signalScaleHandler->adjustAmplitude(analogRead(analogPin));

	if (!basicScreenProperties->isOutOfRangeX(currentXPoint)) {
		currentXPoint = previousXPoint + 1;
	}
	else {
		previousXPoint = basicScreenProperties->getXMin();
		currentXPoint = previousXPoint + 1;
	}
	signalScaleHandler->measurmentDelay();
}

void SignalDrawer::drawSignal() {

	if (basicScreenProperties->isFirstPointInLine(previousXPoint)) {
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
	tft->fillScreen(basicScreenProperties->getBackgroundColor());
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
