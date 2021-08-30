#include <Arduino.h>
#include <SPI.h>
#include <mcp2515.h>
#include <LibPrintf.h>
#include "zakhar_canbus.h"

struct can_frame read_frame;
struct can_frame write_frame;
bool res = false;
bool testing = true;
MCP2515 mcp2515(10);
uint32_t addr = 0x2a0;

enum CAN_CMD
{
    CAN_CMD_READ = 0b01000000,  // 0b01000000 | REGISTER_NUM(6bits)
    CAN_CMD_WRITE = 0b10000000, // 0b10000000 | REGISTER_NUM(6bits)
    CAN_CMD_PING = 0b11111111,
};

enum CAN_DATA
{
    CAN_DATA_ADDR = 0x0,
    CAN_DATA_CMD,
    CAN_DATA_DATA0,
    CAN_DATA_DATA1,
    CAN_DATA_DATA2,
    CAN_DATA_DATA3,
    CAN_DATA_DATA4,
    CAN_DATA_DATA5,
};

void Success()
{
    // printf("Test passed!\n\r");
    Serial.println("Test passed!");
    res = true;
    // detachInterrupt(digitalPinToInterrupt(2));
    // while (1)
    // ;
}

void print_msg(struct can_frame &canMsg)
{
    Serial.print(canMsg.can_id, HEX); // print ID
    Serial.print(" ");
    Serial.print(canMsg.can_dlc, HEX); // print DLC
    Serial.print(" ");
    for (int i = 0; i < canMsg.can_dlc; i++)
    { // print the data
        Serial.print(canMsg.data[i], HEX);
        Serial.print(" ");
    }
    Serial.println();
}

bool CanSend(uint32_t id, bool rtr, uint8_t bytes = 0,
             uint8_t d0 = 0x00,
             uint8_t d1 = 0x00,
             uint8_t d2 = 0x00,
             uint8_t d3 = 0x00,
             uint8_t d4 = 0x00,
             uint8_t d5 = 0x00,
             uint8_t d6 = 0x00,
             uint8_t d7 = 0x00)
{
    struct can_frame msg;
    msg.can_id = id;
    if (rtr)
    {
        msg.can_id |= CAN_RTR_FLAG;
    }
    else
    {
        msg.can_dlc = bytes;
        msg.data[0] = d0;
        msg.data[1] = d1;
        msg.data[2] = d2;
        msg.data[3] = d3;
        msg.data[4] = d4;
        msg.data[5] = d5;
        msg.data[6] = d6;
        msg.data[7] = d7;
    }
    bool res = mcp2515.sendMessage(&msg);
    if (res == MCP2515::ERROR_OK)
    {
        printf("Sent: ");
        print_msg(msg);
    }
    else
    {
        printf("Error: 0x%x\n\r", res);
    }
    return res;
}

void irqHandler()
{
    uint8_t irq = mcp2515.getInterrupts();

    if (irq & MCP2515::CANINTF_RX0IF)
    {
        if ((mcp2515.readMessage(MCP2515::RXB0, &read_frame) == MCP2515::ERROR_OK))
        {
            if ((read_frame.can_id >> 30U) & 1)
            {
                // printf("Requested: ");
            }
            else
            {
                // printf("Got: ");
            }
            // print_msg(read_frame);
            if (read_frame.can_id == 0x2a0)
            {
                Success();
            }
        }
    }

    if (irq & MCP2515::CANINTF_RX1IF)
    {
        if (mcp2515.readMessage(MCP2515::RXB1, &read_frame) == MCP2515::ERROR_OK)
        {
            if ((read_frame.can_id >> 30U) & 1)
            {
                // printf("Requested: ");
            }
            else
            {
                // printf("Got: ");
            }
            // print_msg(read_frame);
            if (read_frame.can_id == 0x2a0)
            {
                Success();
            }
        }
    }
}

void setup()
{

    while (!Serial)
        ;
    Serial.begin(115200);

    mcp2515.reset();
    mcp2515.setBitrate(CAN_125KBPS);
    mcp2515.setNormalMode();
    attachInterrupt(digitalPinToInterrupt(2), irqHandler, FALLING);
    pinMode(13, OUTPUT);
    Serial.println("Example: CAN Test Node");
}

void loop()
{
    if (testing)
    {

        if (res)
        {
            detachInterrupt(digitalPinToInterrupt(2));
            Serial.print("Result msg: ");
            print_msg(read_frame);
            testing = false;
            Serial.println("[  SUCCESS  ]");
        }
        else
        {
            CanSend(0, false);
            // delay(300);
            CanSend(addr, true);
            switch(addr){
                case 0x2a0:
                    addr = 0x2b0;
                    break;
                case 0x2b0:
                    addr = 0x2c0;
                    break;
                default:
                    addr = 0x2a0;
                    break;
            }

            // digitalWrite(13, HIGH);
            // delay(200);
            // digitalWrite(13, LOW);
            // delay(200);
        }
    }

    // CanSend(0x2a2, false, 3, 0xa1, 0xa2, 0xa3);
    // delay(500);
    // CanSend(0x2a0, true);
    // delay(500);
}
