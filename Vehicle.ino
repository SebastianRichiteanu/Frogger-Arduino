#include "Vehicle.h"

Vehicle::Vehicle() {
  blinking = false;
  isMoving = false;
  delayTime = random(5000, 10000); // TODO different for each dif
  lastUpdateTime = updateTime;
  lastBlinkUpdateTime = updateTime;
  if (direction) { // from right
    y = levelMap.width - 1;
  } else { // from left
    y = levelMap.width - 1;
  }
  speed = random(0, 4) + getVehicleSpeedByDif();
  direction = random(0, 2);
  length = random(2, 5);
  visibility = false;
}

bool Vehicle::getMoving() { return isMoving; }

void Vehicle::blink(byte x, byte y) {
  if (blinking) {
    if (debounce(lastBlinkUpdateTime, blinkDelay)) {
       visibility = !visibility;
       if (visibility) {
        levelMap.set(x, y, false);
       } else {
        levelMap.set(x, y, true);
       }
    }
  }
}

void Vehicle::moveVehicleLeft(byte x) { 
  if (y < levelMap.width) {
    isMoving = true;
    ++y; 
  } else {
    if (debounce(lastUpdateTime, delayTime)) {
      isMoving = true;
      y = 0;
    } else {
      isMoving = false;
      // kinda broken for now
      blink(x, 0);
    }
  }
}

void Vehicle::moveVehicleRight(byte x) {
  if (y > 0) {
    isMoving = true;
    --y;
  } else {
    if (debounce(lastUpdateTime, delayTime)) {
      isMoving = true;
      y = levelMap.width - 1;
    } else {
      isMoving = false;
      // kinda broken for now
      blink(x, 7);
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
  if (!isMoving) {
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

void Vehicle::moveVehicle(byte x) {
  if (direction) {
    moveVehicleRight(x);
  } else {
    moveVehicleLeft(x);
  }
}

void Vehicle::update(byte x) {
  setVehicleCells(x);
  moveVehicle(x);
}
