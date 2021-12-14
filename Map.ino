#include "Map.h"
#include "Hardware.h"
#include "Matrix.h"
#include "Score.h"
#include "Settings.h"
#include "TimerDisplay.h"

Map levelMap;

Map::Map() {
  isActive = true;
  lastFinishBlinkUpdateTime = updateTime;
}

unsigned int Map::get(byte x) const { return data[x]; }
bool Map::get(byte x, byte y) const { return data[x].get(width - y - 1); }

void Map::setRow(byte x, bool value) { 
  for (byte y = 0; y < width; ++y) {
    data[x].set(width - y - 1, value);
  }
}
void Map::set(byte x, byte y, bool value) { data[x].set(width - y - 1, value); }

void Map::createWalls() {
  byte lastRandom = 0;
  for (byte i = 0; i < getNumberOfWallsByDif(); ++i) {
    byte randomX = random(2, 4); // distance between walls
    short randomLen = getLengthOfWallsByDif();
    short randomDir = random(0, 2); // direction
    if (randomDir) {
      randomLen = -randomLen;
    }
    lastRandom += randomX;
    walls[lastRandom] = randomLen;
  }
}

void Map::createBonus() {
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

void Map::updateBonus(byte x) {
//  if (debounce(lastBonusBlinkTime, blinkDelay)) {
//    levelMap.set(x + 1, bonus[x], bonusActive);
//    bonusActive = !bonusActive;
//  }
  levelMap.set(x + 1, bonus[x], true);
}

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
      if (bonus[i]) {
        levelMap.updateBonus(i);
      }
    }
  }
}

void Map::clean() {
  for (byte i = 0; i < levelMap.height; ++i) {
    setRow(i, false);
    levelMap.bonus[i] = 0;
    levelMap.walls[i] = 0;
  }
}

void Map::render() const {
  for (byte row = 0; row < matrix.rows; ++row) {
    for (byte column = 0; column < matrix.columns; ++column)
      matrix.set(row, column, levelMap.get(row + xOffset, column));
  }
}

byte Map::getOffset() const { return xOffset; }

void Map::moveUp() {
  if (xOffset < levelMap.height - matrix.rows) {
    ++xOffset;
  }
}

void Map::moveDown() {
  if (xOffset > 0) {
    --xOffset;
  }
}

//MapView

//void MapView::centerOnX() { xOffset = (levelMap.width - matrix.rows) / 2; }

//void MapView::moveToTop() { xOffset = levelMap.height - matrix.rows; }
