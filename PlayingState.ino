#include "PlayingState.h"

#include "Map.h"
#include "Player.h"
#include "Score.h"
// #include "TimeDisplay.h"

const Timer deathDelay = 2000;

bool PlayingState::isGameOver() const {
  return player.hasNoLivesLeft();// || timeDisplay.isFinished();
}

void PlayingState::onBegin() {
  savedDifficulty = getCurrentDif();

  lcd.clear();
  lcd.setCursor(1, 0);
  lcd.print("Use JS to move.");
  lcd.setCursor(0, 1);
  lcd.print("Press for pause.");

  // start melody

  player.moveTo(7, 3);

  paused = false;
  playerMoved = false;
  playerDied = false;
  
}

void PlayingState::onEnd() {
  // stop song
  // calculate points
  player.reset();
}

void PlayingState::update() {
  // if game over.. etc
  if (js.isPressedDebounce()) {
    paused = !paused;
  }

  if (paused) {
    return;
  }

  if (!playerMoved && (js.isLeftDebounce() || js.isRightDebounce() || js.isUpDebounce())) {
    playerMoved = true;
    lcd.clear();
  }

  if (!playerDied) {
    player.update();
  }
  
}

void PlayingState::render() const {
  if (paused) {
    lcd.clear();
    lcd.setCursor(2, 0);
    lcd.print("Game paused");
    lcd.setCursor(3, 1);
    lcd.print("Press JS");
    return;
  } else {
    lcd.clear(); // temporary
  }

  levelMap.render();
}
