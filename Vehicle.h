#pragma once

class Vehicle {
  public:
    Vehicle();
    void update(byte x);
    bool getMoving() const;
    byte getY() const;
  
  private:
    bool direction, isMoving, visibility;
    byte y, length, maxLength;
    Timer delayTime, lastUpdateTime;
  
    void increaseLength(byte x);
  
    void moveVehicle();
    void moveVehicleLeft();
    void moveVehicleRight();
  
    void setVehicleCells(byte x);
    void setVehicleCellsLeft(byte x);
    void setVehicleCellsRight(byte x);
};
