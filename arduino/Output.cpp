/* SmartCar - makingrobot.net
 * Copyright MakingRobot 2018
 * MIT License
 */
#include "Output.h"
#include "Display.h"
#include "LedController.h"

Output::Output(Display *display, LedController *ledController)
{
  mDisplay = display;  
  mLedController = ledController;
}

void Output::Show(char* text, uint8_t line)
{
  mDisplay->Show(text, line);
}

void Output::TurnHeadLed(uint8_t mode)
{
  mLedController->TurnHeadLed(mode);
}

void Output::TurnStopLed(uint8_t mode)
{
  mLedController->TurnStopLed(mode);
}
    
void Output::BlinkLeftLed()
{
  mLedController->BlinkLeftLed();
}

void Output::BlinkRightLed()
{
  mLedController->BlinkRightLed();
}
    
Output::~Output()
{
}
