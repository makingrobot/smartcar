/* SmartCar - makingrobot.net
 * Copyright MakingRobot 2018
 * MIT License
 */
#ifndef _LCD_DISPLAY_H_
#define _LCD_DISPLAY_H_
#pragma once

#include "Display.h"

class LcdDisplay : public Display
{
  public:
    LcdDisplay(uint8_t address, uint8_t chars, uint8_t lines);
    ~LcdDisplay();

    void Show(const String &text, uint8_t line) override;
    
};

#endif
