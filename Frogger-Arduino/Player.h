#pragma once

class Player {
  byte x, y, lives, jumps;
  bool canJump;
  Timer lastMoveTime, lastJumpTime, lastDeathTime, lastUpdateTime, lastBoostTime;
  
  void setPlayerCell(bool value);

  bool collidesLeft() const;
  bool collidesRight() const;
  bool collidesUp() const;
  bool collidesDown() const;
  
  void collectBonus();
  void getRandomBonus();

  public:
    void moveTo(byte newX, byte newY);
    void jump();
    
    void reset();
    void update();

    byte getX() const;
    byte getRelativeX() const;
    byte getY() const;
    void setLives(byte newLives);
    byte getLives() const;
    void setJumps(byte newJumps);
    byte getJumps() const;
    bool hasNoLivesLeft() const;
    bool finishedLevel() const;
    bool isPlayer(byte X, byte Y) const;
    void checkCrash();
};

extern Player player;
