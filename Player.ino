#include "Player.h" 

#include "Joystick.h"
#include "Map.h"
#include "Score.h"
#include "Timer.h"

const Timer blinkDelay = 500;
const Timer moveDelay = 120;

Player player;

void Player::setPlayerCell(bool value) { levelMap.set(x, y, value); }


bool Player::collidesLeft() const { 
  short currentWall = levelMap.walls[x - 1];
  if (currentWall) {
    if (currentWall > 0) {
      return y <= currentWall;
    } 
  }
  return y == 0; 
}
bool Player::collidesRight() const { 
  short currentWall = levelMap.walls[x - 1];
  if (currentWall) {
    if (currentWall < 0) {
      return y >= levelMap.width + currentWall;
    } 
  }
  return y == 7;
}
bool Player::collidesUp() const { 
  short currentWall = levelMap.walls[x];
  if (currentWall) {
    if (currentWall > 0) {
      return y < currentWall;
    } else {
      return y >= levelMap.width + currentWall; // -1
    }
  }
  return x == levelMap.height - 1; 
}
bool Player::collidesDown() const { 
  short currentWall = levelMap.walls[x - 2];
  if (currentWall) {
    if (currentWall > 0) {
      return y < currentWall;
    } else {
      return y >= levelMap.width + currentWall; // -1
    }
  }
  return x == 0; 
}

void Player::moveTo(byte newX, byte newY) {
  setPlayerCell(false);
  x = newX;
  y = newY;
  setPlayerCell(true);
}

void Player::reset() {
  x = levelMap.height - 1; 
  y = 3;
  setPlayerCell(true);

  actualY = y;
  lastUpdateTime = updateTime;
}

void Player::update() {
  if (updateTime - lastMoveTime > moveDelay) {
    if (js.isLeftDebounce() && !collidesLeft()) {
      moveTo(x, y - 1);
    } 
    if (js.isRightDebounce() && !collidesRight()) {
      moveTo(x, y + 1);
    }
    if (js.isUpDebounce() && !collidesUp()) {
      moveTo(x + 1, y);
    }
    if (js.isDownDebounce() && !collidesDown()) {
      moveTo(x - 1, y);
    }

    lastMoveTime = updateTime;
  }

  if (updateTime % blinkDelay > blinkDelay / 4) {
    setPlayerCell(true);
  } else {
    setPlayerCell(false);
  }

}

byte Player::getX() const { return x; }
byte Player::getY() const { return y; }

void Player::setLives(byte newLives) { lives = newLives; }
byte Player::getLives() const { return lives; }

bool Player::hasNoLivesLeft() const { return lives == 0; }

bool Player::finishedLevel() const { return x == 0; }

bool Player::isPlayer(byte X, byte Y) const { return x == X && y == Y; }

void Player::checkCrash() { 
  if (levelMap.vehicles[x - 1].getMoving() && debounce(lastDeathTime, deathDelay)) {
    buzzer.playCrashed();
    --lives;
    
  }
}

byte Player::getRelativeX() const { return x - levelMap.getOffset(); }
  
