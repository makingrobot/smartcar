#ifndef __SOFTSERIAL_WRAPPER_H_
#define __SOFTSERIAL_WRAPPER_H_
#pragma once

#include <Arduino.h>
#include <SoftwareSerial.h>

#include "SerialWrapper.h"

class SoftSerialWrapper : public SerialWrapper
{
  public:
    SoftSerialWrapper(uint8_t rxPin, uint8_t txPin, int baud);
    ~SoftSerialWrapper();

    uint8_t Available() override;
    byte Read() override;
    void Write(byte data) override;
    void Println() override;

  private:
    SoftwareSerial *mSoftSerial;
  
};

#endif
