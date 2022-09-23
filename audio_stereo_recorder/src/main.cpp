#include <Arduino.h>

#define MAX_ADC_VAL 255U

const uint32_t SAMPLE_RATE_HZ = 10;
const uint64_t SERIAL_BAUDRATE = 400000;
const uint32_t SYNC_FRAMES = 32;

const uint8_t PIN_MIC_LEFT = A0;
const uint8_t PIN_MIC_RIGHT = A1;

uint8_t frame_count = 0;
uint8_t left = 128;
uint8_t right = 0;
uint64_t last_transmission_time = 0;
const uint32_t PERIOD_US = 1000000 / SAMPLE_RATE_HZ;

void setup()
{
    Serial.begin(SERIAL_BAUDRATE);
    pinMode(PIN_MIC_LEFT, INPUT);
    pinMode(PIN_MIC_RIGHT, INPUT);
    pinMode(LED_BUILTIN, OUTPUT);

    // Don't start the loop if the baudrate is too high
    while (SERIAL_BAUDRATE < (SAMPLE_RATE_HZ * 2 * 8))
    {
        Serial.println("Serial baudrate is too low for this sample rate!");
        delay(1000);
    }
}

void read_data(uint8_t &left_mic, uint8_t &right_mic)
{
    left_mic = MAX_ADC_VAL - analogRead(PIN_MIC_LEFT);
    right_mic = MAX_ADC_VAL - analogRead(PIN_MIC_RIGHT);
}

void send_frame(uint8_t left_mic, uint8_t right_mic)
{
    Serial.write(left_mic);
    Serial.write(right_mic);
    last_transmission_time = micros();
}

void handle_sync(){
    
    if (frame_count >= SYNC_FRAMES){
        frame_count = 0;
        Serial.write(0x55);
        Serial.write(0x55);
        Serial.write(0x55);
        Serial.write(0x55);
    }
    frame_count++;
}

void loop()
{
    if (micros() - last_transmission_time >= PERIOD_US)
    {
        handle_sync();
        read_data(left, right);
        send_frame(left, right);
    }
}
