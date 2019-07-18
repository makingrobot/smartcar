#ifndef __INFRARED_CONTROL_H_
#define __INFRARED_CONTROL_H_

#include "RemoteControl.h"
#include <IRremote.h>

class InfraredControl : public RemoteControl
{
  public:
    InfraredControl(uint8_t inPin);
    ~InfraredControl();

  protected:
    virtual void ReadInput();

  private:
    IRrecv *mIRrecv;
    decode_results mResults;
  
};

#endif
