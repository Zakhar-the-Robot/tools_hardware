#include <Arduino.h>
#include <SPI.h>
#include <LibPrintf.h>
#include "zakhar_canbus.h"
#include "CanShield.hpp"
#include "CanBus.hpp"
#include <MemoryFree.h>

#define LOG_FREEMEM(x) (printf("%s (free mem: %d)\n", x, freeMemory()))
bool res = false;
bool testing = true;


void setup()
{

    while (!Serial)
        ;
    Serial.begin(9600);
    printf("Example: CAN Test Node\n");
    canShield.Start();
    canShield.SetGreen0(true);
    devCanBus.Start(10, 1, 1);
    // devCanBus.Stop();
}

void loop()
{
    // printf("Example: CAN Test Nod\n");

}
