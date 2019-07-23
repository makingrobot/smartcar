/* SmartCar - makingrobot.net
 * Copyright MakingRobot 2018
 * MIT License
 */
#include "CustomServoDriver.h"

CustomServoDriver::CustomServoDriver(uint8_t servoPin)
{
  mServoPin = servoPin;
}

void CustomServoDriver::Drive(int angle)
{
    //发送50个脉冲
  for(int i=0;i<50;i++){
    int pulsewidth = (angle * 11) + 500; //将角度转化为500-2480的脉宽值
    digitalWrite(mServoPin, HIGH);   //将舵机接口电平至高
    delayMicroseconds(pulsewidth);  //延时脉宽值的微秒数
    digitalWrite(mServoPin, LOW);    //将舵机接口电平至低
    delayMicroseconds(20000 - pulsewidth);
  }
  delay(100);
}

CustomServoDriver::~CustomServoDriver()
{
}
