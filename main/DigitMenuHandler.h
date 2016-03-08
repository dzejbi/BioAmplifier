// DigitMenuHandler.h

#ifndef _DIGITMENUHANDLER_h
#define _DIGITMENUHANDLER_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "MenuHandler.h"
#include <ILI9341_t3.h>

class DigitMenuHandler : public MenuHandler
{

 private:
	 ILI9341_t3* tft;
	 Button buttonArray[13];
	 virtual void createButtonAppearance() override;
	 virtual Button whatButtonWasPressed(TS_Point p) override;
	 virtual void createButtonArray() override;
	 virtual void drawButton(Button b) override;

 public:
	 DigitMenuHandler(ILI9341_t3* tft);
	 virtual MenuAction handleTouch(TS_Point p) override;
	 virtual void drawMenu() override;
};


#endif

