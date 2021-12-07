#include "PlayingState.h"

#include "Map.h"
#include "Player.h"
#include "Score.h"
#include "TimerDisplay.h"

static byte heartChar[] = {0b00000,
  0b01010,
  0b11111,
  0b11111,
  0b01110,
  0b00100,
  0b00000,
  0b00000};

const Timer deathDelay = 2000;

bool PlayingState::isGameOver() const {
  return player.hasNoLivesLeft() || timerDisplay.isFinished() || player.finishedLevel();
}

void PlayingState::onBegin() {
  savedDifficulty = getCurrentDif();

//  lcd.clear();
//  lcd.setCursor(1, 0);
//  lcd.print("Use JS to move.");
//  lcd.setCursor(0, 1);
//  lcd.print("Press for pause.");

  // start melody

  player.moveTo(7, 3);
  player.setLives(getStartingLivesByDif());

  timerDisplay.pause();

  paused = false;
  playerMoved = false;
  playerDied = false;
  
}

void PlayingState::onEnd() {
  // stop song

  score.addPointsForTimeLeft(timerDisplay.getTimeLeftInSec());
  score.addPointsForLivesLeft(player.getLives());
  // score.addPointsForCollectedObj();

  if (score.isHighScore()) {
    score.updateHighScoreList();
  }
  
  player.reset();
}


void PlayingState::update() {
  if (isGameOver()) {
    setGameState(GameState::GameOver);
  }
  
  if (js.isPressedDebounce()) {
    paused = !paused;
  }

  if (paused) {
    return;
  } 

  timerDisplay.update();
   
  if (!playerMoved && js.isAnyDebounce()) {
    playerMoved = true;
    timerDisplay.unpause();
    lcd.clear();
  }

  if (!playerDied) {
    player.update();
  }

 
}

void PlayingState::render() const {
  if (paused) {
    lcd.clear();
    lcd.setCursor(2, 0);
    lcd.print("Game paused");
    lcd.setCursor(3, 1);
    lcd.print("Press JS");
    return;
  } else {
    lcd.clear();
    lcd.createChar(0, heartChar); // do this once somewhere

    lcd.setCursor(0, 0);
    lcd.print("Dif:");
    lcd.print(getCurrentDifAsChar());
    
    lcd.setCursor(6, 0);
    lcd.print("Lvl:1");

    lcd.setCursor(12, 0);
    lcd.write((byte)0);
    lcd.print(":");
    lcd.print(player.getLives());

    lcd.setCursor(0, 1);
   // lcd.print("Name:");
   // lcd.print(savedData.playerName);
    lcd.print("Time:");
    lcd.print(timerDisplay.getTimeLeftInSec());
    
  }

  timerDisplay.update();
  levelMap.render();
}
