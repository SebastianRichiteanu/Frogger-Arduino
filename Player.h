#pragma once

#include "Timer.h"

class Player {
  byte x, y;
  unsigned long actualY, actualX;  
  
  Timer lastMoveTime;

  byte lives;
  void setPlayerCell(bool value);

  bool collidesLeft() const;
  bool collidesRight() const;
  bool collidesUp() const;
  bool collidesDown() const;

  public:
    void reset();
    void update();

    byte getX() const;
    byte getY() const;

    unsigned long getActualHeight() const;

    int getRelativeX() const;
    int getRelativeY() const;

    void moveTo(byte newX, byte newY);

    void setLives(byte newLives);
    byte getLives() const;
    bool hasNoLivesLeft() const;
    bool finishedLevel() const;
    bool wasCrashed() const;

    bool isPlayer(byte X, byte Y) const;
};

extern Player player;
