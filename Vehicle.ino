#include "Vehicle.h"

Vehicle::Vehicle() {
  isMoving = false;
  delayTime = random(5000, 10000) * vehicleDelayByDif() * vehicleDelayByLevel();
  lastUpdateTime = updateTime;
  if (direction) { // from right
    y = levelMap.width - 1;
  } else { // from left
    y = levelMap.width - 1;
  }
  direction = random(0, 2);
  maxLength = random(2, 5) * vehicleLenByDif() * vehicleLenByLevel();
  length = 0;
  visibility = false;
}



bool Vehicle::getMoving() const { return isMoving; }

byte Vehicle::getY() const { return y; }

void Vehicle::increaseLength(byte x) {
  if (length < maxLength) {
    ++length;
  }
}

void Vehicle::moveVehicleLeft() { 
  if (y < levelMap.width) {
    isMoving = true;
    ++y;
  } else {
    if (debounce(lastUpdateTime, delayTime)) {
      isMoving = true;
      y = 0;
    } else {
      length = 0;
      isMoving = false;
    }
  }
}

void Vehicle::moveVehicleRight() {
  if (y > 0) {
    isMoving = true;
    --y;
  } else {
    if (debounce(lastUpdateTime, delayTime)) {
      isMoving = true;
      y = levelMap.width - 1;
    } else {
      length = 0;
      isMoving = false;
    }
  }
}


void Vehicle::setVehicleCellsLeft(byte x) {
  for (byte i = 0; i < y; ++i) {
    if (!player.isPlayer(x, i)) {
      levelMap.set(x, i, false);
    }
  }
  for (byte i = y+1; i < levelMap.width - 1; ++i) {
    if (!player.isPlayer(x, i)) {
      levelMap.set(x, i, false);
    }
  }
  for (byte i = 0; i < length && y + i < levelMap.width; ++i) {
    levelMap.set(x, y + i, true);
  }
}

void Vehicle::setVehicleCellsRight(byte x) {
  for (short i = y - 1; i > 0; --i) {
    if (!player.isPlayer(x, i)) {
      levelMap.set(x, i, false);
    }
  }
  
  if (!isMoving && !player.isPlayer(x, 0)) {
    levelMap.set(x, 0, false);
  }
  
  for (byte i = levelMap.width - 1; i > y; --i) { // >= ?
    if (!player.isPlayer(x, i)) {
      levelMap.set(x, i, false);
    }
  }

  if (isMoving) {
    for (byte i = 0; i < length && y - i >= 0; ++i) {
      levelMap.set(x, y - i, true);
    }
  }
}

void Vehicle::setVehicleCells(byte x) {
  if (direction) {
    setVehicleCellsRight(x);
  } else {
    setVehicleCellsLeft(x);
  }
}

void Vehicle::moveVehicle() {
  if (direction) {
    moveVehicleRight();
  } else {
    moveVehicleLeft();
  }
}

void Vehicle::update(byte x) {
  setVehicleCells(x);
  moveVehicle();
  if (isMoving) {
    increaseLength(x);
  }
}
