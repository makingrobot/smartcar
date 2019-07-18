#ifndef __REMOTE_CONTROL_H_
#define __REMOTE_CONTROL_H_
#pragma once

#include "Control.h"

class RemoteControl : public Control
{
   public:
     virtual void Execute(MotorDriver driver);
     
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
