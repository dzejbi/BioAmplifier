#ifndef SIGNAL_DRAWER_H
#define SIGNAL_DRAWER_H

#include<WProgram.h>

class signalDrawer{
  private:
	ILI9341_t3 tft = ILI9341_t3(10, 9);
    uint16_t xMin;
    uint16_t yMin;
    uint16_t xMax;
    uint16_t yMax;
    uint16_t backgroundColor;
    uint16_t signalColor;
	uint16_t x1Point;
	uint16_t x2Point;
	uint16_t y1Point;
	uint16_t y2Point;
	uint16_t frequencyScale;
	int16_t offset;
	float amplitudeScale;
	char analogPin;
	uint16_t pointsHistory[320];
	void decreaseOffset();
	void increaseOffset();
	void decreaseFrequency();
	void increaseFrequency();
	void decreaseAmplitude();
	void increaseAmplitude();
	void drawLimitInfo();
    
  public: 
    signalDrawer(uint8_t tft_cs, uint8_t tft_dc);
    void setScreenDimension(uint16_t xmin, uint16_t xmax, uint16_t ymin, uint16_t ymax);
    void setAnalogPin(char analogPin);
    void setColors(uint16_t backgroundColor, uint16_t signalColor);
    void setScale(uint16_t frequencyScale, float amplitudeScale, int16_t offset);
	void getNewPoint();
    void drawSignal();
	void drawSignal(uint16_t* signal);
	void addPointToHistory();
	void drawMenu();
	void menuAction(TS_Point p);
	void drawBlank();
	void reset();
	uint16_t* getPointsHistory();

};

#endif
