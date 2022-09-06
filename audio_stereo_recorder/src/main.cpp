#include <Arduino.h>

#define LEFT_MIC_ONLY 1

const uint32_t SAMPLE_RATE = 8000;
const uint64_t SERIAL_BAUDRATE = 230400;
const uint8_t PIN_MIC_LEFT = A0;
const uint8_t PIN_MIC_RIGHT = A1;

uint8_t left = 128;
uint8_t right = 0;
uint64_t last_transmission_time = 0;
uint32_t period_us = 10^6 / SAMPLE_RATE;

void setup() {
    Serial.begin(SERIAL_BAUDRATE);
    pinMode(PIN_MIC_LEFT, INPUT);
    pinMode(PIN_MIC_RIGHT, INPUT);
    
    // Don't start the loop if the baudrate is too high
    while (SERIAL_BAUDRATE < (SAMPLE_RATE * 2 * 8)){
        Serial.println("Serial baudrate is too low for this sample rate!");
        delay(1000);
    }
}

void _increase(uint8_t &left_mic,  uint8_t &right_mic){
    left_mic++;
    right_mic;
}

void _read_mics(uint8_t &left_mic,  uint8_t &right_mic){
    left_mic = analogRead(PIN_MIC_LEFT);
    right_mic = analogRead(PIN_MIC_RIGHT);
}

void _send_data(uint8_t left_mic, uint8_t right_mic){
    Serial.write(left_mic);
#ifndef LEFT_MIC_ONLY
    Serial.write(right_mic);
#endif
}

void read_n_send()
{
    _read_mics(left, right);
    _send_data(left, right);
    last_transmission_time = micros();
}

void loop() {
    
    if (micros() - last_transmission_time >= period_us)
    {
        read_n_send();
    }
}
