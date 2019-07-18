#include "UltrasonicAO.h"

#define KeepAway 25//离障碍最近距离
#define LookDelay 300//转动舵机的停顿时间
#define TurnDelay 500//转向停顿时间，通过停顿时间控制转弯角度大小
#define BackDelay 600//倒退时间
#define ReboundDelay 150 //反弹时间

void UltrasonicAO::Servo(uint16_t angle) { //定义一个脉冲函数
  //发送50个脉冲
  for(int i=0;i<50;i++){
    int pulsewidth = (angle * 11) + 500; //将角度转化为500-2480的脉宽值
    digitalWrite(nSeroPin, HIGH);   //将舵机接口电平至高
    delayMicroseconds(pulsewidth);  //延时脉宽值的微秒数
    digitalWrite(nSeroPin, LOW);    //将舵机接口电平至低
    delayMicroseconds(20000 - pulsewidth);
  }
  delay(100);
}

void UltrasonicAO::LookAngle(uint16_t angle) {
  Servo(angle);
  delay(LookDelay);
}

void UltrasonicAO::LookForward() {//向前看
  Servo(90);
  delay(LookDelay);
}

float UltrasonicAO::CheckDistance() {//超声波探测障碍物距离函数
  float distance;
  digitalWrite(nTrigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(nTrigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(nTrigPin, LOW);
  // 检测脉冲宽度，并计算出距离
  distance = pulseIn(nEchoPin, HIGH) / 58.00;

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


UltrasonicAO::UltrasonicAO(uint8_t echoPin, uint8_t trigPin, uint8_t seroPin)
{
  nSeroPin = seroPin;
  
  pinMode(echoPin, INPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(seroPin, OUTPUT);
}

void UltrasonicAO::Execute(MotorDriver driver)
{
   LookForward();//调整超声波探测模块向前看
  int distance = CheckDistance();//查看距离
  if (distance > KeepAway) {//如果距离大于最小距离
    driver.Forward(MotoPowerMax);//一直向前
  } else {
    for (int i = 0; i < 100; i++)
    {
      driver.Stop();
      //goRebound();
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
      driver.Backward(MotoPowerMin);
      delay(BackDelay);
      driver.Stop();
    }
  }
}

UltrasonicAO::~UltrasonicAO()
{
  
}
