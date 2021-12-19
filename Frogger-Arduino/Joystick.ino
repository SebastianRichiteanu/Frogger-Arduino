#include "Joystick.h"

// joystick pins
static const byte pinSW = 8;
static const byte pinJoyX = A0;
static const byte pinJoyY = A1;

// joystick thresholds, to check movement
static const int avgValue = 512;
static const int threshold = 256;

// sets the pin mode for the js and reset the last check time
Joystick::Joystick() {
  pinMode(RS, OUTPUT);
  pinMode(pinJoyX, INPUT);
  pinMode(pinJoyY, INPUT);
  pinMode(pinSW, INPUT_PULLUP);
  lastCheckedTime = 0;
}

// read the values of the joystick
void Joystick::read() {
  buttonState = digitalRead(pinSW);
  xValue = analogRead(pinJoyX);
  yValue = analogRead(pinJoyY);
}

// functions to check if the joystick moved in a given direction
bool Joystick::isLeft() const { return xValue <= avgValue - threshold; }
bool Joystick::isRight() const { return xValue >= avgValue + threshold; }
bool Joystick::isDown() const { return yValue <= avgValue - threshold; }
bool Joystick::isUp() const {return yValue >= avgValue + threshold; }
bool Joystick::isPressed() const { return buttonState == LOW; }
// same but with debounce so it won't fail
bool Joystick::isLeftDebounce() { return debounce(isLeft(), lastCheckedTime); }
bool Joystick::isRightDebounce() { return debounce(isRight(), lastCheckedTime); }
bool Joystick::isDownDebounce() { return debounce(isDown(), lastCheckedTime); }
bool Joystick::isUpDebounce() { return debounce(isUp(), lastCheckedTime); }
bool Joystick::isAnyDebounce() { return isLeftDebounce() || isRightDebounce() || isUpDebounce() || isDownDebounce() || isPressedDebounce(); }
bool Joystick::isPressedDebounce() { return debounce(isPressed(), lastCheckedTime); }
