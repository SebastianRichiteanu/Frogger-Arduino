#include "Player.h" 

#include "Joystick.h"
#include "Map.h"
#include "Score.h"
#include "Timer.h"

const Timer blinkDelay = 500;
const Timer moveDelay = 120;

Player player;

void Player::setPlayerCell(bool value) { levelMap.set(x, y, value); }

bool Player::collidesLeft() const { return 0; }
bool Player::collidesRight() const { return 0; }
bool Player::collidesUp() const { return 0; }
bool Player::collidesDown() const { return 0; }

void Player::moveTo(byte newX, byte newY) {
  setPlayerCell(false);
  x = newX;
  y = newY;
  setPlayerCell(true);
}

void Player::reset() {
  x = 7;
  y = 3;
  setPlayerCell(true);

  actualY = y;
  lastMoveTime = 0;
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

int Player::getRelativeX() const { return 0; } //return int(x) - currentView.getX(); 
  

int Player::getRelativeY() const { return 0; } //return int(y) - currentView.getY(); }
