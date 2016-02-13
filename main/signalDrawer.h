#ifndef SIGNAL_DRAWER_H
#define SIGNAL_DRAWER_H

#include<WProgram.h>

class signalDrawer{
  private:
    uint16_t xMin;
    uint16_t yMin;
    uint16_t xMax;
    uint16_t yMax;
    uint16_t backgroundColor;
    uint16_t signalColor;
    uint16_t frequencyScale;
    uint16_t amplitudeScale;
	uint16_t offset;
	uint16_t x1Point;
	uint16_t x2Point;
	uint16_t y1Point;
	uint16_t y2Point;
	char analogPin;
    
  public: 
    signalDrawer();
    void setScreenDimension(uint16_t xmin, uint16_t xmax, uint16_t ymin, uint16_t ymax);
    void setAnalogPin(char analogPin);
    void setColors(uint16_t backgroundColor, uint16_t signalColor);
    void setScale(uint16_t frequencyScale, uint16_t amplitudeScale, uint16_t offset);
    void drawSignal(ILI9341_t3 & tft);
	void drawMenu(ILI9341_t3 & tft);
};

#endif
