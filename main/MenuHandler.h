#ifndef MENU_H
#define MENU_H

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif

#include <ILI9341_t3.h>
#include <XPT2046_Touchscreen.h>
#include "Button.h"
#include "SignalScaleActionsEnum.h"


class MenuHandler
{
protected:
	ILI9341_t3* tft;
	void drawBlank();
	virtual void drawButton(Button b) = 0;
	virtual Button whatButtonWasPressed(TS_Point p) = 0;
	virtual void createButtonArray() = 0;
	virtual void createButtonAppearance() = 0;
public:
	virtual MenuAction handleTouch(TS_Point p) = 0;
	virtual void drawMenu() = 0;
};

#endif