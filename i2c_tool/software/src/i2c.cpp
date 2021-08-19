#include "i2c.hpp"
#include <Wire.h>

void I2c_write(uint8_t addr, uint8_t reg, uint8_t val)
{
    Wire.beginTransmission(addr);
    Wire.write(reg);
    Wire.write(val);
    Wire.endTransmission(true); // stop transmitting
    // delay(20);
    
}

uint8_t I2c_read(uint8_t addr, uint8_t reg){
    Wire.beginTransmission(addr);
    Wire.write(reg);
    Wire.requestFrom(addr, 1);
    uint8_t res = static_cast<uint8_t>(Wire.read());
    Wire.endTransmission(true); // stop transmitting

    // auto res = Wire.requestFrom(addr, 1, reg, 1, 1);
    return res;
}
