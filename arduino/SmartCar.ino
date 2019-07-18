#include "UltrasonicAO.h"
#include "InfraredTrack.h"

#include "BluetoothControl.h"
#include "PS2xControl.h"
#include "InfraredControl.h"

#define UltrasonicAOMode 0
#define InfraredTrackMode 1
#define FollowMode 2
#define InfraredCtrlMode 3
#define BluetoothCtrlMode 4
#define PS2xCtrlMode 5

#define USE_SOFTSERIAL

MotorDriver driver(5, 6, 9, 10);

uint8_t mode = -1;
Control *control = NULL;

void setup() {
  mode = 0;

  Serial.begin(9600);
  Serial.println("AiCar started.");
}

void loop() {

  uint8_t newMode = 0;

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
#ifdef USE_SOFTSERIAL
        control = new BluetoothControl(2, 3, 9600);
#else
        control = new BluetoothControl();
#endif                
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
