#ifndef MENU_H
#define MENU_H

#include <ILI9341_t3.h>
#include <XPT2046_Touchscreen.h>
#include "Button.h"
#include<WProgram.h>
#include "SignalScaleActionsEnum.h"


class MenuHandler
{
protected:
	ILI9341_t3* tft;
	void drawBlank();
	virtual Button whatButtonWasPressed(TS_Point p) = 0;
	virtual void createButtonArray() = 0;
	virtual void drawButton(Button b) = 0;
public:
	virtual MenuAction handleTouch(TS_Point p) = 0;
	virtual void drawMenu() = 0;
};

#endif