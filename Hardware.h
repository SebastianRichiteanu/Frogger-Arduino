#pragma once

#include <LedControl.h>
#include <LiquidCrystal.h>
#include "Joystick.h"
#include "Buzzer.h"

extern LiquidCrystal lcd;
extern LedControl lc;
extern Joystick js;
extern Buzzer buzzer;

void initHardware();
void updateHardware();
