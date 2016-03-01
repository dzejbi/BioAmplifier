#ifndef SIGNAL_DRAWER_H
#define SIGNAL_DRAWER_H

#include<WProgram.h>

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
	char analogPin;
	uint16_t pointsHistory[320];

  public: 
	void drawMenuNumbers(uint16_t color);
	void drawMenuScale(uint16_t color);
	SignalDrawer(ILI9341_t3 * tft, SignalScaleHandler * ssh);
	void setAnalogPin(char analogPin);
    void setSignalColor(uint16_t signalColor);
	void getNewPoint();
    void drawSignal();
	void drawSignal(uint16_t* signal);
	void addPointToHistory();
	void reset();
	void drawBlank();
	void drawInfo(String info);
	uint16_t* getPointsHistory();

};

#endif
