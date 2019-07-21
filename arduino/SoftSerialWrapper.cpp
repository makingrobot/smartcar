#include <Arduino.h>
#include "SoftSerialWrapper.h"

SoftSerialWrapper::SoftSerialWrapper(uint8_t rxPin, uint8_t txPin, int baud)
{
  mSoftSerial = new SoftwareSerial(rxPin, txPin);
  mSoftSerial->begin(baud);
}

uint8_t SoftSerialWrapper::Available()
{
  return mSoftSerial->available();
}

byte SoftSerialWrapper::Read()
{
  return mSoftSerial->read();
}

void SoftSerialWrapper::Write(byte data)
{
  mSoftSerial->write(data);
}

void SoftSerialWrapper::Println()
{
  mSoftSerial->println();
}

SoftSerialWrapper::~SoftSerialWrapper()
{
  delete mSoftSerial;
}
