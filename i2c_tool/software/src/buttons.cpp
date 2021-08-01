#include <Arduino.h>
#include <Wire.h>
#include "TimerOne.h"
#include "MultiFuncShield.h"
#include "buttons.hpp"
#include "i2c.hpp"
#include "hex.h"

static uint8_t _addr = I2C_ADDR_MOTORS;

void button1_func()
{
    MFS.write("scan");
    MFS.writeLeds(0b1111, 0);
    delay(500);
    Wire.beginTransmission(I2C_ADDR_MOTORS);
    MFS.writeLeds(0b0001, !Wire.endTransmission());
    Wire.beginTransmission(I2C_ADDR_FACE);
    MFS.writeLeds(0b0010, !Wire.endTransmission());
    Wire.beginTransmission(I2C_ADDR_SENS);
    MFS.writeLeds(0b0100, !Wire.endTransmission());
    MFS.write("done");
}

void button2_func()
{
    switch (_addr)
    {
    case I2C_ADDR_MOTORS:
        _addr = I2C_ADDR_SENS;
        MFS.writeLeds(0b1111, 0);
        MFS.writeLeds(0b0010, 1);
        MFS.write("sens");
        break;
    case I2C_ADDR_SENS:
        _addr = I2C_ADDR_FACE;
        MFS.writeLeds(0b1111, 0);
        MFS.writeLeds(0b0100, 1);
        MFS.write("face");
        break;
    default:
        _addr = I2C_ADDR_MOTORS;
        MFS.writeLeds(0b1111, 0);
        MFS.writeLeds(0b0001, 1);
        MFS.write("mtrs");
        break;
    }
    // MFS.write (hex(_addr).c_str());
}

void button3_func()
{
    uint8_t val = random(0x01, 0xFE);
    I2c_write(_addr, 1, val);
    auto i = I2c_read(_addr, 1);
    MFS.write("-");
    delay (100);
    MFS.write("--");
    delay (100);
    MFS.write("---");
    delay (100);
    MFS.write("----");
    delay(100);
    MFS.write(hex((val << 8) | i).c_str());
}
