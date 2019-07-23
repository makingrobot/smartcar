/* SmartCar - makingrobot.net
 * Copyright MakingRobot 2018
 * MIT License
 */
#ifndef _INFRARED_CONTROL_H_
#define _INFRARED_CONTROL_H_

#include "RemoteControl.h"
#include <IRremote.h>

class InfraredControl : public RemoteControl
{
  public:
    InfraredControl(uint8_t inPin);
    ~InfraredControl();

  protected:
    void ReadInput() override;

  private:
    IRrecv *mIRrecv;
    decode_results mResults;
  
};

#endif
