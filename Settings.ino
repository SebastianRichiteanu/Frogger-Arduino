#include "Settings.h"

Difficulty getCurrentDif() { return savedData.difficulty; }

void setCurrentDif(Difficulty diff) { 
  savedData.difficulty = diff;
}

const char* getCurrentDifAsString() {
  switch(getCurrentDif()) {
    case Difficulty::Easy:
      return "Easy";
    case Difficulty::Medium:
      return "Medium";
    case Difficulty::Hard:
      return "Hard";
  }
}

const char getCurrentDifAsChar() {
  switch(getCurrentDif()) {
    case Difficulty::Easy:
      return 'E';
    case Difficulty::Medium:
      return 'M';
    case Difficulty::Hard:
      return 'H';
  }
}

void increaseDifficulty() {
  byte diff = (byte)getCurrentDif();
  diff = (diff + 1) % difficultyNum;
  savedData.difficulty = (Difficulty)diff;
}

void decreaseDifficulty() {
  byte diff = (byte)getCurrentDif();
  diff = (diff + difficultyNum - 1) % difficultyNum;
  savedData.difficulty = (Difficulty)diff;
}

const Timer getStartingTimeByDif() {
  switch(getCurrentDif()) {
    case Difficulty::Easy:
      return 100000;
    case Difficulty::Medium:
      return 75000;
    case Difficulty::Hard:
      return 50000;
  }
}

const Timer getStartingTimeByDifAsSec() {
  return getStartingTimeByDif() / 1000;
}

const byte getStartingLivesByDif() {
  switch(getCurrentDif()) {
    case Difficulty::Easy:
      return 4;
    case Difficulty::Medium:
      return 3;
    case Difficulty::Hard:
      return 2;
  }
}

const byte getStartingJumpsByDif() {
  switch(getCurrentDif()) {
    case Difficulty::Easy:
      return 3;
    case Difficulty::Medium:
      return 2;
    case Difficulty::Hard:
      return 1;
  }
}

const byte getVehicleSpeedByDif() {
  switch(getCurrentDif()) {
    case Difficulty::Easy:
      return 0;
    case Difficulty::Medium:
      return 2;
    case Difficulty::Hard:
      return 4;
  }
}

const byte getNumberOfWallsByDif() {
  switch(getCurrentDif()) {
    case Difficulty::Easy:
      return 2;
    case Difficulty::Medium:
      return 3;
    case Difficulty::Hard:
      return 4;
  }
}

const byte getLengthOfWallsByDif() {
  switch(getCurrentDif()) {
    case Difficulty::Easy:
      return random(2, 4);
    case Difficulty::Medium:
      return random(2, 5);
    case Difficulty::Hard:
      return random(3, 5);
  }
}

const float getLengthOfWallsByLvl() {
  byte currentLvl = levelMap.getLevel();
  switch(getCurrentDif()) {
    case Difficulty::Easy:
      return 1 + currentLvl * 0.3;
    case Difficulty::Medium:
      return 1 + currentLvl * 0.25;
    case Difficulty::Hard:
      return 1 + currentLvl * 0.2;
  }
}

const byte getNumberOfBonusByDif() {
  switch(getCurrentDif()) {
    case Difficulty::Easy:
      return random(2, 4);
    case Difficulty::Medium:
      return random(1, 3);
    case Difficulty::Hard:
      return random(0, 2);
  }
}

const byte getScoreMultiplierByDif() {
  switch(getCurrentDif()) {
    case Difficulty::Easy:
      return 30;
    case Difficulty::Medium:
      return 40;
    case Difficulty::Hard:
      return 50;
  }
}

const float vehicleDelayByDif() {
  switch(getCurrentDif()) {
    case Difficulty::Easy:
      return 1;
    case Difficulty::Medium:
      return 0.9;
    case Difficulty::Hard:
      return 0.8;
  }
}
const float vehicleDelayByLevel() {
  byte currentLvl = levelMap.getLevel();
  switch(getCurrentDif()) {
    case Difficulty::Easy:
      return 1 - currentLvl * 0.01;
    case Difficulty::Medium:
      return 1 - currentLvl * 0.025;
    case Difficulty::Hard:
      return 1 - currentLvl * 0.05;
  }
}

const float vehicleLenByDif() {
  switch(getCurrentDif()) {
    case Difficulty::Easy:
      return 1;
    case Difficulty::Medium:
      return 1.1;
    case Difficulty::Hard:
      return 1.2;
  }
}

const float vehicleLenByLevel() {
  byte currentLvl = levelMap.getLevel();
  switch(getCurrentDif()) {
    case Difficulty::Easy:
      return 1 + currentLvl * 0.01;
    case Difficulty::Medium:
      return 1 + currentLvl * 0.025;
    case Difficulty::Hard:
      return 1 + currentLvl * 0.05;
  }
}


// lcd

byte getCurrentLcdContrast() { return savedData.lcdContrast; }
byte getCurrentLcdBrightness() { return savedData.lcdBrightness; }

void increaseLcdContrast() {
  byte contrast = getCurrentLcdContrast();
  contrast = (contrast + 5) % maxLcdContrast;
  savedData.lcdContrast = contrast;
}

void decreaseLcdContrast() {
  byte contrast = getCurrentLcdContrast();
  contrast = (contrast + maxLcdContrast - 5) % maxLcdContrast;
  savedData.lcdContrast = contrast;
}

void increaseLcdBrightness() {
  byte brightness = getCurrentLcdBrightness();
  brightness = (brightness + 5) % maxLcdBrightness;
  savedData.lcdBrightness = brightness;
}

void decreaseLcdBrightness() {
  byte brightness = getCurrentLcdBrightness();
  brightness = (brightness + maxLcdBrightness - 5) % maxLcdBrightness;
  savedData.lcdBrightness = brightness; 
}

void changeMusicState() { 
  savedData.musicState = !savedData.musicState;
}

// matrix

byte getCurrentMatrixBright() { return savedData.matrixBrightness; }

void increaseMatrixBright() {
  byte brightness = getCurrentMatrixBright();
  brightness = (brightness + 5) % maxMatrixBrightness;
  savedData.matrixBrightness = brightness;
}

void decreaseMatrixBright() {
  byte brightness = getCurrentMatrixBright();
  brightness = (brightness + maxMatrixBrightness - 5) % maxMatrixBrightness;
  savedData.matrixBrightness = brightness;
}
