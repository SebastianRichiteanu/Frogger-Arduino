#include "Joystick.h"

static const byte pinSW = 8;
static const byte pinJoyX = A0;
static const byte pinJoyY = A1;

static const int avgValue = 512;
static const int threshold = 256;

extern unsigned long updateTime; // global

Joystick::Joystick() {
  pinMode(RS, OUTPUT);
  pinMode(pinJoyX, INPUT);
  pinMode(pinJoyY, INPUT);
  pinMode(pinSW, INPUT_PULLUP);
  lastCheckedTime = 0;
}

void Joystick::read() {
  buttonState = digitalRead(pinSW);
  xValue = analogRead(pinJoyX);
  yValue = analogRead(pinJoyY);
}

bool Joystick::isLeft() const { return xValue <= avgValue - threshold; }
bool Joystick::isRight() const { return xValue >= avgValue + threshold; }
bool Joystick::isDown() const { return yValue <= avgValue - threshold; }
bool Joystick::isUp() const {return yValue >= avgValue + threshold; }
bool Joystick::isPressed() const { return buttonState == LOW; }
bool Joystick::isLeftDebounce() { return debounce(isLeft(), lastCheckedTime); }
bool Joystick::isRightDebounce() { return debounce(isRight(), lastCheckedTime); }
bool Joystick::isDownDebounce() { return debounce(isDown(), lastCheckedTime); }
bool Joystick::isUpDebounce() { return debounce(isUp(), lastCheckedTime); }
bool Joystick::isAnyDebounce() { return isLeftDebounce() || isRightDebounce() || isUpDebounce() || isDownDebounce(); }
bool Joystick::isPressedDebounce() { return debounce(isPressed(), lastCheckedTime); }
int Joystick::getX() const { return xValue; }
int Joystick::getY() const { return yValue; }
