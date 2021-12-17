#include "IntroState.h"

const int introDuration = 3000;

void IntroState::onBegin() {
  startTime = updateTime;

  lcd.clear();
  lcd.setCursor(5, 0);
  lcd.print("Frogger");
  lcd.setCursor(4, 1);
  lcd.print("Welcome!!");
}

void IntroState::update() {
  // skip menu or after time
  if (debounce(startTime, introDuration) || js.isPressedDebounce()) {
    setGameState(GameState::StartMenu);
  }
}
