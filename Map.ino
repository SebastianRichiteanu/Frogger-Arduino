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

bool Map::get(byte x, byte y) const { return data[x][y]; }

void Map::setRow(byte x, bool value) { 
  for (byte y = 0; y < width; ++y) {
    data[x][y] = value;
  }
}
void Map::set(byte x, byte y, bool value) { data[x][y] = value; }

void Map::update() {
  if (debounce(lastFinishBlinkUpdateTime, blinkDelay)) {
    setRow(0, isActive);
    isActive = !isActive;
    lastFinishBlinkUpdateTime = updateTime;
  }
  for (byte i = 0; i < levelMap.height - 2; ++i) { // - 2 (start line && finish line)
    levelMap.vehicles[i].update(i + 1); // i + 1 = real x
  }
}

void Map::clean() {
  for (byte i = 0; i < 8; ++i)
    setRow(i, false);
}

void Map::render() const {
  for (byte row = 0; row < 8; ++row) {
    for (byte column = 0; column < 8; ++column)
      matrix.set(row, column, levelMap.get(row, column));
  }
}
