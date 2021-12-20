#include "NewLevelState.h"

// prints the congrats message on reaching a new level
void NewLevelState::printInfo() const {
  lcd.clear();
  lcd.setCursor(3, 0);
  lcd.print(F("Good job!!"));
  lcd.setCursor(3, 1);
  lcd.print(F("Next lvl:"));
  lcd.print(levelMap.getLevel());
}

// increase the level, prints the congrats message and a happy face
void NewLevelState::onBegin() {
  levelMap.increaseLevel();
  printInfo();
  lastTime = updateTime;
  matrix.happyFace();
}

// clears both matrix and lcd
void NewLevelState::onEnd() {
  lcd.clear();
  matrix.clear();
}

// check the timer of the message to dissapear or for player input
void NewLevelState::update() {
  if (js.isPressedDebounce() || debounce(lastTime, messageDisplayDelay)) {
    setGameState(GameState::Starting);
  }
}
