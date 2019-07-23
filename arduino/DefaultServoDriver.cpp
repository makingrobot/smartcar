/* SmartCar - makingrobot.net
 * Copyright MakingRobot 2018
 * MIT License
 */
#include "DefaultServoDriver.h"
#include <Servo.h>

DefaultServoDriver::DefaultServoDriver(uint8_t servoPin)
{
  mServo = new Servo();
  mServo->attach(servoPin);
}

void DefaultServoDriver::Drive(int angle)
{
  mServo->write(angle);
}

DefaultServoDriver::~DefaultServoDriver()
{
  delete mServo;
}
