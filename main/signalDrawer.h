#ifndef SIGNAL_DRAWER_H
#define SIGNAL_DRAWER_H

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif

class SignalDrawer{
  private:
	ILI9341_t3* tft;
	BasicScreenProperties* basicScreenProperties;
	SignalScaleHandler* signalScaleHandler;
	uint16_t signalColor;
	uint16_t previousXPoint;
	uint16_t currentXPoint;
	uint16_t previousYPoint;
	uint16_t currentYPoint;
	uint8_t analogPin;
	uint16_t pointsHistory[320];
	void addPointToHistory();
	void getReadyForNewPoint();

  public: 
	SignalDrawer(ILI9341_t3 * tft, SignalScaleHandler * ssh);
	void setAnalogPin(uint8_t analogPin);
    void setSignalColor(uint16_t signalColor);

	void reset();
	void drawBlank();

	void drawSignal(uint16_t* signal);
	void drawSignal(float newPoint);
	void drawInfo(String info);

	uint16_t* getPointsHistory();

	// TODO put into class
	void drawMenuNumbers(uint16_t color);
	void drawMenuScale(uint16_t color);


};

#endif
