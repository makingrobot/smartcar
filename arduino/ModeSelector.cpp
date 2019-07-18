#include "ModeSelector.h"

const int AD_VALUES[8] = {62, 190, 317, 446, 574, 702, 831, 960};
const int TOLERANCE = 15;
const int TIMES = 5;

ModeSelector::ModeSelector(uint8_t inPin)
{
    mInPin = inPin;
}
  
uint8_t ModeSelector::GetMode()
{
  uint8_t val;
  int i=0;
  while (i++ < TIMES) 
  {
    uint8_t tmp = analogRead(mInPin);
    if (tmp > val)
      val = tmp;
    delay(5);
  }

  for (i=0; i<8; i++)
  {
     if (AD_VALUES[i] > val-TOLERANCE && AD_VALUES[i] < val+TOLERANCE)
     {
       mMode = i + 1;
       break;
     } 
  }
  
  return mMode;
}

ModeSelector::~ModeSelector()
{
  
}
