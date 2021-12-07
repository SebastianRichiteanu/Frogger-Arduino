#include "StartingState.h"

#include "Player.h"
//#include "MelodyPlayer.h"
#include "Settings.h"
#include "Matrix.h"

const Timer startUpTime = 5000;
const Timer scrollDelayTime = 150;

void StartingState::generateInitialMap() {
  
}

void StartingState::onBegin() {
  lcd.clear();
  lcd.setCursor(3, 0);
  lcd.print("Loading...");

  // melody.play

  matrix.fill();
  player.reset();
}

void StartingState::update() {
  if (js.isPressedDebounce()) {
    setGameState(GameState::Playing);
  }
}

void StartingState::render() const{
  levelMap.render();
  // render lcd
}
