#include "UltrasonicAO.h"
#include "ServoDriver.h"

#define KeepAway 25//离障碍最近距离
#define LookDelay 100//转动舵机的停顿时间
#define TurnDelay 200//转向停顿时间，通过停顿时间控制转弯角度大小
#define BackDelay 200//倒退时间
#define ReboundDelay 150 //反弹时间

UltrasonicAO::UltrasonicAO(uint8_t echoPin, uint8_t trigPin, uint8_t servoPin)
{
  mEchoPin = echoPin;
  mTrigPin = trigPin;
  mServoDriver = new ServoDriver(servoPin);
  
  pinMode(echoPin, INPUT);
  pinMode(trigPin, OUTPUT);
}

void UltrasonicAO::Execute(MotorDriver driver)
{
   LookForward();//调整超声波探测模块向前看
  int distance = CheckDistance();//查看距离
  if (distance > KeepAway) {//如果距离大于最小距离
    driver.Forward(MotoPowerMax);//一直向前
  } else {
    
    driver.Stop();
    driver.Backward(MotoPowerMax);
    delay(ReboundDelay);
    driver.Stop();

    switch (LookAround()) {//判断观察周围情况结果，并执行相应动作
      case 1:
        driver.TurnRight(MotoPowerMin);
        delay(TurnDelay);
        driver.Stop();
        return;
      case 2:
        driver.TurnRight(MotoPowerMin);
        delay(TurnDelay / 2);
        driver.Stop();
        return;
      case 3:
        driver.Forward(MotoPowerMax);
        return;
      case 4:
        driver.TurnLeft(MotoPowerMin);
        delay(TurnDelay / 2);
        driver.Stop();
        return;
      case 5:
        driver.TurnLeft(MotoPowerMin);
        delay(TurnDelay);
        driver.Stop();
        return;
      default:
        break;
    }
    
  }
}


void UltrasonicAO::LookAngle(uint16_t angle) {
  mServoDriver->Drive(angle);
  delay(LookDelay);
}

void UltrasonicAO::LookForward() {//向前看
  mServoDriver->Drive(90);
  delay(LookDelay);
}

float UltrasonicAO::CheckDistance() {//超声波探测障碍物距离函数
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

int UltrasonicAO::LookAround() {//观察周围情况，并返回方向代码
  LookAngle(30);
  int D1 = CheckDistance();
  LookAngle(60);
  int D2 = CheckDistance();
  LookForward();
  int D3 = CheckDistance();
  LookAngle(120);
  int D4 = CheckDistance();
  LookAngle(150);
  int D5 = CheckDistance();
  if (D1 > D2 && D1 > D3 && D1 > D4 && D1 > D5 && D1 > KeepAway)return 1;
  if (D2 > D1 && D2 > D3 && D2 > D4 && D2 > D5 && D2 > KeepAway)return 2;
  if (D3 > D2 && D3 > D1 && D3 > D4 && D3 > D5 && D3 > KeepAway)return 3;
  if (D4 > D2 && D4 > D3 && D4 > D1 && D4 > D5 && D4 > KeepAway)return 4;
  if (D5 > D2 && D5 > D3 && D5 > D4 && D5 > D1 && D5 > KeepAway)return 5;
  return 0;
}

UltrasonicAO::~UltrasonicAO()
{
  delete mServoDriver;
}
