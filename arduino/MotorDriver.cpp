#include "MotorDriver.h"

MotorDriver::MotorDriver(uint8_t leftIn1, uint8_t leftIn2, uint8_t rightIn1, uint8_t rightIn2)
{
   pinMode(leftIn1, OUTPUT);
   pinMode(leftIn2, OUTPUT);
   pinMode(rightIn1, OUTPUT);
   pinMode(rightIn2, OUTPUT);

   mLeftIn1 = leftIn1;
   mLeftIn2 = leftIn2;
   mRightIn1 = rightIn1;
   mRightIn2 = rightIn2;
}

void MotorDriver::Drive(uint8_t in1, uint8_t in2, uint8_t in3, uint8_t in4) {
  analogWrite(mLeftIn1, in1);
  analogWrite(mLeftIn2, in2);
  analogWrite(mRightIn1, in3);
  analogWrite(mRightIn2, in4);
}

MotorDriver::Forward(uint8_t power)
{
  Drive(power, MotoNoPower, MotoNoPower, power);
}

MotorDriver::Backward(uint8_t power)
{
   Drive(MotoNoPower, power, power, MotoNoPower);
}

MotorDriver::TurnLeft(uint8_t power)
{
  Drive(MotoPowerTurnMax, MotoNoPower, MotoNoPower, power);
}

MotorDriver::TurnRight(uint8_t power)
{
  Drive(power, MotoNoPower, MotoNoPower, MotoPowerTurnMax);
}

MotorDriver::Stop()
{
  Serial.println("car stop");
  Drive(MotoNoPower, MotoNoPower, MotoNoPower, MotoNoPower);
}


MotorDriver::~MotorDriver()
{
  
}
