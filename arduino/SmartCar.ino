
SerialWrapper mySerial;
//#include "SoftSerialWrapper.h"
//SoftSerialWrapper mySerial(2, 3, 9600);

#include "UltrasonicAO.h"
#include "InfraredTrack.h"

#include "BluetoothControl.h"
#include "PS2xControl.h"
#include "InfraredControl.h"

#include "ModeSelector.h"

#define UltrasonicAOMode 1
#define InfraredTrackMode 2
#define FollowMode 3
#define InfraredCtrlMode 4
#define BluetoothCtrlMode 5
#define PS2xCtrlMode 6

ModeSelector modeSel(A0);
MotorDriver driver(5, 6, 9, 10);

uint8_t mode = 0;
Control *control = NULL;

void setup() {

  Serial.begin(9600);
  Serial.println("AiCar started.");
}

void loop() {

  uint8_t newMode = modeSel.GetMode();

  if (newMode != mode)
  {
    if (control != NULL)
    {
       delete control;
       control = NULL;
    }
    
    switch (mode)
    {
      case UltrasonicAOMode:
        control = new UltrasonicAO(7, 8, 4);
        break;
      case InfraredTrackMode:
        control = new InfraredTrack(A0, A1);
        break;
      case InfraredCtrlMode:
        control = new InfraredControl(3);
        break;
      case BluetoothCtrlMode:
        control = new BluetoothControl(mySerial);
        break;
      case PS2xCtrlMode:
        control = new PS2xControl(11, 12, 13, 5);
        break;
    }  
    
    if (control == NULL)
    {
      Serial.println("cannot create control.");
      return;
    }
    
    mode = newMode;
  }
  
  control->Execute(driver);
  
}
