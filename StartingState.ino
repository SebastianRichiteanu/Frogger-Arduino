#include "StartingState.h"

void StartingState::generateInitialMap() {
  levelMap.clean();
  levelMap.createWalls();
  levelMap.createBonus();
}

void StartingState::onBegin() {
  lcd.clear();
  lcd.setCursor(2, 0);
  lcd.print("Hi! Press JS");
  lcd.setCursor(4, 1);
  lcd.print("to start");

  generateInitialMap();
  player.reset();
  if (levelMap.isFirstLevel()) {
    player.setLives(getStartingLivesByDif());
    player.setJumps(getStartingJumpsByDif());
    timerDisplay.setTime(getStartingTimeByDif());
  }
}

void StartingState::update() {
  if (js.isPressedDebounce()) {
    setGameState(GameState::Playing);
  }
}

void StartingState::render() const{
  levelMap.render();
}
