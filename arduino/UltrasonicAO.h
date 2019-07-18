#ifndef __ULTRASONICAO_H_
#define __ULTRASONICNO_H_

#include "SelfControl.h"

class UltrasonicAO : public SelfControl
{
   public:
     UltrasonicAO(uint8_t echoPin, uint8_t trigPin, uint8_t seroPin);
     ~UltrasonicAO();

    virtual void Execute(MotorDriver driver);
};

#endif
