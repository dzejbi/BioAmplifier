#include "Button.h"


Button::Button(char row, char column, String name, uint16_t nameColor)
{
	this->row = row;
	this->column = column;
	this->name = name;
	this->nameColor = nameColor;
}

Button::Button(char row, char column)
{
	this->row = row;
	this->column = column;
}

Button::Button()
{
	this->row = -1;
	this->column = -1;
	this->name = "undefined";
}

bool Button::operator==(const Button &button) {

	if (this->row == button.row && this->column == button.column) {
		return true;
	}
	else {
		return false;
	}
}

void Button::setAppearance(uint16_t x0, uint16_t y0, uint16_t width, uint16_t height, uint16_t radius, uint16_t color)
{
	this->x0 = x0;
	this->y0 = y0;
	this->width = width;
	this->height = height;
	this->radius = radius;
	this->color = color;
}

void Button::setCursor(uint16_t cursor_x, uint16_t cursor_y, char textSize)
{
	this->cursor_x = cursor_x;
	this->cursor_y = cursor_y;
	this->textSize = textSize;
}

