#include "Vehicle.h"

// the constructor sets the delay time to the random and modified by difficulty and level value
// updates the update time
// sets the y to the max
// pick a random direction
// a randon length

Vehicle::Vehicle() {
  isMoving = false;
  delayTime = random(5000, 10000) * vehicleDelayByDif() * vehicleDelayByLevel();
  lastUpdateTime = updateTime;
  direction = random(0, 2);
  if (!direction) {
    y = levelMap.width - 1;
  }
  maxLength = random(2, 5) * vehicleLenByDif() * vehicleLenByLevel();
  length = 0;
}

// set the vehicle cells to true
// move the vehicle to the corresponding direction
// and increase it's length 
void Vehicle::update(byte x) {
  setVehicleCells(x);
  moveVehicle();
  if (isMoving) {
    increaseLength(x);
  }
}

bool Vehicle::getMoving() const { return isMoving; }

byte Vehicle::getY() const { return y; }

// increase the length of the vehicle by one
// this will make the vehicles appear more fluently
void Vehicle::increaseLength(byte x) {
  if (length < maxLength) {
    ++length;
  }
}

// move the vehicle in the corresponding direction
void Vehicle::moveVehicle() {
  if (direction) {
    moveVehicleRight();
  } else {
    moveVehicleLeft();
  }
}

// if the vehicle has space to move, move it (increase y)
// if not debounce the freeze time before the vehicle appears again
// if that timer passed the vehicle is moving and the y is reset to 0
// if not length is 0 and the vehicle is not moving
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

// set the vehicle cells by the corresponding direction
void Vehicle::setVehicleCells(byte x) {
  if (direction) {
    setVehicleCellsRight(x);
  } else {
    setVehicleCellsLeft(x);
  }
}

// turn off the cells that are before the "head" of the vehicle
// turn off the cells that are after the "head" of the vehicle
// if one of those cells is the player don't turn them off
// turn on the cells that are the full vehicle

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
  
  for (byte i = levelMap.width - 1; i > y; --i) {
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
