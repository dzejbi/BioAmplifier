#include "SignalDrawerMenuHandler.h"

MenuAction SignalDrawerMenuHandler::handleTouch(TS_Point p)
{

	Button buttonPressed = whatButtonWasPressed(p);
	
	if (buttonPressed.name == "A+") {
		menuAction.signalScaleEnum = INCREASE_AMPLITUDE;
		menuAction.stateMachineEnum = SIGNAL_SCALE;
		return menuAction;
	}
	else if (buttonPressed.name == "A-") {
		menuAction.signalScaleEnum = DECREASE_AMPLITUDE;
		menuAction.stateMachineEnum = SIGNAL_SCALE;
		return menuAction;
	}
	else if (buttonPressed.name == "O-") {
		menuAction.signalScaleEnum = DECREASE_OFFSET;
		menuAction.stateMachineEnum = SIGNAL_SCALE;
		return menuAction;
	}
	else if (buttonPressed.name == "O+") {
		menuAction.signalScaleEnum = INCREASE_OFFSET;
		menuAction.stateMachineEnum = SIGNAL_SCALE;
		return menuAction;
	}
	else if (buttonPressed.name == "F-") {
		menuAction.signalScaleEnum = DECREASE_FREQUENCY;
		menuAction.stateMachineEnum = SIGNAL_SCALE;
		return menuAction;
	}
	else if (buttonPressed.name == "F+") {
		menuAction.signalScaleEnum = INCREASE_FREQUENCY;
		menuAction.stateMachineEnum = SIGNAL_SCALE;
		return menuAction;
	}
	else if (buttonPressed.name == "SNAP") {
		menuAction.signalScaleEnum = NOT_DEFINED;
		menuAction.stateMachineEnum = SNAPSHOT;
		return menuAction;
	}
	else if (buttonPressed.name == "MENU") {
		menuAction.signalScaleEnum = NOT_DEFINED;
		menuAction.stateMachineEnum = MAIN_MENU;
		return menuAction;
	}
	else if (buttonPressed.name == "SCALE") {
		menuAction.signalScaleEnum = NOT_DEFINED;
		menuAction.stateMachineEnum = SCALE_MENU;
		return menuAction;
	}
	else {
		menuAction.signalScaleEnum = NOT_DEFINED;
		menuAction.stateMachineEnum = SIGNAL_DRAW;
		return menuAction;
	}
	delay(200);
}



void SignalDrawerMenuHandler::drawMenu()
{

	tft->fillScreen(ILI9341_LIGHTGREY);
	for (int i = 0; i < 9; i++) {
		drawButton(buttonArray[i]);
	}
}


Button SignalDrawerMenuHandler::whatButtonWasPressed(TS_Point p)
{
	Button buttonPressed;

	if (p.x > 2700) {
		buttonPressed.row = 0;
	}
	else if (p.x >= 1400) {
		buttonPressed.row = 1;
	}
	else if (p.x < 1400) {
		buttonPressed.row = 2;
	}

	if (p.y <= 1300) {
		buttonPressed.column = 0;
	}
	else if (p.y <= 2600) {
		buttonPressed.column = 1;
	}
	else if (p.y > 2600) {
		buttonPressed.column = 2;
	}

	bool recognized = false;
	int number;

	for (int i = 0; i < 9; i++) {
		if (buttonArray[i] == buttonPressed) {
			recognized = true;
			number = i;
			break;
		}
	}

	if (recognized) {
		return buttonArray[number];
	}
	else{
		return buttonPressed;
	}
}

		

void SignalDrawerMenuHandler::createButtonArray()
{
	buttonArray[0] = Button(0, 0, "O+", ILI9341_BLUE);
	buttonArray[1] = Button(0, 1, "SNAP", ILI9341_YELLOW);
	buttonArray[2] = Button(0, 2, "A+", ILI9341_BLUE);
	buttonArray[3] = Button(1, 0, "O-", ILI9341_WHITE);
	buttonArray[4] = Button(1, 1, "MENU", ILI9341_RED);
	buttonArray[5] = Button(1, 2, "A-", ILI9341_WHITE);
	buttonArray[6] = Button(2, 0, "F-", ILI9341_DARKGREEN);
	buttonArray[7] = Button(2, 1, "SCALE", ILI9341_PURPLE);
	buttonArray[8] = Button(2, 2, "F+", ILI9341_DARKGREEN);
}


void SignalDrawerMenuHandler::createButtonAppearance() {

	for (int i = 0; i < 9; i++){
		if (buttonArray[i].column != 1) {
			buttonArray[i].setAppearance(8 + (buttonArray[i].column * 215)/2 , 8 + buttonArray[i].row * 76, 90, 71, 15, ILI9341_BLACK);
		}
		else {
			buttonArray[i].setAppearance(103, 8 + buttonArray[i].row * 76, 115, 71, 15, ILI9341_BLACK);
		}
	}

	for (int i = 0; i < 9; i++) {
		if (buttonArray[i].column != 1) {
			buttonArray[i].setCursor(30 + buttonArray[i].column * 110, 25 + buttonArray[i].row * 80, 4);
		}
		else {
			buttonArray[i].setCursor(5+ buttonArray[i].column * 110, 25 + buttonArray[i].row * 80, 4);
		}
	}

	buttonArray[7].textSize = 3;
}

void SignalDrawerMenuHandler::drawButton(Button b) {

	tft->fillRoundRect(b.x0, b.y0, b.width, b.height, b.radius, b.color);
	tft->setTextColor(b.nameColor);
	tft->setTextSize(b.textSize);
	tft->setCursor(b.cursor_x, b.cursor_y);
	tft->print(b.name);
}

SignalDrawerMenuHandler::SignalDrawerMenuHandler(ILI9341_t3 * tft)
{
	this->tft = tft;
	createButtonArray();
	createButtonAppearance();
}

