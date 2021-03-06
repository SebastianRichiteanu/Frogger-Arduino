#include "StartMenuState.h"

// index for menu options
#define startingIndex 0
#define highScoreIndex 1
#define aboutIndex 2
#define settingsIndex 3

// numbers for arrows in the main menu
// each figure is an arrow
// check Hardware.ino for more info
#define startingArrows 9305
#define highScoreArrows 2940
#define aboutArrows 1793
#define settingsArrows 6129

// constant for number of items in the start menu
const byte startMenuItems = 4;

// print the labels in the corresponding position of the lcd
void StartMenuState::printMenuLabels() const {
  lcd.setCursor(1, 0);
  lcd.print(F("Play"));

  lcd.setCursor(8, 0);
  lcd.print(F("HiScores"));

  lcd.setCursor(1,1);
  lcd.print(F("About"));

  lcd.setCursor(8,1);
  lcd.print(F("Settings"));
}

void StartMenuState::printChar(byte chr) const {
  if (chr == 9) { 
    lcd.print('>'); 
  } else {
    lcd.write((byte)chr);
  }
}

// print the arrows in the corresponding position of the lcd
// nr variable contains in each position the char code
// [up left corner, up right corner, down left corner, down right corner]
void StartMenuState::printSelectionArrows() const {
  int nr = startingArrows; // selIndex == startingIndex
  if (selIndex == highScoreIndex) {
    nr = highScoreArrows;
  } else if (selIndex == aboutIndex) {
    nr = aboutArrows;
  } else if (selIndex == settingsIndex) {
    nr = settingsArrows;
  }
  
  lcd.setCursor(0, 0);
  printChar(nr / 1000);
  lcd.setCursor(7, 0);
  printChar(nr / 100 % 10);
  lcd.setCursor(0, 1);
  printChar(nr / 10 % 10);
  lcd.setCursor(7, 1);
  printChar(nr % 10);
  
}

// on begin the matrix & lcd are cleared, index is set to 0
// the menu labels are printed and the music starts
void StartMenuState::onBegin() { 
  initMenuChars();
  matrix.clear();
  matrix.frogEffect();
  selIndex = 0; 
  lcd.clear();
  printMenuLabels();

  buzzer.setMelody(jingleBellsMelody);
  buzzer.play();
}

// on end the arrow get deleted and the lcd cleared
void StartMenuState::onEnd() {
  lcd.clear();
}

// the update function checks for player input
// move the arrow corresponding to those inputs
// and if the js button is pressed
// the game state is changed to the selected label
// also updates the song
void StartMenuState::update() {
  if (js.isLeftDebounce()) {
    selIndex = (selIndex + startMenuItems - 1) % startMenuItems;
    buzzer.playMenuTone();
  } 
  if (js.isRightDebounce()) {
    selIndex = (selIndex + 1) % startMenuItems;
    buzzer.playMenuTone();
  }
  if (js.isUpDebounce()) {
    selIndex = (selIndex + startMenuItems - 2) % startMenuItems;
    buzzer.playMenuTone();
  }
  if (js.isDownDebounce()) {
    selIndex = (selIndex + startMenuItems + 2) % startMenuItems;
    buzzer.playMenuTone();
  }

  if (js.isPressedDebounce()) {
    switch(selIndex) {
      case startingIndex:
        setGameState(GameState::Starting);
        break;
      case highScoreIndex:
        setGameState(GameState::HighScoreMenu);
        break;
      case aboutIndex:
        setGameState(GameState::AboutMenu);
        break;
      case settingsIndex:
        setGameState(GameState::SettingsMenu);
        break;
    }
  }
  if (checkMainState()) {
    printSelectionArrows();
  }

  buzzer.updateOrRestart();
}
