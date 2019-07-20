#include "UltrasonicAO.h"
#include "UltrasonicFL.h"
#include "InfraredTrack.h"
#include "PS2xControl.h"
#include "InfraredControl.h"

#include "SerialWrapper.h"
#include "BluetoothControl.h"

#include "ADC8Selector.h"

#define PS2xCtrlMode 1
#define BluetoothCtrlMode 2
#define InfraredCtrlMode 3
#define UltrasonicAOMode 4
#define UltrasonicFLMode 5
#define InfraredTrackMode 6

//#include "SoftSerialWrapper.h"

MotorDriver driver(5, 6, 9, 10);

ModeSelector *modeSel = NULL;
Control *control = NULL;
SerialWrapper *mySerial = NULL;

uint8_t mode = 0;

void setup() {

  Serial.begin(9600);
  Serial.println("AiCar started.");

  modeSel = new ADC8Selector(A2);
  mySerial = new SerialWrapper();
//  mySerial = new SoftSerialWrapper(2, 3, 9600);
}

void loop() {

  uint8_t newMode = modeSel->GetMode();

  if (newMode != mode)
  {
    Serial.print("new mode:");
    Serial.println(newMode);
    
    if (control != NULL)
    {
       delete control;
       control = NULL;
    }
    
    switch (newMode)
    {
      case PS2xCtrlMode:
        control = new PS2xControl(12, 11, 13, 4);
        break;
      //case BluetoothCtrlMode:
      //  control = new BluetoothControl(mySerial);
      //  break;
      case InfraredCtrlMode:
        control = new InfraredControl(3);
        break;
      case UltrasonicAOMode:
        control = new UltrasonicAO(7, 8, 4);
        break;
      case UltrasonicFLMode:
        control = new UltrasonicFL(7, 8, 4);
        break;  
      case InfraredTrackMode:
        control = new InfraredTrack(A0, A1);
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
