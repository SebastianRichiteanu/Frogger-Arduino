#include "StartingState.h"

#include "Player.h"
//#include "MelodyPlayer.h"
#include "Settings.h"


const Timer startUpTime = 5000;
const Timer scrollDelayTime = 150;

void StartingState::generateInitialMap() {
  levelMap.clean();
}

void StartingState::onBegin() {
  lcd.clear();
  lcd.setCursor(2, 0);
  lcd.print("Hi! Press JS");
  lcd.setCursor(4, 1);
  lcd.print("to start");

  levelMap.clean();
  levelMap.createWalls();
  player.reset();
}

void StartingState::update() {
  // song
  if (js.isPressedDebounce()) {
    timerDisplay.setTime(getStartingTimeByDif());
    setGameState(GameState::Playing);
  }
}

void StartingState::render() const{
  levelMap.render();
}
