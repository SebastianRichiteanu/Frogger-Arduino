#pragma once

class Map {
  public:
    static const byte height = 8;
    static const byte width = 8;

    Map();

    unsigned int get(byte row) const;
    bool get(byte x, byte y) const;

    void set(byte x, byte y, bool value);

    // void createVehicle();

    // void createWall(int x, int y, int length);

    // void shiftDown(); ??

    void render() const;

    //void setTest(byte x);

  private:
    bool data[width][height];

    // byte prevX, prevY, prevLength;
};

extern Map levelMap;

/**
class MapView {
  byte xOffset, yOffset;

  public:
    MapView(byte x, byte y);

    byte get(byte row) const;

    byte getX() const;
    byte getY() const;

    void moveUp();

    // in game over scroll la toata harta?
    void moveToTop();
};

extern MapView currentView;
**/
