/* SmartCar - makingrobot.net
 * Copyright MakingRobot 2018
 * MIT License
 */
#ifndef _BLUETOOTH_CONTROL_H_
#define _BLUETOOTH_CONTROL_H_

#include "RemoteControl.h"
#include "SerialWrapper.h"

class BluetoothControl : public RemoteControl
{
   public:
     BluetoothControl(SerialWrapper &serial);
     ~BluetoothControl();
     
  protected:
    void ReadInput() override;

  private:
    SerialWrapper &mSerial;
  
};

#endif
