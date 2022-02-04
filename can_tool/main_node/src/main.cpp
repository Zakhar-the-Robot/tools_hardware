#include <Arduino.h>
#include <SPI.h>
#include "zakhar_canbus.h"
#include "CanShield.hpp"
#include "CanBus.hpp"

void setup()
{
    Serial.begin(9600);
    canShield.Start();
    canShield.SetGreen0(true);
    devCanBus.Start(10, 1, 1);
}

void loop()
{
}
