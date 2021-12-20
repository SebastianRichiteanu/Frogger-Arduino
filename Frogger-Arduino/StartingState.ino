#include "StartingState.h"

// generating the initial map by cleaning it 
// and creating new walls and bonus points
void StartingState::generateInitialMap() {
  levelMap.clean();
  levelMap.createWalls();
  levelMap.createBonus();
}

// on begin the lcd gets cleared and then prompts the "hi!" messaged
// the map is generated, the player reset
// and if is the first level, the player stats are reset
void StartingState::onBegin() {
  initHeart();
  lcd.clear();
  lcd.setCursor(2, 0);
  lcd.print(F("Hi! Press JS"));
  lcd.setCursor(4, 1);
  lcd.print(F("to start"));

  generateInitialMap();
  player.reset();
  if (levelMap.isFirstLevel()) {
    player.setLives(getStartingLivesByDif());
    player.setJumps(getStartingJumpsByDif());
    timerDisplay.setTime(getStartingTimeByDif());
  }
}

// if the player pressed the js 
// the game state is changed to playing
void StartingState::update() {
  if (js.isPressedDebounce()) {
    setGameState(GameState::Playing);
  }
}

// render the map
void StartingState::render() const{
  levelMap.render();
}
