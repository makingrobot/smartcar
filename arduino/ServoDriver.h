/* SmartCar - makingrobot.net
 * Copyright MakingRobot 2018
 * MIT License
 */
#ifndef _SERVO_DRIVER_H_
#define _SERVO_DRIVER_H_
#pragma once

#include <Arduino.h>

class ServoDriver
{
   public:
     virtual void Drive(int angle);
};

#endif
