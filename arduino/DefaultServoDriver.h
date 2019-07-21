#ifndef __DEFAULT_SERVO_DRIVER_H_
#define __DEFAULT_SERVO_DRIVER_H_
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
