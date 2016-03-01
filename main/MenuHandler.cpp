#include "MenuHandler.h"
#include <ILI9341_t3.h>

void MenuHandler::drawBlank()
{
	tft->fillScreen(ILI9341_BLACK);
}
