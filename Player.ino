#include "Player.h" 

const int blinkDelay = 500;
const int deathDelay = 2000;
const byte moveDelay = 100;
const byte jumpDelay = 150;

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

void Player::collectBonus() {
  if (y > 0 && y == levelMap.bonus[x - 1]) {
     levelMap.bonus[x - 1] = 0;
     getRandomBonus();
     buzzer.playBonus();
  }
}

void Player::getRandomBonus() {
  switch (random(0, 3)) {
    case 0:
      ++lives;
      return;
    case 1:
      ++jumps;
      return;
    default:
      timerDisplay.increaseTime(10000);
      return;
  }
}

void Player::moveTo(byte newX, byte newY) {
  setPlayerCell(false);
  x = newX;
  y = newY;
  setPlayerCell(true);
}

void Player::jump() {
  if (canJump && jumps && x > 1) {
    --jumps;
    moveTo(x - 2, y);
  }
}

void Player::reset() {
  x = levelMap.height - 1; 
  y = 3;
  setPlayerCell(true);
  canJump = false;

  lastUpdateTime = updateTime;
  lastJumpTime = updateTime;
}

void Player::update() {
  
  if (debounce(lastJumpTime, jumpDelay)) {
    if (js.isPressed()) {
      jump();
    }
  }
  
  if (debounce(lastMoveTime, moveDelay)) { 
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

  canJump = true;
  collectBonus();
}

byte Player::getX() const { return x; }
byte Player::getRelativeX() const { return x - levelMap.getOffset(); }
byte Player::getY() const { return y; }

void Player::setLives(byte newLives) { lives = newLives; }
byte Player::getLives() const { return lives; }

void Player::setJumps(byte newJumps) { jumps = newJumps; }
byte Player::getJumps() const { return jumps; }

bool Player::hasNoLivesLeft() const { return lives == 0; }

bool Player::finishedLevel() const { return x == 0; }

bool Player::isPlayer(byte X, byte Y) const { return x == X && y == Y; }

void Player::checkCrash() { 
  if (levelMap.vehicles[x - 1].getMoving() && levelMap.vehicles[x - 1].getY() == player.getY()) {
    if (debounce(lastDeathTime, deathDelay)) {
      buzzer.playCrashed();
      --lives;
    }
  }
}
