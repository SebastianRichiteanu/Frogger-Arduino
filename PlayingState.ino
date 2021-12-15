#include "PlayingState.h"

static byte heartChar[] = {0b00000,
  0b01010,
  0b11111,
  0b11111,
  0b01110,
  0b00100,
  0b00000,
  0b00000};

bool PlayingState::isGameOver() const {
  return player.hasNoLivesLeft() || timerDisplay.isFinished();
}

void PlayingState::onBegin() {
  savedDifficulty = getCurrentDif();

  timerDisplay.pause();

  paused = false;
  playerMoved = false;
  playerDied = false;

  buzzer.setMelody(tetrisMelody);
  buzzer.play();
}

void PlayingState::onEnd() {

  
  player.reset();
}


void PlayingState::update() {
  player.checkCrash();
  
  if (isGameOver()) {
    setGameState(GameState::GameOver);
  }

  if (player.finishedLevel()) {
    buzzer.playFinishedLevel();
    setGameState(GameState::NewLevel);
  }
  
  if (buttonPressed()) { 
    paused = !paused;
    if (paused) {
      timerDisplay.pause();
    } else {
      timerDisplay.unpause();
    }
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
  
  if (player.getRelativeX() < 3) {
    levelMap.moveDown();
  } 
  if (player.getRelativeX() > 4) {
    levelMap.moveUp();
  }
}

void PlayingState::render() const {
  if (paused) {
    lcd.clear();
    lcd.setCursor(2, 0);
    lcd.print("Game paused");
    lcd.setCursor(2, 1);
    lcd.print("Press Button");
    return;
  } else {
    lcd.clear();
    lcd.createChar(0, heartChar); // TODO do this once somewhere

    lcd.setCursor(0, 0);
    lcd.print("Dif:");
    lcd.print(getCurrentDifAsChar());
    
    lcd.setCursor(6, 0);
    lcd.print("Lvl:");
    lcd.print(levelMap.getLevel());

    lcd.setCursor(12, 0);
    lcd.write((byte)0);
    lcd.print(":");
    lcd.print(player.getLives());

    lcd.setCursor(0, 1);
    lcd.print("Time:");
    lcd.print(timerDisplay.getTimeLeftInSec());

    lcd.setCursor(9, 1);
    lcd.print("Jumps:");
    lcd.print(player.getJumps());
  }

  timerDisplay.update();
  levelMap.update();
  levelMap.render();

  // melody
  buzzer.updateOrRestart();
}
