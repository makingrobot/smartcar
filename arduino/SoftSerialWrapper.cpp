#include "SoftSerialWrapper.h"
#include <SoftwareSerial.h>

SoftwareSerial *softSerial;

SoftSerialWrapper::SoftSerialWrapper(uint8_t rxPin, uint8_t txPin, uint32_t baud)
{
  softSerial = new SoftwareSerial(rxPin, txPin);
  softSerial->begin(baud);
}

uint8_t SoftSerialWrapper::Available()
{
  return softSerial->available();
}

byte SoftSerialWrapper::Read()
{
  return softSerial->read();
}

void SoftSerialWrapper::Write(byte data)
{
  softSerial->write(data);
}

void SoftSerialWrapper::Println()
{
  softSerial->println();
}

SoftSerialWrapper::~SoftSerialWrapper()
{
  delete softSerial;
}
