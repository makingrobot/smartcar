#ifndef __CONTROL_H_
#define __CONTROL_H_
#pragma once

#include "Arduino.h"
#include "MotorDriver.h"

class Control
{
   public:
     virtual void Execute(MotorDriver driver);

};

#endif
