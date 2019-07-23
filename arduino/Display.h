/* SmartCar - makingrobot.net
 * Copyright MakingRobot 2018
 * MIT License
 */
#ifndef _DISPLAY_H_
#define _DISPLAY_H_
#pragma once

#include <Arduino.h>

class Display
{
  public:
    Display() {};
    virtual void Show(char* text, uint8_t line) {};
};

#endif
