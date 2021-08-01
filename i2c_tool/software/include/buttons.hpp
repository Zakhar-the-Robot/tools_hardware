#include "MultiFuncShield.h"

inline bool Button1() { return !digitalRead(BUTTON_1_PIN); };
inline bool Button2() { return !digitalRead(BUTTON_2_PIN); };
inline bool Button3() { return !digitalRead(BUTTON_3_PIN); };


void button1_func();
void button2_func();
void button3_func();
