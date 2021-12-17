#pragma once

#include "Vehicle.h"
#include "BitOps.h"

class Map {
  public:
    static const byte height = 16;
    static const byte width = 8;
    byte xOffset = height - matrix.rows;

    byte level;
    static const byte removeStartLevel = 5;
    static const Timer removeDelay = 5000;
    static const byte blinkDelay = 250;
    bool isActive;
    Timer lastFinishBlinkUpdateTime, lastBonusRemoveTime;
    Vehicle vehicles[height];
    byte bonus[height]; // if 0 no bonus, if > 0 then bonus point at matrix[x][bonus[x]]
    short walls[height]; // if 0 no wall, if > 0 then length 

    Map();

    int get(byte row) const;
    bool get(byte x, byte y) const;

    void setRow(byte x, bool value);
    void set(byte x, byte y, bool value);
    bool hasSpaceLeft();
    void createWalls();
    void updateWalls(byte x);
    void createBonus();
    void removeBonus(byte x);
    void updateBonus(byte x);

    void render() const;
    void clean();
    void update();

    byte getOffset() const;
    void moveUp();
    void moveDown();

    byte getLevel() const;
    bool isFirstLevel() const;
    void setLevel(byte newLevel);
    void increaseLevel();
    
  private:
    Bitfield<int> data[height];
};

extern Map levelMap;
