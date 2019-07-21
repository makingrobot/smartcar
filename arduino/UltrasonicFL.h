#ifndef __ULTRASONIC_FL_H_
#define __ULTRASONIC_FL_H_

#include "SelfControl.h"
#include "ServoDriver.h"

class UltrasonicFL : public SelfControl
{
   public:
     UltrasonicFL(uint8_t echoPin, uint8_t trigPin, uint8_t servoPin);
     ~UltrasonicFL();

    void Execute(MotorDriver driver) override;
    
  private:
    void LookForward();
    float CheckDistance();  
    
    ServoDriver *mServoDriver;
    uint8_t mTrigPin;
    uint8_t mEchoPin;

};

#endif
