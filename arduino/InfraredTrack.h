/* SmartCar - makingrobot.net
 * Copyright MakingRobot 2018
 * MIT License
 */
#ifndef _INFRARED_TRACK_H_
#define _INFRARED_TRACK_H_

#include "SelfControl.h"

class InfraredTrack : public SelfControl
{
  public:
    InfraredTrack(uint8_t leftPin, uint8_t rightPin);
    ~InfraredTrack();

  protected:
    void Execute(MotorDriver driver, Output output) override;

  private:
    int CheckState();
    
    uint8_t mLeftPin;
    uint8_t mRightPin;
  
};

#endif
