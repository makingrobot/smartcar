#ifndef __MOTOR_DRIVER_H_
#define __MOTOR_DRIVER_H_
#pragma once

#include "Arduino.h"

#define MotoPowerMax 255
#define MotoPowerTurnMax 180
#define MotoPowerMin 120
#define MotoNoPower 0

class MotorDriver
{
  public:
    MotorDriver(uint8_t leftIn1, uint8_t leftIn2, uint8_t rightIn1, uint8_t rightIn2);
    ~MotorDriver();

    Forward(uint8_t power);
    Backward(uint8_t power);
    TurnLeft(uint8_t power);
    TurnRight(uint8_t power);
    Stop();
};

#endif
