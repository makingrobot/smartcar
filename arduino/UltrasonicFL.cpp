#include "UltrasonicFL.h"

#define KeepAway 25//离障碍最近距离
#define LookDelay 300//转动舵机的停顿时间
#define TurnDelay 500//转向停顿时间，通过停顿时间控制转弯角度大小
#define BackDelay 600//倒退时间
#define ReboundDelay 150 //反弹时间

void UltrasonicFL::Servo(uint16_t angle) { //定义一个脉冲函数
  //发送50个脉冲
  for(int i=0;i<50;i++){
    int pulsewidth = (angle * 11) + 500; //将角度转化为500-2480的脉宽值
    digitalWrite(mSeroPin, HIGH);   //将舵机接口电平至高
    delayMicroseconds(pulsewidth);  //延时脉宽值的微秒数
    digitalWrite(mSeroPin, LOW);    //将舵机接口电平至低
    delayMicroseconds(20000 - pulsewidth);
  }
  delay(100);
}

void UltrasonicFL::LookForward() {//向前看
  Servo(90);
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

UltrasonicFL::UltrasonicFL(uint8_t echoPin, uint8_t trigPin, uint8_t seroPin)
{
  mEchoPin = echoPin;
  mTrigPin = trigPin;
  mSeroPin = seroPin;
  
  pinMode(echoPin, INPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(seroPin, OUTPUT);
}

void UltrasonicFL::Execute(MotorDriver driver)
{
   LookForward();//调整超声波探测模块向前看
   int distance = CheckDistance();//查看距离
  if (distance > KeepAway) {//如果距离大于最小距离
    driver.Forward(MotoPowerMax);//一直向前
  } else {
    
  }
}

UltrasonicFL::~UltrasonicFL()
{
  
}
