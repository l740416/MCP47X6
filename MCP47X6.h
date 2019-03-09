/*
  Copyright 2018 Chiehting Huang <j.huang.1985@gmail.com>

*/
#ifndef MCP47X6_h
#define MCP47X6_h

#define MCP47X6_IS_MCP4706            1
#define MCP47X6_IS_MCP4716            2
#define MCP47X6_IS_MCP4726            3

// Programmable Gain
#define MCP47X6_GAIN_MASK	            0x01
#define MCP47X6_GAIN_1X	              0x00
#define MCP47X6_GAIN_2X	              0x01

// Power Down Mode
#define MCP47X6_PWRDN_MASK            0x06
#define MCP47X6_AWAKE                 0x00
#define MCP47X6_PWRDN_1K              0x02
#define MCP47X6_PWRDN_100K            0x04
#define MCP47X6_PWRDN_500K            0x06

// Reference Voltage
#define MCP47X6_VREF_MASK             0x18
#define MCP47X6_VREF_VDD              0x00
#define MCP47X6_VREF_VREFPIN	        0x10
#define MCP47X6_VREF_VREFPIN_BUFFERED 0x18

// Command
#define MCP47X6_CMD_MASK              0xE0
#define MCP47X6_CMD_VOLDAC            0x00
#define MCP47X6_CMD_VOLALL            0x40
#define MCP47X6_CMD_ALL               0x60
#define MCP47X6_CMD_VOLCONFIG         0x80

#if (ARDUINO >= 100)
 #include "Arduino.h"
#else
 #include "WProgram.h"
#endif

#ifdef __AVR_ATtiny85__
 #include "TinyWireM.h"
 #define Wire TinyWireM
#elif defined(ARDUINO_ARCH_ESP8266)
 #include <Wire.h>
#else
 #include <avr/pgmspace.h>
 #include <Wire.h>
#endif

class MCP47X6
{
  public:
    MCP47X6(uint8_t chip);
    MCP47X6(uint8_t chip, uint8_t address);
    void begin(int SDA_pin, int SCL_pin);
    void begin();
    bool exist();

    void setGain(uint8_t gain);
    void setVref(uint8_t ref);
    void setPowerDown(uint8_t pd);
    
    bool saveSettings(void);

    bool setLevel(uint16_t level);
    
  private:
    const uint8_t address = 0x61;
    void  write8(uint8_t data);
    void  write16(uint8_t data1, uint8_t data2);
    void  write24(uint8_t data1, uint8_t data2, uint8_t data3);

    uint8_t m_address;
    uint8_t m_config;
    uint8_t m_level;
    uint8_t m_dataShiftBits;
};

#endif

