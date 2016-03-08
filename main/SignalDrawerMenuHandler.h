
#ifndef SIGNAL_MENU_H
#define SIGNAL_MENU_H

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif

#include "SignalScaleHandler.h"
#include <XPT2046_Touchscreen.h>
#include "MenuHandler.h"
#include "SignalScaleActionsEnum.h"

class SignalDrawerMenuHandler : public MenuHandler
{
private:

	ILI9341_t3* tft;
	Button buttonArray[9];
	void drawBlankMenu3x3(uint16_t color);
	MenuAction menuAction;
	virtual Button whatButtonWasPressed(TS_Point p) override;
	virtual void createButtonArray() override;
	virtual void drawButton(Button b) override;
	virtual void createButtonAppearance() override;

public:
	SignalDrawerMenuHandler(ILI9341_t3 * tft);
	virtual MenuAction handleTouch(TS_Point p) override;
	virtual void drawMenu() override;
};

#endif