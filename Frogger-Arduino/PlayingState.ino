#include "PlayingState.h"

// check if the game is over
// player has no lives or no more time
bool PlayingState::isGameOver() const {
  return player.hasNoLivesLeft() || timerDisplay.isFinished();
}

// on begin we get the difficulty set in the settings
// pause the timer, update the player and start the sound track
void PlayingState::onBegin() {
  savedDifficulty = getCurrentDif();

  timerDisplay.pause();

  paused = false;
  playerMoved = false;
  playerDied = false;

  buzzer.setMelody(tetrisMelody);
  buzzer.play();
}

// reset the player
void PlayingState::onEnd() {
  player.reset();
}

// check if the player crashed
// if the game is over, set the game state to game over
// is the player finished the level, set the game state to new level and play a sound
// check the button to pause/unpause the game
// and moves the panning camera according to the relative x
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

// render the lcd messages
// if the game is pause we get "game paused"
// if not we can see all the stats: difficulty, level, lives, etc
// and update the time, the map and the buzzer
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

  buzzer.updateOrRestart();
}
