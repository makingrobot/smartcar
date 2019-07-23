/* SmartCar - makingrobot.net
 * Copyright MakingRobot 2018
 * MIT License
 */
#ifndef _ULTRASONIC_FL_H_
#define _ULTRASONIC_FL_H_

#include "SelfControl.h"
#include "ServoDriver.h"

class UltrasonicFL : public SelfControl
{
   public:
     UltrasonicFL(uint8_t echoPin, uint8_t trigPin, ServoDriver *servoDriver);
     ~UltrasonicFL();

    void Execute(MotorDriver driver, Output output) override;
    
  private:
    void LookForward();
    float CheckDistance();  
    
    ServoDriver *mServoDriver;
    uint8_t mTrigPin;
    uint8_t mEchoPin;

};

#endif
