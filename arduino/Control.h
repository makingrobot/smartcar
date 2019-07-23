/* SmartCar - makingrobot.net
 * Copyright MakingRobot 2018
 * MIT License
 */
#ifndef _CONTROL_H_
#define _CONTROL_H_
#pragma once

#include <Arduino.h>
#include "MotorDriver.h"
#include "Output.h"

class Control
{
   public:
     virtual void Execute(MotorDriver driver, Output output);

};

#endif
