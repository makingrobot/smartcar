#ifndef __BLUETOOTH_CONTROL_H_
#define __BLUETOOTH_CONTROL_H_

#include "RemoteControl.h"

class BluetoothControl : public RemoteControl
{
   public:
     BluetoothControl();
     BluetoothControl(uint8_t txPin, uint8_t rxPin, uint32_t baud);
     ~BluetoothControl();
     
  protected:
    virtual void ReadInput();
};

#endif
