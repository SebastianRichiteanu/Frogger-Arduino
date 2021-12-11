#pragma once

class Vehicle {
  bool direction, isMoving, visibility, blinking;
  byte y, speed, length;
  Timer delayTime, lastUpdateTime, lastBlinkUpdateTime;

  static const int blinkDelay = 300;
  static const int startBlinkDelay = 2000;

  void blink(byte x, byte y);

  void setVehicleCells(byte x);
  void moveVehicle(byte x);

  void moveVehicleLeft(byte x);
  void moveVehicleRight(byte x);

  void setVehicleCellsLeft(byte x);
  void setVehicleCellsRight(byte x);  

  public:
    Vehicle();
    void update(byte x);
    bool getMoving();

};
