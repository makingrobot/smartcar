/* SmartCar - makingrobot.net
 * Copyright MakingRobot 2018
 * MIT License
 */
#ifndef _PS2X_CONTROL_H_
#define _PS2x_CONTROL_H_

#include "RemoteControl.h"

class PS2xControl : public RemoteControl
{
  public:
    PS2xControl(uint8_t clk, uint8_t cmd, uint8_t dat, uint8_t cs);
    ~PS2xControl();

  protected:  
    void ReadInput() override;
};

#endif
