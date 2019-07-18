#ifndef __PS2X_CONTROL_H_
#define __PS2x_CONTROL_H_

#include "RemoteControl.h"

class PS2xControl : public RemoteControl
{
  public:
    PS2xControl(uint8_t cmd, uint8_t clk, uint8_t dat, uint8_t cs);
    ~PS2xControl();

  protected:  
    virtual void ReadInput();
};

#endif
