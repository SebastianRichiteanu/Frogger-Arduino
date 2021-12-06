#pragma once

#include <LedControl.h>
#include <LiquidCrystal.h>
#include "Joystick.h"

extern LiquidCrystal lcd;
extern LedControl lc;
extern Joystick js;
// extern buzzer

void initHardware();
void updateHardware();
