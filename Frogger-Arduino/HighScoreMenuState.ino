#include "HighScoreMenuState.h"

// printing a high-score line with the player name and score
void HighScoreMenuState::printScore(byte index) {
  // if i don't do this the string will not be null-terminated
  const Highscore& score = savedData.highscores[index];
  char name[4] = {};
  strncpy(name, score.name, playerNameLen);
  
  lcd.print(index+1); // idented at 0
  lcd.print(F(". "));
  if (strlen(name)) {
    lcd.print(name);
  } else {
    lcd.print(F("NaN"));
  }
  lcd.print(F(" "));
  lcd.print(score.score);
}

// clears the screen and then prints the scores and arrows
void HighScoreMenuState::printScores() {
  lcd.clear();

  lcd.setCursor(0, 0);
  lcd.print('>');
  printScore(topScoreIndex);

  if (topScoreIndex + 1 < maxHighScores) {
    lcd.setCursor(0, 1);
    lcd.write((byte)0);
    printScore(topScoreIndex + 1);
  }
}

// on begin we set the mattrix effect to a cup and print the scores
void HighScoreMenuState::onBegin() { 
  matrix.cupEffect();
  printScores(); 
}

// the update function checks for input
// update the rows poisitions if so
// or go back to the menu if the js is pressed
void HighScoreMenuState::update() {
  if (js.isDownDebounce()) {
    topScoreIndex = (topScoreIndex + maxHighScores - 1) % maxHighScores;
    printScores();
    buzzer.playMenuTone();
  }
  if (js.isUpDebounce()) {
    topScoreIndex = (topScoreIndex + 1) % maxHighScores;
    printScores();
    buzzer.playMenuTone();
  }
  if (js.isPressedDebounce()) {
    buzzer.playMenuTone();
    setGameState(GameState::StartMenu);
  }
}
