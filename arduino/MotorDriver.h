/* SmartCar - makingrobot.net
 * Copyright MakingRobot 2018
 * MIT License
 */
#ifndef _MOTOR_DRIVER_H_
#define _MOTOR_DRIVER_H_
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

  private:
    void Drive(uint8_t in1, uint8_t in2, uint8_t in3, uint8_t in4);
   
    uint8_t mLeftIn1;
    uint8_t mLeftIn2;
    uint8_t mRightIn1;
    uint8_t mRightIn2;

};

#endif
