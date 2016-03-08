#include <ILI9341_t3.h>
#include <XPT2046_Touchscreen.h>
#include <SPI.h>
#include "SignalScaleHandler.h"
#include "BasicScreenProperties.h"
#include "signalDrawer.h"




SignalDrawer::SignalDrawer(ILI9341_t3* tft, SignalScaleHandler* ssh){
  this->signalColor = ILI9341_GREEN;
  this->analogPin = A2;
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


void SignalDrawer::setSignalColor(uint16_t signalColor){
  this->signalColor = signalColor;
}


void SignalDrawer::drawSignal(float newPoint) {

	getReadyForNewPoint();
	currentYPoint = signalScaleHandler->adjustAmplitude(newPoint);
	// tft->drawPixel(x2Point, y2Point, signalColor);
	tft->drawLine(previousXPoint, previousYPoint, currentXPoint, currentYPoint, signalColor);
	addPointToHistory();
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

void SignalDrawer::getReadyForNewPoint()
{
	previousXPoint = currentXPoint;
	previousYPoint = currentYPoint;

	if (!basicScreenProperties->isOutOfRangeX(currentXPoint)) {
		currentXPoint = previousXPoint + 1;
	}
	else {
		previousXPoint = basicScreenProperties->getXMin();
		currentXPoint = previousXPoint + 1;
	}

	if (basicScreenProperties->isFirstPointInLine(previousXPoint)) {
		drawBlank();
	}
}

uint16_t* SignalDrawer::getPointsHistory() {
	return pointsHistory;
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
