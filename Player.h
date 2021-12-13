#pragma once

#include "Timer.h"

class Player {
  byte x, y;
  unsigned long actualY, actualX;  
  
  Timer lastMoveTime, lastJumpTime, lastDeathTime, lastUpdateTime;

  byte lives;
  byte jumps;
  bool canJump;
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

    byte getRelativeX() const;

    void moveTo(byte newX, byte newY);
    void jump();

    void setLives(byte newLives);
    byte getLives() const;
    void setJumps(byte newJumps);
    byte getJumps() const;
    bool hasNoLivesLeft() const;
    bool finishedLevel() const;
    void checkCrash();

    bool isPlayer(byte X, byte Y) const;
};

extern Player player;
