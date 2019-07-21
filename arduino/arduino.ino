#include "UltrasonicAO.h"
#include "UltrasonicFL.h"
#include "InfraredTrack.h"
#include "PS2xControl.h"
#include "InfraredControl.h"

#include "SerialWrapper.h"
#include "BluetoothControl.h"

#include "ADC8Selector.h"
//#include "SoftSerialWrapper.h"

//Control Mode
#define PS2xCtrlMode          1
#define BluetoothCtrlMode     2
#define InfraredCtrlMode      3
#define UltrasonicAOMode      4
#define UltrasonicFLMode      5
#define InfraredTrackMode     6

//Digital Pin
#define Infrared_Ctrl_In      2
#define Servo_Out             3  //PWM
#define PS2x_Attention        4
#define Motor_LeftIn1         5  //PWM
#define Motor_LeftIn2         6  //PWM
#define Ultrasonic_Echo       7
#define Ultrasonic_Trig       8
#define Motor_RightIn1        9  //PWM
#define Motor_RightIn2        10  //PWM
#define PS2x_Command          11  //SPI
#define PS2x_Clock            12  //SPI
#define PS2x_Data             13  //SPI

//Analog Pin
#define Infrared_Left         A0
#define Infrared_Right        A1
#define ADC8_Selector         A3
#define TWI_Clock             A4  //TWI
#define TWI_Data              A5  //TWI 

MotorDriver driver(Motor_LeftIn1, Motor_LeftIn2, Motor_RightIn1, Motor_RightIn2);

ModeSelector *modeSel = NULL;
Control *control = NULL;
SerialWrapper *mySerial = NULL;

uint8_t mode = 0;

void setup() {

  Serial.begin(9600);
  Serial.println("AiCar started.");

  modeSel = new ADC8Selector(ADC8_Selector);
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
        control = new PS2xControl(PS2x_Clock, PS2x_Command, PS2x_Data, PS2x_Attention);
        break;
      case BluetoothCtrlMode:
        control = new BluetoothControl(mySerial);
        break;
      case InfraredCtrlMode:
        control = new InfraredControl(Infrared_Ctrl_In);
        break;
      case UltrasonicAOMode:
        control = new UltrasonicAO(Ultrasonic_Echo, Ultrasonic_Trig, Servo_Out);
        break;
      case UltrasonicFLMode:
        control = new UltrasonicFL(Ultrasonic_Echo, Ultrasonic_Trig, Servo_Out);
        break;  
      case InfraredTrackMode:
        control = new InfraredTrack(Infrared_Left, Infrared_Right);
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
