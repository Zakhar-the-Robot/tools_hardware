#include <Arduino.h>

enum I2C_ADDR
{
    I2C_ADDR_MOTORS = 0x2A,
    I2C_ADDR_SENS = 0x2B,
    I2C_ADDR_FACE = 0x2C,
};

void I2c_write(uint8_t addr, uint8_t reg, uint8_t val);
uint8_t I2c_read(uint8_t addr, uint8_t reg);
