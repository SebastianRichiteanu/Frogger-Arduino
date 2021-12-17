#include "GameOverState.h"

#include "TimerDisplay.h"
#include "Player.h"
#include "Map.h"

const Timer messageDisplayDelay = 4000;

void GameOverState::printCongrats() {
  printingCongrats = true;
  printingScore = false;
  printingHighscore = false;
  matrix.sadFace();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Congrats for rea");
  lcd.setCursor(0, 1);
  lcd.print("ching score:");
  lcd.print(score.getCurrentScore());
}

void GameOverState::printScore() {
  printingCongrats = false;
  printingScore = true;
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Name: ");
  lcd.print(savedData.playerName);
  lcd.setCursor(12, 0);
  lcd.write((byte)0);
  lcd.print(":");
  lcd.print(player.getLives());
  lcd.setCursor(0, 1);
  lcd.print("Time: ");
  lcd.print(timerDisplay.getElapsedTimeInSec() - timerDisplay.getTimeLeftInSec());
  lcd.print(" s");
  lcd.setCursor(12, 1);
  lcd.print("J:");
  lcd.print(player.getJumps());
}

void GameOverState::printHighscore() {
  printingScore = false;
  if (score.isHighScore()) {
    printingHighscore = true;
    lcd.clear();
    lcd.setCursor(1, 0);
    lcd.print("You have a new");
    lcd.setCursor(3, 1);
    lcd.print("HIGHSCORE!");
  } else {
    printReturnToMenu();
  }
}

void GameOverState::printReturnToMenu() {
  printingHighscore = false;
  lcd.clear();
  lcd.setCursor(1, 0);
  lcd.print("Press JS to go");
  lcd.setCursor(2, 1);
  lcd.print("back to menu");
}

void GameOverState::onBegin() {
  score.addPointsForLevel(levelMap.getLevel() - 1);
  score.addPointsForTimeLeft(timerDisplay.getTimeLeftInSec());
  score.addPointsForLivesLeft(player.getLives());
 
  if (score.isHighScore()) {
    score.updateHighScoreList();
  }

  matrix.clear();
  lastTime = updateTime;
  printCongrats();
}

void GameOverState::onEnd() {
  score.reset();
  levelMap.setLevel(1);
}

void GameOverState::update() {
  if (debounce(printingCongrats, lastTime, messageDisplayDelay)) {
    printScore();
  }
  if (debounce(printingScore, lastTime, messageDisplayDelay)) {
    printHighscore();
  }

  if (js.isPressedDebounce()) {
    if (printingCongrats) {
      printScore();
    } else if (printingScore) {
      printHighscore();
    } else if (printingHighscore) {
      setGameState(GameState::StartMenu);
    } else if (!printingCongrats && !printingScore && !printingHighscore) {
      setGameState(GameState::StartMenu);
    } else {
      printReturnToMenu();
    }
  }
}
