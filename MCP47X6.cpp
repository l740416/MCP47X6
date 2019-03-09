/*
    Copyright 2018 Chiehting Huang <j.huang.1985@gmail.com>
*/
#include "Arduino.h"
#include "MCP47X6.h"

// I2C Address
#define MCP47X6_ADDRESS               0x61

MCP47X6::MCP47X6(uint8_t chip) :
  MCP47X6(chip, MCP47X6_ADDRESS)
{
}

MCP47X6::MCP47X6(uint8_t chip, uint8_t address) :
  m_address(address)
{
  if (chip == MCP47X6_IS_MCP4706)
  {
    m_dataShiftBits = 8;
  }
  else if (chip == MCP47X6_IS_MCP4716)
  {
    m_dataShiftBits = 6;
  }
  else if (chip == MCP47X6_IS_MCP4726)
  {
    m_dataShiftBits = 4;
  }
  else
  {
    // should not enter here
  }
  
  m_config = MCP47X6_VREF_VDD | MCP47X6_AWAKE | MCP47X6_GAIN_1X;
  m_level  = 0;
}

void MCP47X6::begin(int SDA_pin, int SCL_pin)
{
    Wire.begin(SDA_pin,SCL_pin);
}

void MCP47X6::begin()
{
    Wire.begin();
}

bool MCP47X6::exist() 
{
  Wire.beginTransmission(m_address);
  if (Wire.endTransmission() == 0)
  {
      return true;
  }
  return false;
}

void MCP47X6::setGain(uint8_t gain)
{
  m_config = m_config & ~MCP47X6_GAIN_MASK;
  m_config = m_config | (gain & MCP47X6_GAIN_MASK);
}

void MCP47X6::setVref(uint8_t ref)
{
  m_config = m_config & ~MCP47X6_VREF_MASK;
  m_config = m_config | (ref & MCP47X6_VREF_MASK);
}

void MCP47X6::setPowerDown(uint8_t pd)
{
  m_config = m_config & ~MCP47X6_PWRDN_MASK;
  m_config = m_config | (pd & MCP47X6_PWRDN_MASK);
}

bool MCP47X6::saveSettings(void)
{
  uint8_t config = MCP47X6_CMD_VOLCONFIG | ( m_config & ~MCP47X6_CMD_MASK);
  write8(config);
}

bool MCP47X6::setLevel(uint16_t level)
{
  uint8_t config = MCP47X6_CMD_VOLALL | ( m_config & ~MCP47X6_CMD_MASK);
  level = level << m_dataShiftBits;
  write24(config, (level >> 8) & 0xFF, level & 0xFF);
}

void MCP47X6::write8(uint8_t data)
{
    Wire.beginTransmission(m_address);
#if (ARDUINO >= 100)
    Wire.write(data);
#else
    Wire.send(data);
#endif
    Wire.endTransmission();
}

void MCP47X6::write16(uint8_t data1, uint8_t data2)
{
    Wire.beginTransmission(m_address);
#if (ARDUINO >= 100)
    Wire.write(data1);
    Wire.write(data2);
#else
    Wire.send(data1);
    Wire.send(data2);
#endif
    Wire.endTransmission();
}

void MCP47X6::write24(uint8_t data1, uint8_t data2, uint8_t data3)
{
    Wire.beginTransmission(m_address);
#if (ARDUINO >= 100)
    Wire.write(data1);
    Wire.write(data2);
    Wire.write(data3);
#else
    Wire.send(data1);
    Wire.send(data2);
    Wire.send(data3);
#endif
    Wire.endTransmission();
}
