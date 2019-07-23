/* SmartCar - makingrobot.net
 * Copyright MakingRobot 2018
 * MIT License
 */
#ifndef _REMOTE_CONTROL_H_
#define _REMOTE_CONTROL_H_
#pragma once

#include "Control.h"

class RemoteControl : public Control
{
   public:
     void Execute(MotorDriver driver, Output output) override;
     
   protected:
     virtual void ReadInput();
     
     uint8_t leftPressState=0;
     uint8_t rightPressState=0;
     uint8_t forwardPressState=0;
     uint8_t backwardPressState=0;
     uint8_t accelPressState=0;
     uint8_t stopPressState=0;
     
    int carAngleValue=0;
    int carAccelValue=0;

};

#endif
