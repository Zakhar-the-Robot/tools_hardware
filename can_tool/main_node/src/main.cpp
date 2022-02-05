#include <Arduino.h>
#include <SPI.h>
#include "CanShield.hpp"
#include "CanBus.hpp"
#include <LibPrintf.h>

void RxCallback(const CanBus *dev, const can_frame &msg)
{
    printf("0x%08lx : %02x : %02x : %02x : %02x : %02x : %02x : %02x : %02x\n",
           msg.can_id,
           msg.data[7],
           msg.data[6],
           msg.data[5],
           msg.data[4],
           msg.data[3],
           msg.data[2],
           msg.data[1],
           msg.data[0]);
}

void setup()
{
    Serial.begin(115200);
    canShield.Start();
    canShield.SetGreen0(true);
    devCanBus.Start(10, 1, 1);
    devCanBus.SetRxCallback(RxCallback);
}

void loop()
{
}
