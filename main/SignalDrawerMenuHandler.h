
#ifndef SIGNAL_MENU_H
#define SIGNAL_MENU_H

#include<WProgram.h>
#include "SignalScaleHandler.h"
#include <XPT2046_Touchscreen.h>
#include "MenuHandler.h"
#include "SignalScaleActionsEnum.h"

class SignalDrawerMenuHandler : public MenuHandler
{
private:
	// Inherited via MenuHandler
	virtual void drawButton(Button b) override;
	virtual Button whatButtonWasPressed(TS_Point p) override;
	virtual void createButtonArray() override;
	ILI9341_t3* tft;
	Button buttonArray[9];
	void createButtonAppearance();
	void drawBlankMenu3x3(uint16_t color);
	MenuAction menuAction;

public:
	SignalDrawerMenuHandler(ILI9341_t3 * tft);
	// Inherited via MenuHandler
	virtual MenuAction handleTouch(TS_Point p) override;
	virtual void drawMenu() override;
};

#endif