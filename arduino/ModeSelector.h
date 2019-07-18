#ifndef __MODE_SELECTOR_H_
#define __MODE_SELECTOR_H_
#pragma once

#include "Arduino.h"

class ModeSelector
{
  public:
    ModeSelector::ModeSelector(uint8_t inPin);
    ModeSelector::~ModeSelector();

    uint8_t GetMode();
};

#endif
