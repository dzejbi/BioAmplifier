#include "BasicScreenProperties.h"
#include <ILI9341_t3.h>

BasicScreenProperties::BasicScreenProperties(uint16_t backgroundColor, uint16_t xMin , uint16_t yMin, uint16_t xMax, uint16_t yMax)
{
	this->backgroundColor = backgroundColor;
	this->xMin = xMin;
	this->xMax = xMax;
	this->yMin = yMin;
	this->yMax = yMax;
}

BasicScreenProperties::BasicScreenProperties() {
	this->backgroundColor = ILI9341_BLACK;
	this->xMin = 0;
	this->xMax = ILI9341_TFTHEIGHT;
	this->yMin = 0;
	this->yMax = ILI9341_TFTWIDTH;
}

uint16_t BasicScreenProperties::getBackgroundColor() {
	return backgroundColor;
}

uint16_t BasicScreenProperties::getXMin()
{
	return xMin;
}

bool BasicScreenProperties::isOutOfRangeX(uint16_t PointX)
{
	if (PointX > xMax || PointX < xMin) {
		return true;
	}
	else {
		return false;
	}
}

bool BasicScreenProperties::isOutOfRangeY(uint16_t PointY)
{
	if (PointY > yMax || PointY < yMin) {
		return true;
	}
	else {
		return false;
	}
}

bool BasicScreenProperties::isFirstPointInLine(uint16_t PointX)
{
	return PointX==xMin;
}

