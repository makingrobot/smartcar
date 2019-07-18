#include "InfraredControl.h"

#include <IRremote.h>

IRrecv *mIRrecv;
decode_results results;

InfraredControl::InfraredControl(uint8_t inPin)
{
   mIRrecv = new IRrecv(inPin);
   mIRrecv->enableIRIn(); 
}

void InfraredControl::ReadInput()
{
  if (mIRrecv->decode(&results)) {
    Serial.println(results.value, HEX);
    mIRrecv->resume();
    if (results.value == 0xFF18E7) {
      forwardPressState = 1;
    } else if (results.value == 0xFF4AB5) {
      backwardPressState = 1;
    } else if (results.value == 0xFF10EF) {
      leftPressState = 1;
    } else if (results.value == 0xFF5AA5) {
      rightPressState = 1;
    } else if (results.value == 0xFF38C7) {
      stopPressState = 1;
    }
  }
}

InfraredControl::~InfraredControl()
{
  delete mIRrecv;
}
