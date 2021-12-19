#include "SaveSettingsMenuState.h"
#include "SettingsMenuState.h"

// const for this menu options
const byte saveSettingsMenuItems = 2;

// print the lcd messages
void SaveSettingsMenuState::printMenuLabels() const {
  lcd.setCursor(1, 0);
  lcd.print("Save Settings?");

  lcd.setCursor(1, 1);
  lcd.print("yes");

  lcd.setCursor(14, 1);
  lcd.print("no");
}

// print the selection arrow to the selected item
void SaveSettingsMenuState::printSelectionArrow() const {
  if (selIndex == 0) {
    lcd.setCursor(0, 1);
  } else {
    lcd.setCursor(13, 1);
  }
  lcd.print('>');
}

// revert the settings to the old ones
// the copy saved data is instantiated every time
// the player opens the settings menu
void SaveSettingsMenuState::resetSettings() {
  strcpy(savedData.playerName, copySavedData.playerName);
  savedData.lcdBrightness = copySavedData.lcdBrightness;
  savedData.lcdContrast = copySavedData.lcdContrast;
  savedData.matrixBrightness = copySavedData.matrixBrightness;
  savedData.difficulty = copySavedData.difficulty;
  savedData.musicState = copySavedData.musicState;
  savedData.soundState = copySavedData.soundState;
}

void SaveSettingsMenuState::onBegin() { selIndex = 0; }

// check for player input to change the selected item
// if the selected item is yes 
  // update the hardware to the new settings and save them to the EEPROM
// if not
  // revert the settings and save them to the EEPROM 
void SaveSettingsMenuState::update() {
  if (js.isLeftDebounce()) {
    selIndex = (selIndex + saveSettingsMenuItems - 1) % saveSettingsMenuItems;
  }
  if (js.isRightDebounce()) {
    selIndex = (selIndex + 1) % saveSettingsMenuItems;
  }
  if (js.isPressedDebounce()) {
    if (selIndex == 0) {
      updateHardware();
      saveSavedData();
    } else {
      resetSettings();
      updateHardware();
      saveSavedData();
    }
    setGameState(GameState::StartMenu);
  }
}

// clear the lcd and print the labels and the arrow
void SaveSettingsMenuState::render() const {
  lcd.clear();
  printMenuLabels();
  printSelectionArrow();
}
