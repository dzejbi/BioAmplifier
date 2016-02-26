
#ifndef BASIC_SCREEN_H
#define BASIC_SCREEN_H

#include<WProgram.h>

class BasicScreenProperties
{
private:
	uint16_t xMin;
	uint16_t yMin;
	uint16_t xMax;
	uint16_t yMax;
	uint16_t backgroundColor;
public:
	BasicScreenProperties(uint16_t backgroundColor, uint16_t xMin, uint16_t yMin, uint16_t xMax, uint16_t yMax);
	BasicScreenProperties();
	uint16_t getBackgroundColor();
	uint16_t getXMin();
	bool isOutOfRangeX(uint16_t PointX);
	bool isOutOfRangeY(uint16_t PointY);
	bool isFirstPointInLine(uint16_t PointX); 
}; 

#endif
