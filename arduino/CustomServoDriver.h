/* SmartCar - makingrobot.net
 * Copyright MakingRobot 2018
 * MIT License
 */
#ifndef _CUSTOM_SERVO_DRIVER_H_
#define _CUSTOM_SERVO_DRIVER_H_
#pragma once

#include <Arduino.h>
#include "ServoDriver.h"

class CustomServoDriver : public ServoDriver
{
   public:
     CustomServoDriver(uint8_t servoPin);
     ~CustomServoDriver();

     void Drive(int angle) override;

  private:
    uint8_t mServoPin;
};

#endif
