#include "SaveSettingsMenuState.h"
#include "SettingsMenuState.h"

const byte saveSettingsMenuItems = 2;

void SaveSettingsMenuState::printMenuLabels() const {
  lcd.setCursor(1, 0);
  lcd.print("Save Settings?");

  lcd.setCursor(1, 1);
  lcd.print("yes");

  lcd.setCursor(14, 1);
  lcd.print("no");
}

void SaveSettingsMenuState::printSelectionArrow() const {
  if (selIndex == 0) {
    lcd.setCursor(0, 1);
  } else {
    lcd.setCursor(13, 1);
  }
  lcd.print('>');
}

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
      saveSavedData();
    }
    setGameState(GameState::StartMenu);
  }
}

void SaveSettingsMenuState::render() const {
  lcd.clear();
  printMenuLabels();
  printSelectionArrow();
}
