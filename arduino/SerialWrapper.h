/* SmartCar - makingrobot.net
 * Copyright MakingRobot 2018
 * MIT License
 */
#ifndef _SERIAL_WRAPPER_H_
#define _SERIAL_WRAPPER_H_
#pragma once

#include <Arduino.h>

class SerialWrapper
{
  public:
    SerialWrapper();
    ~SerialWrapper();

    virtual uint8_t Available();
    virtual byte Read();
    virtual void Write(byte data);
    virtual void Println();
};

#endif
