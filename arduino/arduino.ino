/* SmartCar - makingrobot.net
 * Copyright MakingRobot 2018
 * MIT License
 */
#define USE_SOFTSERIAL

#include "ADC8Selector.h"
#include "Output.h"

#include "UltrasonicAO.h"
#include "UltrasonicFL.h"
#include "InfraredTrack.h"
#include "PS2xControl.h"
#include "InfraredControl.h"

#include "SerialWrapper.h"
#include "BluetoothControl.h"
#include "ServoDriver.h"
#include "LcdDisplay.h"

//Control Mode
#define PS2X_CTRL_MODE          1
#define BLUETOOTH_CTRL_MODE     2
#define INFRARED_CTRL_MODE      3
#define ULTRASONIC_AO_MODE      4
#define ULTRASONIC_FL_MODE      5
#define INFRARED_TRACK_MODE     6

//Digital Pin
#define INFRARED_CTRL_IN      2
#define SERVO_OUT             3  //PWM
#define PS2_ATTENTION         4
#define MOTOR_LEFT_IN1        5  //PWM
#define MOTOR_LEFT_IN2        6  //PWM
#define ULTRASONIC_ECHO       7
#define ULTRASONIC_TRIG       8
#define MOTOR_RIGHT_IN1       9  //PWM
#define MOTOR_RIGHT_IN2       10  //PWM
#define PS2_COMMAND           11  //SPI
#define PS2_CLOCK             12  //SPI
#define PS2_DATA              13  //SPI

//Analog Pin
#define INFRARED_LEFT_IN      A0
#define INFRARED_RIGHT_IN     A1
#define ADC8_SELECTOR_IN      A3
#define TWI_CLOCK             A4  //TWI
#define TWI_DATA              A5  //TWI

#ifdef USE_SOFTSERIAL
#include "SoftSerialWrapper.h"
#include "CustomServoDriver.h"
ServoDriver *servoDriver = new CustomServoDriver(SERVO_OUT);
SerialWrapper *mySerial = new SoftSerialWrapper(2, 3, 9600);
#else
#include "DefaultServoDriver.h"
ServoDriver *servoDriver = new DefaultServoDriver(SERVO_OUT);
SerialWrapper *mySerial = new SerialWrapper();
#endif

Display *display = new Display(); //LcdDisplay(0x0, 20, 4);
LedController *ledController = new LedController();

MotorDriver motorDriver(MOTOR_LEFT_IN1, MOTOR_LEFT_IN2, MOTOR_RIGHT_IN1, MOTOR_RIGHT_IN2);
Output output(display, ledController);
ADC8Selector modeSel(ADC8_SELECTOR_IN);
Control *control = NULL;

uint8_t mode = 0;

void setup() {

  Serial.begin(9600);
  Serial.println("AiCar started.");
}

void loop() {

  uint8_t newMode = modeSel.GetMode();

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
      case PS2X_CTRL_MODE:
        control = new PS2xControl(PS2_CLOCK, PS2_COMMAND, PS2_DATA, PS2_ATTENTION);
        break;
      case BLUETOOTH_CTRL_MODE:
        control = new BluetoothControl(mySerial);
        break;
      case INFRARED_CTRL_MODE:
        control = new InfraredControl(INFRARED_CTRL_IN);
        break;
      case ULTRASONIC_AO_MODE:
        control = new UltrasonicAO(ULTRASONIC_ECHO, ULTRASONIC_TRIG, servoDriver);
        break;
      case ULTRASONIC_FL_MODE:
        control = new UltrasonicFL(ULTRASONIC_ECHO, ULTRASONIC_TRIG, servoDriver);
        break;  
      case INFRARED_TRACK_MODE:
        control = new InfraredTrack(INFRARED_LEFT_IN, INFRARED_RIGHT_IN);
        break;
    }  
    
    if (control == NULL)
    {
      Serial.println("cannot create control.");
      return;
    }
    
    mode = newMode;
  }
  
  control->Execute(motorDriver, output);
  
}
