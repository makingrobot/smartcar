#ifndef __OUTPUT_H_
#define __OUTPUT_H_
#pragma once

#include "Display.h"
#include "LedController.h"

class Output
{
  public:
    Output(Display *display, LedController *ledController);
    ~Output();

    // led
    void TurnHeadLed(uint8_t mode); // 前灯
    void TurnStopLed(uint8_t mode); // 刹车灯
    void BlinkLeftLed(); // 左转向灯
    void BlinkRightLed(); // 右转向灯

    // screen
    void Show(char* text, uint8_t line);

    // audio
    
  private:
    Display *mDisplay;
    LedController *mLedController;
      
};

#endif
