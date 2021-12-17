#include "HighScoreMenuState.h"

void HighScoreMenuState::printScore(byte index) {
  // if i don t do this the string will not be null-terminated
  const Highscore& score = savedData.highscores[index];
  char name[4] = {};
  strncpy(name, score.name, playerNameLen);
  
  lcd.print(index+1); // idented at 0
  lcd.print(". ");
  lcd.print(name);
  lcd.print(" ");
  lcd.print(score.score);
}

void HighScoreMenuState::printScores() {
  lcd.clear();

  lcd.setCursor(0, 0);
  printScore(topScoreIndex);

  if (topScoreIndex + 1 < maxHighScores) {
    lcd.setCursor(0, 1);
    printScore(topScoreIndex + 1);
  }
}

void HighScoreMenuState::onBegin() { 
  matrix.cupEffect();
  printScores(); 
}

void HighScoreMenuState::update() {
  if (js.isDownDebounce()) {
    topScoreIndex = (topScoreIndex + maxHighScores - 1) % maxHighScores;
    printScores();
  }
  if (js.isUpDebounce()) {
    topScoreIndex = (topScoreIndex + 1) % maxHighScores;
    printScores();
  }
  if (js.isPressedDebounce()) {
    setGameState(GameState::StartMenu);
  }
}
