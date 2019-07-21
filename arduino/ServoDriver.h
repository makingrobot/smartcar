#ifndef __SERVO_DRIVER_H_
#define __SERVO_DRIVER_H_
#pragma once

#include "ServoDriver.h"
#include "Servo.h"

class ServoDriver
{
   public:
     ServoDriver(uint8_t servoPin);
     ~ServoDriver();

     void Drive(int angle);

   private:
     Servo *mServo;  
};

#endif
