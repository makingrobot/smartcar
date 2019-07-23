/* SmartCar - makingrobot.net
 * Copyright MakingRobot 2018
 * MIT License
 */
#ifndef _ULTRASONIC_AO_H_
#define _ULTRASONIC_NO_H_

#include "SelfControl.h"
#include "ServoDriver.h"

class UltrasonicAO : public SelfControl
{
   public:
     UltrasonicAO(uint8_t echoPin, uint8_t trigPin, ServoDriver *servoDriver);
     ~UltrasonicAO();

    void Execute(MotorDriver driver, Output output) override;

  private:
    void LookForward();
    int LookAround();
    void LookAngle(int angle);
    float CheckDistance();  
    
    ServoDriver *mServoDriver;
    uint8_t mTrigPin;
    uint8_t mEchoPin;
};

#endif
