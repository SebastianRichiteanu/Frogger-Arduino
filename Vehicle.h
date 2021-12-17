#pragma once

class Vehicle {
  bool direction, isMoving, visibility;
  byte y, length, maxLength;
  Timer delayTime, lastUpdateTime;

  void increaseLength(byte x);

  void setVehicleCells(byte x);
  void moveVehicle();

  void moveVehicleLeft();
  void moveVehicleRight();

  void setVehicleCellsLeft(byte x);
  void setVehicleCellsRight(byte x);  

  public:
    Vehicle();
    void update(byte x);
    bool getMoving() const;
    byte getY() const;
};
