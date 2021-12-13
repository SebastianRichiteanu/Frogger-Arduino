#pragma once

#include "Vehicle.h"
#include "Matrix.h"
#include "BitOps.h"

class Map {
  public:
    static const byte height = 16;
    static const byte width = 8;
    byte xOffset = height - matrix.rows;
    static const byte blinkDelay = 250;
    bool isActive;
    Timer lastFinishBlinkUpdateTime;
    Vehicle vehicles[height];

    Map();

    unsigned int get(byte row) const;
    bool get(byte x, byte y) const;

    void setRow(byte x, bool value);
    void set(byte x, byte y, bool value);

    bool hasSpaceLeft();

    // void createWall(int x, int y, int length);

    void render() const;

    void clean();

    void update();


    byte getOffset() const;
    void moveUp();
    void moveDown();

  private:
    Bitfield<unsigned int> data[height];
    //bool data[width][height];

    // byte prevX, prevY, prevLength;
};

extern Map levelMap;
