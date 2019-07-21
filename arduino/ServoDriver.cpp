#include "ServoDriver.h"
#include "Servo.h"

ServoDriver::ServoDriver(uint8_t servoPin)
{
  mServo = new Servo();
  mServo->attach(servoPin);
}

void ServoDriver::Drive(int angle)
{
  mServo->write(angle);
}

ServoDriver::~ServoDriver()
{
  delete mServo;
}
