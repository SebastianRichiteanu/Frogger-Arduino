#include "StartMenuState.h"
#include "Buzzer.h"

const byte startMenuItems = 4;

void StartMenuState::printMenuLabels() const {
  lcd.setCursor(1, 0);
  lcd.print("Play");

  lcd.setCursor(8, 0);
  lcd.print("HiScores");

  lcd.setCursor(1,1);
  lcd.print("About");

  lcd.setCursor(8,1);
  lcd.print("Settings");
}

void StartMenuState::printSelectionArrow() const {
  switch(selIndex) {
    case 1:
      lcd.setCursor(7,0);
      break;
    case 2:
      lcd.setCursor(0,1);
      break;
    case 3:
      lcd.setCursor(7,1);
      break;
    default:
      lcd.setCursor(0,0);
      break;
  }
  lcd.print('>');
}

void StartMenuState::deleteSelectionArrow() const {
  switch(selIndex) {
    case 1:
      lcd.setCursor(7,0);
      break;
    case 2:
      lcd.setCursor(0,1);
      break;
    case 3:
      lcd.setCursor(7,1);
      break;
    default:
      lcd.setCursor(0,0);
      break;
  }
  lcd.print(' ');
}

void StartMenuState::onBegin() { 
  selIndex = 0; 
  lcd.clear();
  printMenuLabels();

  buzzer.setMelody(jingleBellsMelody);
  buzzer.play();
}

void StartMenuState::onEnd() {
  deleteSelectionArrow();
  lcd.clear();
}

void StartMenuState::update() {
  deleteSelectionArrow();
  if (js.isLeftDebounce()) {
    selIndex = (selIndex + startMenuItems - 1) % startMenuItems;
  } 
  if (js.isRightDebounce()) {
    selIndex = (selIndex + 1) % startMenuItems;
  }
  if (js.isUpDebounce()) {
    selIndex = (selIndex + startMenuItems - 2) % startMenuItems;
  }
  if (js.isDownDebounce()) {
    selIndex = (selIndex + startMenuItems + 2) % startMenuItems;
  }

  if (js.isPressedDebounce()) {
    switch(selIndex) {
      case 0:
        setGameState(GameState::Starting);
        break;
      case 1:
        setGameState(GameState::HighScoreMenu);
        break;
      case 2:
        setGameState(GameState::AboutMenu);
        break;
      case 3:
        setGameState(GameState::SettingsMenu);
        break;
    }
  }
  if (checkMainState()) {
    printSelectionArrow();
  }

  // melody
  buzzer.updateOrRestart();

  
}
