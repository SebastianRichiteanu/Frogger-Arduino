#pragma once

#include "Vehicle.h"
#include "BitOps.h"

class Map {
  public:
    static const byte height = 16, width = 8;
   
    static const byte removeStartLevel = 5, blinkDelay = 250;
    static const Timer removeDelay = 5000;

    bool isActive;
    byte level, xOffset = height - matrix.rows, bonus[height];;
    Timer lastFinishBlinkUpdateTime, lastBonusRemoveTime;
    Vehicle vehicles[height];
    short walls[height]; // if 0 no wall, if > 0 then length 

    Map();

    int get(byte row) const;
    bool get(byte x, byte y) const;

    void set(byte x, byte y, bool value);
    void setRow(byte x, bool value);
    
    void createWalls();
    void createBonus();
    void updateBonus(byte x);
    void removeBonus(byte x);
    void updateWalls(byte x);

    void update();
    void clean();
    void render() const;
    
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
