#ifndef __ULTRASONIC_AO_H_
#define __ULTRASONIC_NO_H_

#include "SelfControl.h"
#include "ServoDriver.h"

class UltrasonicAO : public SelfControl
{
   public:
     UltrasonicAO(uint8_t echoPin, uint8_t trigPin, uint8_t servoPin);
     ~UltrasonicAO();

    void Execute(MotorDriver driver) override;

  private:
    void LookForward();
    int LookAround();
    void LookAngle(uint16_t angle);
    float CheckDistance();  
    
    ServoDriver *mServoDriver;
    uint8_t mTrigPin;
    uint8_t mEchoPin;
};

#endif
