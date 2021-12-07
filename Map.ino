#include "Map.h"

#include "Hardware.h"
#include "Matrix.h"
#include "Score.h"
#include "Settings.h"
// #include "TimeDisplay.h"

Map levelMap;

Map::Map() {
  for (byte i = 0; i < 8; ++i)
    for (byte j = 0; j < 8; ++j)
      data[i][j] = false;
}

//bool[] Map::get(byte row) const { return data[row]; }
bool Map::get(byte x, byte y) const { return data[x][y]; }

void Map::set(byte x, byte y, bool value) { data[x][y] = value; }


void Map::render() const {
  for (byte row = 0; row < 8; ++row) {
    for (byte column = 0; column < 8; ++column)
      matrix.set(row, column, levelMap.get(row, column));
  }
}


/**
MapView::MapView(byte x, byte y) : xOffset(x), yOffset(y) {}

byte MapView::get(byte row) const {
  byte mapRow = yOffset + (matrix.rows - 1 - row);
  return levelMap.get(mapRow);
}


byte MapView::getX() const { return xOffset; }
byte MapView::getY() const { return yOffset; }
void MapView::moveUp() {
  if (yOffset < levelMap.height - matrix.rows) {
    ++yOffset;
  }
}

void MapView::moveToTop() { yOffset = levelMap.height - matrix.rows; }
**/
