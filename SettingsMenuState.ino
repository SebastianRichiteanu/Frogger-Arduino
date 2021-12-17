#include "SettingsMenuState.h"

const byte settingsNum = 7;

const Timer arrowBlinkDelay = 1000;
const Timer chrBlinkDelay = 500;

const char nameFieldString[] = "Name: ";

void SettingsMenuState::clearSelArrow() {
  lcd.setCursor(0, 0);
  lcd.print(" ");
}

void SettingsMenuState::printSelArrow() {
  lcd.setCursor(0, 0);
  lcd.print(">");
}

void SettingsMenuState::printNameField() {
  lcd.print(nameFieldString);
  lcd.print(savedData.playerName);
}

void SettingsMenuState::printDifficultyLevelField() {
  lcd.print("Diff: ");
  if (isEditing && currentIndex == 1) {
    lcd.print("{");
  }
  lcd.print(getCurrentDifAsString());
  if (isEditing && currentIndex == 1) {
    lcd.print("}");
  }
}

void SettingsMenuState::printLcdContrast() {
  lcd.print("Contrast: ");
  if (isEditing && currentIndex == 2) {
    lcd.print("{");
  }
  lcd.print(savedData.lcdContrast);
  if (isEditing && currentIndex == 2) {
    lcd.print("}");
  }
}

void SettingsMenuState::printLcdBrightness() {
  lcd.print("LCD Bright:");
  if (isEditing && currentIndex == 3) {
    lcd.print("{");
  } else {
    lcd.print(" ");
  }
  lcd.print(savedData.lcdBrightness);
  if (isEditing && currentIndex == 3) {
    lcd.print("}");
  }
}

void SettingsMenuState::printMatrixBright() {
  lcd.print("Mat Bright:");
  if (isEditing && currentIndex == 4) {
    lcd.print("{");
  } else {
    lcd.print(" ");
  }
  lcd.print(savedData.matrixBrightness);
  if (isEditing && currentIndex == 4) {
    lcd.print("}");
  }
}

void SettingsMenuState::printMusicState() {
  lcd.print("Music:");
  if (isEditing && currentIndex == 5) {
    lcd.print("{");
  } else {
    lcd.print(" ");
  }
  if (savedData.musicState) {
    lcd.print("ON");
  } else {
    lcd.print("OFF");
  }
  if (isEditing && currentIndex == 5) {
    lcd.print("}");
  }
}

void SettingsMenuState::printSoundState() {
  lcd.print("Sound:");
  if (isEditing && currentIndex == 6) {
    lcd.print("{");
  } else {
    lcd.print(" ");
  }
  if (savedData.soundState) {
    lcd.print("ON");
  } else {
    lcd.print("OFF");
  }
  if (isEditing && currentIndex == 6) {
    lcd.print("}");
  }
}

void SettingsMenuState::printField(byte index) {
  if (index == 0) {
    printNameField();
  } else if (index == 1) {
    printDifficultyLevelField();
  } else if (index == 2) {
    printLcdContrast();
  } else if (index == 3) {
    printLcdBrightness();
  } else if (index == 4) {
    printMatrixBright();
  } else if (index == 5) {
    printMusicState();
  } else if (index == 6) {
    printSoundState();
  }
}

void SettingsMenuState::printFields(byte index) {
  lcd.clear();
  lcd.setCursor(1, 0);
  printField(index);

  lcd.setCursor(0, 1);
  lcd.print(" ");
  printField(index + 1);
}

void SettingsMenuState::changeToPrevChar() {
  char& ch = savedData.playerName[chrIndex];
  if (ch == 'a') {
    ch = 'z';
  } else {
    ch = 'a' + (ch - 'a' + 25) % 26;
  }
}

void SettingsMenuState::changeToNextChar() {
  char& ch = savedData.playerName[chrIndex];
  if (ch == 'z') {
    ch = 'a';
  } else {
    ch = 'a' + (ch - 'a' + 1) % 26;
  }
}

void SettingsMenuState::copySaveData() {
  strcpy(copySavedData.playerName, savedData.playerName);
  copySavedData.lcdBrightness = savedData.lcdBrightness;
  copySavedData.lcdContrast = savedData.lcdContrast;
  copySavedData.matrixBrightness = savedData.matrixBrightness;
  copySavedData.difficulty = savedData.difficulty;
  copySavedData.musicState = savedData.musicState;
  copySavedData.soundState = savedData.soundState;
}

void SettingsMenuState::onBegin() {
  copySaveData();
  currentIndex = 0;
  isEditing = false;
  printFields(currentIndex);
  matrix.hammerEffect();
}

void SettingsMenuState::update() {
  if (js.isPressedDebounce()) {
    isEditing = !isEditing;
    if (currentIndex == 0) {
      chrIndex = 0;
    }
    printFields(currentIndex);
  }

  if (isEditing) {
    
    if (updateTime % arrowBlinkDelay > arrowBlinkDelay / 2) {
      printSelArrow();
    } else {
      clearSelArrow();
    }
  
    if (currentIndex == 0) {
      if (js.isLeftDebounce()) {
        chrIndex = (chrIndex + playerNameLen - 1) % playerNameLen;
        printFields(currentIndex);
      }
      if (js.isRightDebounce()) {
        chrIndex = (chrIndex + 1) % playerNameLen;
        printFields(currentIndex);
      }
      if (js.isUpDebounce()) {
        changeToPrevChar();
      }
      if (js.isDownDebounce()) {
        changeToNextChar();
      }
      lcd.setCursor(sizeof(nameFieldString) + chrIndex, 0);
      if (updateTime % chrBlinkDelay > chrBlinkDelay / 2) {
        lcd.print(' ');
      } else {
        lcd.print(savedData.playerName[chrIndex]);
      } 
    } else if (currentIndex == 1) {
      if (js.isLeftDebounce()) {
        decreaseDifficulty();
        printFields(currentIndex);
      } 
      if (js.isRightDebounce()) {
        increaseDifficulty();
        printFields(currentIndex);
      }
    } else if (currentIndex == 2) {
      if (js.isLeftDebounce()) {
        decreaseLcdContrast();
        printFields(currentIndex);
        updateHardware();
      }
      if (js.isRightDebounce()) {
        increaseLcdContrast();
        printFields(currentIndex);
        updateHardware();
      }
    } else if (currentIndex == 3) {
      if (js.isLeftDebounce()) {
        decreaseLcdBrightness();
        printFields(currentIndex);
        updateHardware();
      }
      if (js.isRightDebounce()) {
        increaseLcdBrightness();
        printFields(currentIndex);
        updateHardware();
      }
    } else if (currentIndex == 4) {
      if (js.isLeftDebounce()) {
        decreaseMatrixBright();
        printFields(currentIndex);
        updateHardware();
      }
      if (js.isRightDebounce()) {
        increaseMatrixBright();
        printFields(currentIndex);
        updateHardware();
      }
    } else if (currentIndex == 5) {
      if (js.isLeftDebounce() || js.isRightDebounce()) {
        changeMusicState();
        printFields(currentIndex);
      } 
    } else if (currentIndex == 6) {
      if (js.isLeftDebounce() || js.isRightDebounce()) {
        changeSoundState();
        printFields(currentIndex);
      }
    }
    
  } else {
    printSelArrow();
    if (js.isDownDebounce()) {
      currentIndex = (currentIndex + settingsNum - 1) % settingsNum;
      printFields(currentIndex);
    } 
    if (js.isUpDebounce()) {
      currentIndex = (currentIndex + 1) % settingsNum;
      printFields(currentIndex);
    }
    if (js.isLeftDebounce()) {
      setGameState(GameState::SaveSettingsMenu);
    }
  }
}
