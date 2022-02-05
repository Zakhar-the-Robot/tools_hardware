// *************************************************************************
//
// Copyright (c) 2021 Andrei Gramakov. All rights reserved.
//
// site:    https://agramakov.me
// e-mail:  mail@agramakov.me
//
// *************************************************************************

#include "CanShield.hpp"


void CanShield::Start(){
    pinMode(LED_GREEN0, OUTPUT);
    pinMode(LED_GREEN1, OUTPUT);
    pinMode(LED_GREEN2, OUTPUT);
    pinMode(LED_RED, OUTPUT);
    pinMode(BTN0, INPUT);
}

void CanShield::SetGreen0(bool val)
{
    digitalWrite(LED_GREEN0, (val ? HIGH : LOW));
}

void CanShield::SetGreen1(bool val)
{
    digitalWrite(LED_GREEN1, (val ? HIGH : LOW));
}

void CanShield::SetGreen2(bool val)
{
    digitalWrite(LED_GREEN2, (val ? HIGH : LOW));
}

void CanShield::SetRed(bool val)
{
    digitalWrite(LED_RED, (val ? HIGH : LOW));
}

bool CanShield::GetButton0()
{
    return !digitalRead(BTN0);
}

CanShield canShield;
