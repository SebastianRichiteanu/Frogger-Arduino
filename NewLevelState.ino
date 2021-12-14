#include "NewLevelState.h"

void NewLevelState::printInfo() const {
  lcd.clear();
  lcd.setCursor(3, 0);
  lcd.print("Good job!!");
  lcd.setCursor(3, 1);
  lcd.print("Next lvl:");
  lcd.print(levelMap.getLevel());
}

void NewLevelState::onBegin() {
  levelMap.increaseLevel();
  printInfo();
  lastTime = updateTime;
  matrix.happyFace();
}

void NewLevelState::onEnd() {
  lcd.clear();
  matrix.clear();
}

void NewLevelState::update() {
  if (js.isPressedDebounce() || debounce(lastTime, messageDisplayDelay)) {
    setGameState(GameState::Starting);
  }
}
