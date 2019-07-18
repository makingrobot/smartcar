#ifndef __ULTRASONIC_FL_H_
#define __ULTRASONIC_FL_H_

#include "SelfControl.h"

class UltrasonicFL : public SelfControl
{
   public:
     UltrasonicFL(uint8_t echoPin, uint8_t trigPin, uint8_t seroPin);
     ~UltrasonicFL();

    virtual void Execute(MotorDriver driver);
    
  private:
    void Servo(uint16_t angle);
    void LookForward();
    float CheckDistance();  
    
    uint8_t nSeroPin;
    uint8_t nTrigPin;
    uint8_t nEchoPin;

};

#endif
