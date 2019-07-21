#ifndef __DISPLAY_H_
#define __DISPLAY_H_
#pragma once

#include <Arduino.h>

class Display
{
  public:
    Display() {};
    virtual void Show(char* text, uint8_t line) {};
};

#endif
