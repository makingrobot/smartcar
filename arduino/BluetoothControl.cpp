#include "BluetoothControl.h"

BluetoothControl::BluetoothControl(SerialWrapper serial)
{
  mSerial = serial;
}

void BluetoothControl::ReadInput()
{
   uint8_t action=0;

  while (mSerial.Available() > 0) {
    uint8_t in = mSerial.Read();
    delay(2);
    if (in == -1)
      continue;

    Serial.println(in, BIN);
    action = in;
  }

  if (action > 64) {
     return;
  }
     
  backwardPressState = (action & 1);
  forwardPressState = (action & 2) >> 1;
  leftPressState = (action & 4) >> 2;
  rightPressState = (action & 8) >> 3;
  accelPressState = (action & 16) >> 4;
  stopPressState = (action & 32) >> 5;

  if (backwardPressState==1) {
    carAngleValue=0;
  } else if (forwardPressState==1) {
    carAngleValue=0;
  } else if (leftPressState==1) {
    if (carAngleValue>-20)
      carAngleValue-=6;
    if (carAngleValue>-35)
      carAngleValue-=4;
    else
      carAngleValue-=2;
    
    if (carAngleValue<-45)
      carAngleValue=-45;
  } else if (rightPressState==-1) {
    if (carAngleValue<20)
      carAngleValue+=6;
    if (carAngleValue<35)
      carAngleValue+=4;
    else
      carAngleValue+=2;
      
    if (carAngleValue>45)
      carAngleValue=45;
  }
  
  if (accelPressState==1) {
     if (carAccelValue < 100)
        carAccelValue+=1;
  } else {
    if (carAccelValue>0) {
      carAccelValue-=1;
    }
  }
  if (stopPressState==1) {
     carAccelValue=0;
     carAngleValue=0;
  }

  // feedback
  mSerial.Write(carAccelValue);
  mSerial.Println();
}

BluetoothControl::~BluetoothControl()
{ 
}
