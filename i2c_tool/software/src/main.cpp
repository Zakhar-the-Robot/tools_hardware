#include <Arduino.h>
#include <Wire.h>
#include "TimerOne.h"
#include "MultiFuncShield.h"
#include "buttons.hpp"

void setup()
{
    // put your setup code here, to run once:

    Wire.begin();
    Timer1.initialize();
    MFS.initialize(&Timer1); // initialize multi-function shield library

    MFS.write("Hi");
    MFS.writeLeds(0b1111,1);
    delay(1000);
    MFS.writeLeds(0b1110,0);

}


void loop()
{
  if (Button1()) {
    button1_func();
    while(Button1());
  } else if (Button2()){
    button2_func();
    while(Button2());
  } else if (Button3()){
    button3_func();
    while(Button3());
  }
}
