/* SmartCar - makingrobot.net
 * Copyright MakingRobot 2018
 * MIT License
 */
#ifndef _MODE_SELECTOR_H_
#define _MODE_SELECTOR_H_
#pragma once

#include "Arduino.h"

class ModeSelector
{
  public:
    virtual uint8_t GetMode() ;

};

#endif
