#include "Map.h"

// the game map instance
Map levelMap;

// on creation sets the level to 1 and updates the timers
Map::Map() {
  level = 1;
  isActive = true;
  lastFinishBlinkUpdateTime = updateTime;
  lastBonusRemoveTime = updateTime;
}

// get one raw of the map
int Map::get(byte x) const { return data[x]; }

// get one position of the map
bool Map::get(byte x, byte y) const { return data[x].get(width - y - 1); }

// sets one position of the map to a given value
void Map::set(byte x, byte y, bool value) { data[x].set(width - y - 1, value); }

// sets an entire row to a given value
void Map::setRow(byte x, bool value) { 
  for (byte y = 0; y < width; ++y) {
    data[x].set(width - y - 1, value);
  }
}

// function to create the map walls
// it creats getNumberOfWallsByDif() number of wall
// with a randomX distance between them
// and a randomLen length
// and a randomDir direction 
// if 0 then from left to right, otherwise from right to left
void Map::createWalls() {
  byte lastRandom = 0;
  for (byte i = 0; i < getNumberOfWallsByDif(); ++i) {
    byte randomX = random(2, 4); 
    short randomLen = getLengthOfWallsByDif() * getLengthOfWallsByLvl();
    if (randomLen > 7) {
      randomLen = 7;
    }
    short randomDir = random(0, 2);
    if (randomDir) {
      randomLen = -randomLen;
    }
    lastRandom += randomX;
    walls[lastRandom] = randomLen;
  }
}

// function to create the bonus points
// it creats getNumberOfBonusByDif() number of bonus points
// with a row position of randomX
// and a column position of randomPos
void Map::createBonus() {
  lastBonusRemoveTime = updateTime;
  for (byte i = 0; i < getNumberOfBonusByDif(); ++i) {
    byte randomX = random(2, levelMap.height - 2);
    if (!walls[randomX] && !bonus[randomX]) {
      byte randomPos = random(1, 6); // not on the margins
      bonus[randomX] = randomPos;
    } else {
      --i;
    }
  }
}

// sets the bonus point value in the map to true
void Map::updateBonus(byte x) {
  levelMap.set(x + 1, bonus[x], true);
}

// sets the bonus point value in the map to false
// and delets the bonus from the array
void Map::removeBonus(byte x) {
  levelMap.set(x + 1, bonus[x], false);
  bonus[x] = 0;
}

// check the direction of the wall and sets 
// the corresponding map values to true
void Map::updateWalls(byte x) {
  short y = walls[x];
  byte offset = 0;
  if (y < 0) { // the wall is sticking to the right
    y = -y;
    offset = levelMap.width - y;
  }
  for (byte i = 0; i < y; ++i) {
    levelMap.set(x + 1, offset + i, true);
  }
}

// check the debounce on the finish line (the finish line is blinking)
// for each row it checks if we have a wall, update it
// if we have a vehicle update it
// if we have a bonus point and the removing of them started
  // debounces the timer and delets the bonus
// if we have a bonus point but the removing of them has not started
  // just update it
void Map::update() {
  if (debounce(lastFinishBlinkUpdateTime, blinkDelay) && xOffset == 0) {
    setRow(0, isActive);
    isActive = !isActive;
  }
  for (byte i = 0; i < levelMap.height - 2; ++i) { // - 2 (start line && finish line)
    if (walls[i]) { // if is a wall
      levelMap.updateWalls(i);
    } else {
      levelMap.vehicles[i].update(i + 1); // i + 1 = real x
      if (bonus[i] && level >= removeStartLevel) {
          if (debounce(lastBonusRemoveTime, removeDelay)) {
            removeBonus(i);
          }
      }
      if (bonus[i]) {
        levelMap.updateBonus(i);
      }
    }
  }
}


// sets the whole matrix to false and delets the bonus points and walls
void Map::clean() {
  for (byte i = 0; i < levelMap.height; ++i) {
    setRow(i, false);
    levelMap.bonus[i] = 0;
    levelMap.walls[i] = 0;
  }
}

// render the map on the matrix
void Map::render() const {
  for (byte row = 0; row < matrix.rows; ++row) {
    for (byte column = 0; column < matrix.columns; ++column)
      matrix.set(row, column, levelMap.get(row + xOffset, column));
  }
}

byte Map::getOffset() const { return xOffset; }

// change offset of the panning cammera when the player goes up
void Map::moveUp() {
  if (xOffset < levelMap.height - matrix.rows) {
    ++xOffset;
  }
}

// change offset of the panning cammera when the player goes down
void Map::moveDown() {
  if (xOffset > 0) {
    --xOffset;
  }
}

byte Map::getLevel() const { return level; }
bool Map::isFirstLevel() const { return level == 1; }
void Map::setLevel(byte newLevel) { level = newLevel; }
void Map::increaseLevel() { ++level; }
