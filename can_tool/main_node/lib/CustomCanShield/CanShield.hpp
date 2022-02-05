// *************************************************************************
//
// Copyright (c) 2021 Andrei Gramakov. All rights reserved.
//
// site:    https://agramakov.me
// e-mail:  mail@agramakov.me
//
// *************************************************************************

#pragma once

// includes
#include <Arduino.h>

class CanShield
{

private:
    const int LED_GREEN0 = A0;
    const int LED_GREEN1 = A1;
    const int LED_GREEN2 = A2;
    const int LED_RED = A3;

    const int BTN0 = 4;

public:
    CanShield()=default;
    void Start();
    void SetGreen0(bool val);
    void SetGreen1(bool val);
    void SetGreen2(bool val);
    void SetRed(bool val);
    bool GetButton0();
};

extern CanShield canShield;
