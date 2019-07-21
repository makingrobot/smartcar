#ifndef __SERIAL_WRAPPER_H_
#define __SERIAL_WRAPPER_H_
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
