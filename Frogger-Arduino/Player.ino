#include "Player.h" 

#define randomLives 0
#define randomJumps 1

// delay constants
const int blinkDelay = 500;
const int deathDelay = 2000;
const byte moveDelay = 100;
const byte jumpDelay = 150;

// bonus point timer value
const int bonusAddTime = 10000;

// default value for reset
const byte defaultY = 3;
const byte defaultX = levelMap.height - 1;

// player instance
Player player;

// sets the player cell on the map to a given value
void Player::setPlayerCell(bool value) { levelMap.set(x, y, value); }

// checks if the player collies left to a wall or the border of the matrix
bool Player::collidesLeft() const { 
  short currentWall = levelMap.walls[x - 1];
  if (currentWall) {
    if (currentWall > 0) {
      return y <= currentWall;
    } 
  }
  return y == 0; 
}

// checks if the player collies right to a wall or the border of the matrix
bool Player::collidesRight() const { 
  short currentWall = levelMap.walls[x - 1];
  if (currentWall) {
    if (currentWall < 0) {
      return y >= levelMap.width + currentWall - 1;
    } 
  }
  return y == 7;
}

// checks if the player collies up to a wall or the border of the matrix
bool Player::collidesUp() const { 
  short currentWall = levelMap.walls[x];
  if (currentWall) {
    if (currentWall > 0) {
      return y < currentWall;
    } else {
      return y >= levelMap.width + currentWall; 
    }
  }
  return x == levelMap.height - 1; 
}

// checks if the player collies down to a wall or the border of the matrix
bool Player::collidesDown() const { 
  short currentWall = levelMap.walls[x - 2];
  if (currentWall) {
    if (currentWall > 0) {
      return y < currentWall;
    } else {
      return y >= levelMap.width + currentWall; 
    }
  }
  return x == 0; 
}

// checks if the player position is the same of a bonus
// then collect it (remove the bonus, choose a random bonus
// and play a sound)
void Player::collectBonus() {
  if (y > 0 && y == levelMap.bonus[x - 1]) {
     levelMap.bonus[x - 1] = 0;
     getRandomBonus();
     buzzer.playBonus();
  }
}

// get a random reward for collecting the bonus point
// life, jump or more time
void Player::getRandomBonus() {
  switch (random(0, 3)) {
    case randomLives:
      ++lives;
      return;
    case randomJumps:
      ++jumps;
      return;
    default:
      timerDisplay.increaseTime(bonusAddTime);
      return;
  }
}

// move the player to a new position by setting the old cell to false
// chaning the x, y values and setting the new cell to true
void Player::moveTo(byte newX, byte newY) {
  setPlayerCell(false);
  x = newX;
  y = newY;
  setPlayerCell(true);
}

// check if the player can jump (it has a timer)
// if the player has jump movements
// and the player is not on the starting line
// if so move the player 2 positions up
void Player::jump() {
  if (canJump && jumps && x > 1) {
    --jumps;
    moveTo(x - 2, y);
  }
}

// resets the player to the default spawn position
// sets his cell to true and reset the timers
void Player::reset() {
  x = defaultX; 
  y = defaultY;
  setPlayerCell(true);
  canJump = false;

  lastUpdateTime = updateTime;
  lastJumpTime = updateTime;
}


// the update function checks for inputs and respond corresponing to them
// button press jump, left goes left, etc.
// also update the timers and blink player cell
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
// get the relative x position of the map (because of the panning camera)
byte Player::getRelativeX() const { return x - levelMap.getOffset(); }
byte Player::getY() const { return y; }

void Player::setLives(byte newLives) { lives = newLives; }
byte Player::getLives() const { return lives; }

void Player::setJumps(byte newJumps) { jumps = newJumps; }
byte Player::getJumps() const { return jumps; }

bool Player::hasNoLivesLeft() const { return lives == 0; }

bool Player::finishedLevel() const { return x == 0; }

bool Player::isPlayer(byte X, byte Y) const { return x == X && y == Y; }

// this function is called for every vehicle
// if the player is on a row with a vehicle
// and that vehicles is moving and the y position of the player
// is the same as the vehicle
// play a sound and decrease the number of lives
void Player::checkCrash() { 
  if (levelMap.vehicles[x - 1].getMoving() && levelMap.vehicles[x - 1].getY() == player.getY()) {
    if (debounce(lastDeathTime, deathDelay)) {
      buzzer.playCrashed();
      --lives;
    }
  }
}
