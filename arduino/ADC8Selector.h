/* SmartCar - makingrobot.net
 * Copyright MakingRobot 2018
 * MIT License
 */
#ifndef _ADC8_SELECTOR_H_
#define _ADC8_SELECTOR_H_
#pragma once

#include "Arduino.h"
#include "ModeSelector.h"

class ADC8Selector : public ModeSelector
{
  public:
    ADC8Selector(uint8_t inPin);
    ~ADC8Selector();

    uint8_t GetMode() override;

  private:
    uint8_t mMode = 1;
    uint8_t mInPin;
  
};

#endif
