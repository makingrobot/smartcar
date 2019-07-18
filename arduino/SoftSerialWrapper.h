#ifndef __SOFTSERIAL_WRAPPER_H_
#define __SOFTSERIAL_WRAPPER_H_
#pragma once

#include "Arduino.h"
#include "SerialWrapper.h"

class SoftSerialWrapper : public SerialWrapper
{
  public:
    SoftSerialWrapper(uint8_t rxPin, uint8_t txPin, uint32_t baud);
    ~SoftSerialWrapper();

    virtual uint8_t Available();
    virtual byte Read();
    virtual void Write(byte data);
    virtual void Println();
};

#endif
