#include <Arduino.h>
#include <SPI.h>
#include <mcp2515.h>
#include <LibPrintf.h>

struct can_frame canMsg1;
struct can_frame canMsg2;
MCP2515 mcp2515(10);

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

bool CanSendRawMsg(uint8_t id, uint8_t bytes,
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
    msg.can_dlc = bytes;
    msg.data[0] = d0;
    msg.data[1] = d1;
    msg.data[2] = d2;
    msg.data[3] = d3;
    msg.data[4] = d4;
    msg.data[5] = d5;
    msg.data[6] = d6;
    msg.data[7] = d7;
    if (mcp2515.sendMessage(&msg) == MCP2515::ERROR_OK)
    {
        return true;
    }
    else
    {
        return false;
    };
}

bool CanWrite(uint8_t priority, uint8_t addr, uint8_t reg,
              uint8_t d0 = 0x00,
              uint8_t d1 = 0x00,
              uint8_t d2 = 0x00,
              uint8_t d3 = 0x00,
              uint8_t d4 = 0x00,
              uint8_t d5 = 0x00)
{
    uint8_t d[6] = {d0, d1, d2, d3, d4, d5};

    uint8_t dlc = 0;
    for (int i = 0; i < 6; ++i)
    {
        if (d[i])
        {
            dlc = i + 1;
        }
    }
    dlc += 2; // addr and cmd

    return CanSendRawMsg(priority, dlc, addr, (CAN_CMD_WRITE | reg), d0, d1, d2, d3, d4, d5);
}

bool CanRead(uint8_t priority, uint8_t addr, uint8_t reg, struct can_frame & result)
{
    CanSendRawMsg(priority, 2, addr, (CAN_CMD_READ | reg));
    while (mcp2515.readMessage(&result) != MCP2515::ERROR_OK);
    print_msg(result);
    return true;
}

void setup()
{

    while (!Serial)
        ;
    Serial.begin(115200);

    mcp2515.reset();
    mcp2515.setBitrate(CAN_125KBPS);
    mcp2515.setNormalMode();

    Serial.println("Example: Write to CAN");
}

void loop()
{
    uint8_t prior = 1;
    uint8_t addr = 0x2a;
    uint8_t reg = 0xa;
    uint8_t d0 = 0;
    uint8_t d1 = 1;
    uint8_t d2 = 2;
    uint8_t d3 = 3;
    uint8_t d4 = 4;
    uint8_t d5 = 5;
    struct can_frame result;

    printf("Write: %x %x %x %x %x %x %x %x %x\n\r", 
                    prior,  addr, reg, d0, d1,  d2,  d3,  d4, d5);
    CanWrite(prior, addr, reg, d0, d1, d2, d3, d4, d5);
    delay(300);

    printf("Read: %x %x %x\n\r", 
                prior, addr, reg);
    CanRead(prior, addr, reg, result);
    delay(300);
}
