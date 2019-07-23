/* SmartCar - makingrobot.net
 * Copyright MakingRobot 2018
 * MIT License
 */
#ifndef _PCF8574_LED_CONTROLLER_H_
#define _PCF8574_LED_CONTROLLER_H_
#pragma once

#include "LedController.h"

class PCF8574LedController : public LedController
{
  public:
    PCF8574LedController(uint8_t address);
    ~PCF8574LedController();
    
    void TurnHeadLed(uint8_t mode) override; // 前灯
    void TurnStopLed(uint8_t mode) override; // 刹车灯
    void BlinkLeftLed() override; // 左转向灯
    void BlinkRightLed() override; // 右转向灯  
};

#endif
