#ifndef BUTTON_H
#define BUTTON_H

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif

class Button
{
public:
	char row;
	char column;
	String name;
	uint16_t nameColor;

	uint16_t x0;
	uint16_t y0;
	uint16_t width;
	uint16_t height;
	uint16_t radius;
	uint16_t color;

	uint16_t cursor_x;
	uint16_t cursor_y;
	char textSize;

	Button(char row, char column, String name, uint16_t nameColor);
	Button(char row, char column);
	Button();
	bool operator ==(const Button &button);
	void setAppearance(uint16_t x0, uint16_t y0, uint16_t width, uint16_t height, uint16_t radius, uint16_t color);
	void setCursor(uint16_t cursor_x, uint16_t cursor_y, char textSize);
	void setColor(uint16_t color);
};

#endif