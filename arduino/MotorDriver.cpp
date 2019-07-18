#include "MotorDriver.h"

uint8_t nLeftIn1;
uint8_t nLeftIn2;
uint8_t nRightIn1;
uint8_t nRightIn2;

MotorDriver::MotorDriver(uint8_t leftIn1, uint8_t leftIn2, uint8_t rightIn1, uint8_t rightIn2)
{
   pinMode(leftIn1, OUTPUT);
   pinMode(leftIn2, OUTPUT);
   pinMode(rightIn1, OUTPUT);
   pinMode(rightIn2, OUTPUT);

   nLeftIn1 = leftIn1;
   nLeftIn2 = leftIn2;
   nRightIn1 = rightIn1;
   nRightIn2 = rightIn2;
}

void drive(uint8_t in1, uint8_t in2, uint8_t in3, uint8_t in4) {
  analogWrite(nLeftIn1, in1);
  analogWrite(nLeftIn2, in2);
  analogWrite(nRightIn1, in3);
  analogWrite(nRightIn2, in4);
}

MotorDriver::Forward(uint8_t power)
{
  drive(power, MotoNoPower, MotoNoPower, power);
}

MotorDriver::Backward(uint8_t power)
{
   drive(MotoNoPower, power, power, MotoNoPower);
}

MotorDriver::TurnLeft(uint8_t power)
{
  drive(MotoPowerTurnMax, MotoNoPower, MotoNoPower, power);
}

MotorDriver::TurnRight(uint8_t power)
{
  drive(power, MotoNoPower, MotoNoPower, MotoPowerTurnMax);
}

MotorDriver::Stop()
{
  Serial.println("car stop");
  drive(MotoNoPower, MotoNoPower, MotoNoPower, MotoNoPower);
}


MotorDriver::~MotorDriver()
{
  
}
