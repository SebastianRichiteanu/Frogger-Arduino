#include "Vehicle.h"
#include "Map.h"
#include "Settings.h"
#include "Player.h"

Vehicle::Vehicle() {
  isMoving = false;
  delayTime = random(5000, 10000); 
  lastUpdateTime = updateTime;
  lastBlinkUpdateTime = updateTime;
  // y = 0;
  y = levelMap.width;
  speed = random(0, 4) + getVehicleSpeedByDif();
  direction = random(0, 2);
  length = random(2, 5);
}

bool Vehicle::getMoving() { return isMoving; }

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
//      if (debounce(lastBlinkUpdateTime, blinkDelay)) {
//        visibility = !visibility;
//        if (visibility) {
//          levelMap.set(x, 0, false);
//        } else {
//          levelMap.set(x, 0, true);
//        }
//      }
    }
  }
}

//void Vehicle::moveVehicleRight(byte x) {
//  if (y > 0) {
//    --y;
//  } else {
//    if (debounce(lastUpdateTime, delayTime)) {
//      y = levelMap.width - 1;
//    } else {
//      // broken
//    }
//  }
//}


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

//void Vehicle::setVehicleCellsRight(byte x) {
//  for (byte i = 0; i < y + length; ++i) { // i < y + length - 1 for blink
//    Serial.println(i);
//    levelMap.set(x, y, false);
//  }
//  for (byte i = y + length; i < levelMap.width; ++i) {
//    levelMap.set(x, i, false);
//  }
//  if (y != 0)
//    for (byte i = 0; i < length && y + i < levelMap.width; ++i) {
//      levelMap.set(x, y + i, true);
//    }
//}


void Vehicle::update(byte x) {
  setVehicleCellsLeft(x);
  moveVehicleLeft(x);
}
