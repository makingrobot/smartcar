#ifndef __BLUETOOTH_CONTROL_H_
#define __BLUETOOTH_CONTROL_H_

#include "RemoteControl.h"
#include "SerialWrapper.h"

class BluetoothControl : public RemoteControl
{
   public:
     BluetoothControl(SerialWrapper *serial);
     ~BluetoothControl();
     
  protected:
    void ReadInput() override;

  private:
    SerialWrapper *mSerial;
  
};

#endif
