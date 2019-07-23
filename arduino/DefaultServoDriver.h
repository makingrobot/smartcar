/* SmartCar - makingrobot.net
 * Copyright MakingRobot 2018
 * MIT License
 */
#ifndef _DEFAULT_SERVO_DRIVER_H_
#define _DEFAULT_SERVO_DRIVER_H_
#pragma once

#include "ServoDriver.h"
#include <Servo.h>

class DefaultServoDriver : public ServoDriver
{
   public:
     DefaultServoDriver(uint8_t servoPin);
     ~DefaultServoDriver();

     void Drive(int angle) override;

   private:
     Servo *mServo;  
};

#endif
