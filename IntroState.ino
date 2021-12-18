#include "IntroState.h"

// const for duration of intro message
const int introDuration = 3000;

// set the start time to the actual time
// and prints a welcome message
void IntroState::onBegin() {
  startTime = updateTime;

  lcd.clear();
  lcd.setCursor(5, 0);
  lcd.print("Frogger");
  lcd.setCursor(4, 1);
  lcd.print("Welcome!!");
}

// the update function check if the js is pressed
// to skip the message or waits for the debounce
void IntroState::update() {
  if (debounce(startTime, introDuration) || js.isPressedDebounce()) {
    setGameState(GameState::StartMenu);
  }
}
