#ifndef __SERVO_DRIVER_H_
#define __SERVO_DRIVER_H_
#pragma once

#include <Arduino.h>

class ServoDriver
{
   public:
     virtual void Drive(int angle);
};

#endif
