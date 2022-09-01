#include <Arduino.h>

uint8_t left = 128;
uint8_t right = 0;


void setup() {
    Serial.begin(230400);
    pinMode(A0, INPUT);
    pinMode(A1, INPUT);
}

void increase(uint8_t &left_mic,  uint8_t &right_mic){
    left_mic++;
    right_mic;
}

void read_mics(uint8_t &left_mic,  uint8_t &right_mic){
    left_mic = analogRead(A0);
    right_mic = analogRead(A1);
}

void send_data(uint8_t left_mic, uint8_t right_mic){
    Serial.write(left_mic);
    Serial.write(right_mic);
}

void loop() {
    // read_mics(left, right);
    increase(left, right);
    send_data(left, right);
}
