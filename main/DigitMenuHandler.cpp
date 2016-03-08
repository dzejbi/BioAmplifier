// 
// 
// 

#include "DigitMenuHandler.h"


void DigitMenuHandler::createButtonArray() {

	buttonArray[0] = Button(0, 3, "<-", ILI9341_BLACK);
	buttonArray[1] = Button(1, 0, "1", ILI9341_WHITE);
	buttonArray[2] = Button(1, 1, "2", ILI9341_WHITE);
	buttonArray[3] = Button(1, 2, "3", ILI9341_WHITE);
	buttonArray[4] = Button(1, 3, ".", ILI9341_WHITE);
	buttonArray[5] = Button(2, 0, "4", ILI9341_WHITE);
	buttonArray[6] = Button(2, 1, "5", ILI9341_WHITE);
	buttonArray[7] = Button(2, 2, "6", ILI9341_WHITE);
	buttonArray[8] = Button(2, 3, "0", ILI9341_WHITE);
	buttonArray[9] = Button(3, 0, "7", ILI9341_WHITE);
	buttonArray[10] = Button(3, 1, "8", ILI9341_WHITE);
	buttonArray[11] = Button(3, 2, "9", ILI9341_WHITE);
	buttonArray[12] = Button(3, 3, "OK", ILI9341_WHITE);
}

void DigitMenuHandler::createButtonAppearance()
{
	for (int i = 0; i < 13; i++) {
		buttonArray[i].setAppearance(10 + buttonArray[i].column * 75, 10 + buttonArray[i].row * 55, 70, 50, 5, ILI9341_BLACK);
		buttonArray[i].setCursor(40 + buttonArray[i].column * 75, 20 + buttonArray[i].row * 55, 4);
	}
	buttonArray[4].setCursor(265, 75, 4);
	buttonArray[8].setCursor(265, 130, 4);
	buttonArray[0].setCursor(245, 20, 4);
	buttonArray[12].setCursor(245, 185, 4);
	buttonArray[0].setColor(ILI9341_YELLOW);
	buttonArray[12].setColor(ILI9341_GREEN);
}

Button DigitMenuHandler::whatButtonWasPressed(TS_Point p)
{
	return Button();
}
	

DigitMenuHandler::DigitMenuHandler(ILI9341_t3 * tft)
{
	this->tft = tft;
	createButtonArray();
	createButtonAppearance();
}

MenuAction DigitMenuHandler::handleTouch(TS_Point p)
{
	return MenuAction();
}

void DigitMenuHandler::drawButton(Button b) {

	tft->fillRoundRect(b.x0, b.y0, b.width, b.height, b.radius, b.color);
	tft->setTextColor(b.nameColor);
	tft->setTextSize(b.textSize);
	tft->setCursor(b.cursor_x, b.cursor_y);
	tft->print(b.name);
}

void DigitMenuHandler::drawMenu()
{
	tft->fillScreen(ILI9341_LIGHTGREY);
	tft->fillRect(10, 10, 220, 50, ILI9341_BLACK);
	for (int i = 0; i < 13; i++) {
		drawButton(buttonArray[i]);
	}
}

