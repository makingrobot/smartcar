#ifndef __LCD_DISPLAY_H_
#define __LCD_DISPLAY_H_
#pragma once

#include "Display.h"

class LcdDisplay : public Display
{
  public:
    LcdDisplay(uint8_t address, uint8_t chars, uint8_t lines);
    ~LcdDisplay();

    void Show(char* text, uint8_t line) override;
    
};

#endif
