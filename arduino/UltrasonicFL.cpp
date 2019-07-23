/* SmartCar - makingrobot.net
 * Copyright MakingRobot 2018
 * MIT License
 */
#include "UltrasonicFL.h"
#include "ServoDriver.h"

#define KeepAway 25//离障碍最近距离
#define LookDelay 300//转动舵机的停顿时间
#define TurnDelay 500//转向停顿时间，通过停顿时间控制转弯角度大小
#define BackDelay 600//倒退时间
#define ReboundDelay 150 //反弹时间

UltrasonicFL::UltrasonicFL(uint8_t echoPin, uint8_t trigPin, ServoDriver *servoDriver)
{
  mEchoPin = echoPin;
  mTrigPin = trigPin;
  mServoDriver = servoDriver;
  
  pinMode(echoPin, INPUT);
  pinMode(trigPin, OUTPUT);
}

void UltrasonicFL::Execute(MotorDriver driver, Output output)
{
   LookForward();//调整超声波探测模块向前看
   int distance = CheckDistance();//查看距离
  if (distance > KeepAway) {//如果距离大于最小距离
    driver.Forward(MotoPowerMax);//一直向前
  } else {
    
  }
}

void UltrasonicFL::LookForward() {//向前看
  mServoDriver->Drive(90);
  delay(LookDelay);
}

float UltrasonicFL::CheckDistance() {//超声波探测障碍物距离函数
  float distance;
  digitalWrite(mTrigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(mTrigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(mTrigPin, LOW);
  // 检测脉冲宽度，并计算出距离
  distance = pulseIn(mEchoPin, HIGH) / 58.00;

  Serial.print("Distance:");
  Serial.print(distance);
  Serial.print("cm");
  Serial.println();
  
  return distance;
}

UltrasonicFL::~UltrasonicFL()
{
}
