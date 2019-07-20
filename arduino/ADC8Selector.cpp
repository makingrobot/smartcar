#include "ADC8Selector.h"

const int AD_VALUES[8] = {62, 190, 317, 446, 574, 702, 831, 960};
const int TOLERANCE = 15;
const int TIMES = 5;

ADC8Selector:: ADC8Selector(uint8_t inPin)
{
    mInPin = inPin;
}
  
uint8_t ADC8Selector::GetMode()
{
  uint16_t maxSample=0;
  int i=0;
  uint16_t sample = 0;
  while (i++ < TIMES) 
  {
    sample = analogRead(mInPin);
    if (sample >10)
      break;
  }

  if (sample > 10) // 按钮按下了，
  {
    while(true)
    {
      if (sample > maxSample)
        maxSample = sample;  // 保存最大的取样值
      delay(5);
      sample = analogRead(mInPin);
      if (sample < 10) // 按钮松开了
        break;
    }
  }

  if (maxSample > 0)
  {
    Serial.print("input ");
    Serial.println(maxSample);
      
    for (i=0; i<8; i++)
    {
       if (AD_VALUES[i] > maxSample-TOLERANCE && AD_VALUES[i] < maxSample+TOLERANCE)
       {
         mMode = i + 1;
         break;
       } 
    }
  }
  
  return mMode;
}

ADC8Selector::~ADC8Selector()
{
  
}
