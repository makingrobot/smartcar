#include "SerialWrapper.h"

SerialWrapper::SerialWrapper()
{
  
}

uint8_t SerialWrapper::Available()
{
  return Serial.available();
}

byte SerialWrapper::Read()
{
  return Serial.read();
}

void SerialWrapper::Write(byte data)
{
  Serial.write(data);
}

void SerialWrapper::Println()
{
  Serial.println();
}

SerialWrapper::~SerialWrapper()
{
  
}
