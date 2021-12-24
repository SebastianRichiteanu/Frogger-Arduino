#include "SettingsMenuState.h"

#define nameIndex 0
#define difficultyIndex 1
#define lcdContrastIndex 2
#define lcdBrightnessIndex 3
#define matrixBrightnessIndex 4
#define musicStateIndex 5
#define gameSoundIndex 6
#define menuSoundIndex 7
#define resetEEPROMIndex 8

// constant for number of settings in the menu
const byte settingsNum = 9;

// blink constants
const int arrowBlinkDelay = 1000;
const int chrBlinkDelay = 500;

const char nameFieldString[] = "Name: ";

// called every time the player enters this menu
// makes a copy of the current settings
void SettingsMenuState::copySaveData() {
  strcpy(copySavedData.playerName, savedData.playerName);
  copySavedData.lcdBrightness = savedData.lcdBrightness;
  copySavedData.lcdContrast = savedData.lcdContrast;
  copySavedData.matrixBrightness = savedData.matrixBrightness;
  copySavedData.difficulty = savedData.difficulty;
  copySavedData.musicState = savedData.musicState;
  copySavedData.gameSoundState = savedData.gameSoundState;
}

// sets the arrow position to a blank space
void SettingsMenuState::clearSelArrow() {
  lcd.setCursor(0, 0);
  lcd.print(" ");
}

// sets the arrow position to an arrow
void SettingsMenuState::printSelArrow() {
  lcd.setCursor(0, 0);
  lcd.print(">");
}

// prints the "Name: " and player name
void SettingsMenuState::printNameField() {
  lcd.print(nameFieldString);
  lcd.print(savedData.playerName);
}

// prints the difficulty field as a string
void SettingsMenuState::printDifficultyLevelField() {
  lcd.print(F("Diff: "));
  if (isEditing && currentIndex == difficultyIndex) {
    lcd.print(F("{"));
  }
  lcd.print(getCurrentDifAsString());
  if (isEditing && currentIndex == difficultyIndex) {
    lcd.print(F("}"));
  }
}

// prints the lcd contrast as a number
void SettingsMenuState::printLcdContrast() {
  lcd.print(F("Contrast: "));
  if (isEditing && currentIndex == lcdContrastIndex) {
    lcd.print(F("{"));
  }
  lcd.print(savedData.lcdContrast);
  if (isEditing && currentIndex == lcdContrastIndex) {
    lcd.print(F("}"));
  }
}

// prints the lcd brightness as a number
void SettingsMenuState::printLcdBrightness() {
  lcd.print(F("LCD Bright:"));
  if (isEditing && currentIndex == lcdBrightnessIndex) {
    lcd.print(F("{"));
  } else {
    lcd.print(F(" "));
  }
  lcd.print(savedData.lcdBrightness);
  if (isEditing && currentIndex == lcdBrightnessIndex) {
    lcd.print(F("}"));
  }
}

// prints the matrix brightness as a number
void SettingsMenuState::printMatrixBright() {
  lcd.print(F("Mat Bright:"));
  if (isEditing && currentIndex == matrixBrightnessIndex) {
    lcd.print(F("{"));
  } else {
    lcd.print(F(" "));
  }
  lcd.print(savedData.matrixBrightness);
  if (isEditing && currentIndex == matrixBrightnessIndex) {
    lcd.print(F("}"));
  }
}

// prints the music state (ON/OFF)
void SettingsMenuState::printMusicState() {
  lcd.print(F("Music:"));
  if (isEditing && currentIndex == musicStateIndex) {
    lcd.print(F("{"));
  } else {
    lcd.print(F(" "));
  }
  if (savedData.musicState) {
    lcd.print(F("ON"));
  } else {
    lcd.print(F("OFF"));
  }
  if (isEditing && currentIndex == musicStateIndex) {
    lcd.print(F("}"));
  }
}

// prints the game sound state (ON/OFF)
void SettingsMenuState::printGameSoundState() {
  lcd.print(F("GameSound:"));
  if (isEditing && currentIndex == gameSoundIndex) {
    lcd.print(F("{"));
  } else {
    lcd.print(F(" "));
  }
  if (savedData.gameSoundState) {
    lcd.print(F("ON"));
  } else {
    lcd.print(F("OFF"));
  }
  if (isEditing && currentIndex == gameSoundIndex) {
    lcd.print(F("}"));
  }
}

//prints the menu sound state (ON/OFF)
void SettingsMenuState::printMenuSoundState() {
  lcd.print(F("MenuSound:"));
  if (isEditing && currentIndex == menuSoundIndex) {
    lcd.print(F("{"));
  } else {
    lcd.print(F(" "));
  }
  if (savedData.menuSoundState) {
    lcd.print(F("ON"));
  } else {
    lcd.print(F("OFF"));
  }
  if (isEditing && currentIndex == menuSoundIndex) {
    lcd.print(F("}"));
  }
}

// prints the reset EEPROM setting
void SettingsMenuState::printResetEEPROM() {
  if (isEditing && currentIndex == resetEEPROMIndex) {
    lcd.print(F("{"));
  }
  lcd.print(F("Reset EEPROM"));
  if (isEditing && currentIndex == resetEEPROMIndex) {
    lcd.print(F("}"));
  }
}

// prints the field by index
void SettingsMenuState::printField(byte index) {
  if (index == nameIndex) {
    printNameField();
  } else if (index == difficultyIndex) {
    printDifficultyLevelField();
  } else if (index == lcdContrastIndex) {
    printLcdContrast();
  } else if (index == lcdBrightnessIndex) {
    printLcdBrightness();
  } else if (index == matrixBrightnessIndex) {
    printMatrixBright();
  } else if (index == musicStateIndex) {
    printMusicState();
  } else if (index == gameSoundIndex) {
    printGameSoundState();
  } else if (index == menuSoundIndex) {
    printMenuSoundState();
  } else if (index == resetEEPROMIndex) {
    printResetEEPROM();
  }
}

// clears the lcd and then prints the index field
// and the index + 1 field (on the next row) if there is any
void SettingsMenuState::printFields(byte index) {
  lcd.clear();
  lcd.setCursor(1, 0);
  printField(index);

  if (index < settingsNum - 1) {
    lcd.setCursor(0, 1);
    lcd.write((byte)0);
    printField(index + 1);
  }
}

// change the name char to the previous char
void SettingsMenuState::changeToPrevChar() {
  char& ch = savedData.playerName[chrIndex];
  if (ch == 'a') {
    ch = 'z';
  } else {
    ch = 'a' + (ch - 'a' + 25) % 26;
  }
}

// change the name char to the next char
void SettingsMenuState::changeToNextChar() {
  char& ch = savedData.playerName[chrIndex];
  if (ch == 'z') {
    ch = 'a';
  } else {
    ch = 'a' + (ch - 'a' + 1) % 26;
  }
}

// on begin, copy the saved data, reset the index 
// and print the fields along with the hammer effect
void SettingsMenuState::onBegin() {
  copySaveData();
  currentIndex = nameIndex;
  isEditing = false;
  printFields(currentIndex);
  matrix.hammerEffect();
}

// the update function checks the js button to select a row
// blinks the arrow
// change the corresponding values according to the input
// and change the selected index position accroding to the input
// also goes back to the menu once the player inputs left
void SettingsMenuState::update() {
  if (js.isPressedDebounce()) {
    isEditing = !isEditing;
    if (currentIndex == nameIndex) {
      chrIndex = nameIndex;
    }
    printFields(currentIndex);
    buzzer.playMenuTone();
  }

  if (isEditing) {
    
    if (updateTime % arrowBlinkDelay > arrowBlinkDelay / 2) {
      printSelArrow();
    } else {
      clearSelArrow();
    }
  
    if (currentIndex == nameIndex) {
      if (js.isLeftDebounce()) {
        buzzer.playMenuTone();
        chrIndex = (chrIndex + playerNameLen - 1) % playerNameLen;
        printFields(currentIndex);
      }
      if (js.isRightDebounce()) {
        buzzer.playMenuTone();
        chrIndex = (chrIndex + 1) % playerNameLen;
        printFields(currentIndex);
      }
      if (js.isUpDebounce()) {
        buzzer.playMenuTone();
        changeToPrevChar();
      }
      if (js.isDownDebounce()) {
        buzzer.playMenuTone();
        changeToNextChar();
      }
      lcd.setCursor(sizeof(nameFieldString) + chrIndex, 0);
      if (updateTime % chrBlinkDelay > chrBlinkDelay / 2) {
        lcd.print(' ');
      } else {
        lcd.print(savedData.playerName[chrIndex]);
      } 
    } else if (currentIndex == difficultyIndex) {
      if (js.isLeftDebounce()) {
        buzzer.playMenuTone();
        decreaseDifficulty();
        printFields(currentIndex);
      } 
      if (js.isRightDebounce()) {
        buzzer.playMenuTone();
        increaseDifficulty();
        printFields(currentIndex);
      }
    } else if (currentIndex == lcdContrastIndex) {
      if (js.isLeftDebounce()) {
        buzzer.playMenuTone();
        decreaseLcdContrast();
        printFields(currentIndex);
        updateHardware();
      }
      if (js.isRightDebounce()) {
        buzzer.playMenuTone();
        increaseLcdContrast();
        printFields(currentIndex);
        updateHardware();
      }
    } else if (currentIndex == lcdBrightnessIndex) {
      if (js.isLeftDebounce()) {
        buzzer.playMenuTone();
        decreaseLcdBrightness();
        printFields(currentIndex);
        updateHardware();
      }
      if (js.isRightDebounce()) {
        buzzer.playMenuTone();
        increaseLcdBrightness();
        printFields(currentIndex);
        updateHardware();
      }
    } else if (currentIndex == matrixBrightnessIndex) {
      if (js.isLeftDebounce()) {
        buzzer.playMenuTone();
        decreaseMatrixBright();
        printFields(currentIndex);
        updateHardware();
      }
      if (js.isRightDebounce()) {
        buzzer.playMenuTone();
        increaseMatrixBright();
        printFields(currentIndex);
        updateHardware();
      }
    } else if (currentIndex == musicStateIndex) {
      if (js.isLeftDebounce() || js.isRightDebounce()) {
        buzzer.playMenuTone();
        changeMusicState();
        printFields(currentIndex);
      } 
    } else if (currentIndex == gameSoundIndex) {
      if (js.isLeftDebounce() || js.isRightDebounce()) {
        buzzer.playMenuTone();
        changeGameSoundState();
        printFields(currentIndex);
      }
    } else if (currentIndex == menuSoundIndex) {
      if (js.isLeftDebounce() || js.isRightDebounce()) {
        buzzer.playMenuTone();
        changeMenuSoundState();
        printFields(currentIndex);
      }
    } else if (currentIndex == resetEEPROMIndex) {
      if (js.isLeftDebounce() || js.isRightDebounce()) {
        buzzer.playMenuTone();
        resetSavedData();
        printFields(currentIndex);
      }
    }
  } else {
    printSelArrow();
    if (js.isDownDebounce()) {
      currentIndex = (currentIndex + settingsNum - 1) % settingsNum;
      printFields(currentIndex);
      buzzer.playMenuTone();
    } 
    if (js.isUpDebounce()) {
      currentIndex = (currentIndex + 1) % settingsNum;
      printFields(currentIndex);
      buzzer.playMenuTone();
    }
    if (js.isLeftDebounce()) {
      buzzer.playMenuTone();
      setGameState(GameState::SaveSettingsMenu);
    }
  }
}
