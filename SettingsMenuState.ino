#include "SettingsMenuState.h"

// #include "Settings.h"

const byte settingsNum = 5;

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
  lcd.print("Level: ");
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

void SettingsMenuState::onBegin() {
  currentIndex = 0;
  isEditing = false;
  printFields(currentIndex);
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
      }
      if (js.isRightDebounce()) {
        increaseLcdContrast();
        printFields(currentIndex);
      }
    } else if (currentIndex == 3) {
      if (js.isLeftDebounce()) {
        decreaseLcdBrightness();
        printFields(currentIndex);
      }
      if (js.isRightDebounce()) {
        increaseLcdBrightness();
        printFields(currentIndex);
      }
    } else if (currentIndex == 4) {
      if (js.isLeftDebounce()) {
        decreaseMatrixBright();
        printFields(currentIndex);
      }
      if (js.isRightDebounce()) {
        increaseMatrixBright();
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
      
      updateHardware(); // are you sure?
      saveSavedData();
      setGameState(GameState::StartMenu);
    }
  }
}
