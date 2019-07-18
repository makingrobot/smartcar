#include "InfraredTrack.h"

#define LineTurnDelay 100

uint8_t nLeftPin;
uint8_t nRightPin;

InfraredTrack::InfraredTrack(uint8_t leftPin, uint8_t rightPin)
{
  nLeftPin = leftPin;
  nRightPin = rightPin;
}

int checkState() {
  int left = analogRead(nLeftPin);
  int right = analogRead(nRightPin);
  left = left > 512 ? 1 : 0;
  right = right > 512 ? 1 : 0;
  return left * 2 + right;
}

void InfraredTrack::Execute(MotorDriver driver)
{
  int state = checkState();
  Serial.println(state);
  if (state==0 || state==3) {
    driver.Forward(MotoPowerMax);// 11, 00 向前
    delay(300);
  } else {
    if (state==1) { // 01 偏右
      driver.TurnLeft(MotoPowerMin);
    } else if (state==2) { // 10 偏左
      driver.TurnRight(MotoPowerMin);
    }
    
    delay(LineTurnDelay);
  }
  driver.Stop();
  delay(300);
}
  
InfraredTrack::~InfraredTrack()
{
  
}
