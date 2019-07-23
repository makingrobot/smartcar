/* SmartCar - makingrobot.net
 * Copyright MakingRobot 2018
 * MIT License
 */
#ifndef _LED_CONTROLLER_H_
#define _LED_CONTROLLER_H_
#pragma once

#include <Arduino.h>

class LedController
{
  public:
    LedController() {};
    
    virtual void TurnHeadLed(uint8_t mode) {}; // 前灯
    virtual void TurnStopLed(uint8_t mode) {}; // 刹车灯
    virtual void BlinkLeftLed() {}; // 左转向灯
    virtual void BlinkRightLed() {}; // 右转向灯
};

#endif
