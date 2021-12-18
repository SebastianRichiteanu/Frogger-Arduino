#include "StartMenuState.h"

// constant for number of items in the start menu
const byte startMenuItems = 4;

// print the labels in the corresponding position of the lcd
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

// print the arrow in the corresponding position of the lcd
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

// delete the arrow in the correspoding position fo the lcd
// delete means overwriting the arrow with a blank space
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

// on begin the matrix & lcd are cleared, index is set to 0
// the menu labels are printed and the music starts
void StartMenuState::onBegin() { 
  matrix.clear();
  selIndex = 0; 
  lcd.clear();
  printMenuLabels();

  buzzer.setMelody(jingleBellsMelody);
  buzzer.play();
}

// on end the arrow get deleted and the lcd cleared
void StartMenuState::onEnd() {
  deleteSelectionArrow();
  lcd.clear();
}

// the update function checks for player input
// move the arrow corresponding to those inputs
// and if the js button is pressed
// the game state is changed to the selected label
// also updates the song
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

  buzzer.updateOrRestart();
}
