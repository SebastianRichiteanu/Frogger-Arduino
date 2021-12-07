#pragma once

#include "Timer.h"

class Joystick {
  Timer lastCheckedTime;
  int xValue = 0, yValue = 0;
  bool buttonState = HIGH;

  public:
  Joystick();

  void read();
  bool isLeft() const;
  bool isRight() const;
  bool isDown() const;
  bool isUp() const;

  bool isPressed() const;

  bool isLeftDebounce();
  bool isRightDebounce();
  bool isDownDebounce();
  bool isUpDebounce();

  bool isAnyDebounce();

  bool isPressedDebounce();

  int getX() const;
  int getY() const;
  
};
