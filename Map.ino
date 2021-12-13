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

void Map::update() {
  if (debounce(lastFinishBlinkUpdateTime, blinkDelay) && xOffset == 0) {
    setRow(0, isActive);
    isActive = !isActive;
    lastFinishBlinkUpdateTime = updateTime;
  }
  for (byte i = 0; i < levelMap.height - 2; ++i) { // - 2 (start line && finish line)
    levelMap.vehicles[i].update(i + 1); // i + 1 = real x
  }
}

void Map::clean() {
  for (byte i = 0; i < levelMap.height; ++i) {
    setRow(i, false);
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
