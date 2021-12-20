#include "Settings.h"

Difficulty getCurrentDif() { return savedData.difficulty; }

// returns a char for each difficulty (for lcd output purposes)
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

// returns a string for each difficulty (for lcd output purposes)
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

void setCurrentDif(Difficulty diff) { 
  savedData.difficulty = diff;
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

// returns the starting time corresponding to the selected difficulty
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

// returns the starting number of lives corresponding to the selected difficulty
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

// returns the starting number of jumps corresponding to the selected difficulty
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

// returns the number of walls corresponding to the selected difficulty
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

// returns the length of walls corresponding to the selected difficulty
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

// returns the walls length multiplier corresponding to the selected difficulty
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

// returns the starting number of bonus points corresponding to the selected difficulty
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

// returns the score multiplier by difficulty
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

// returns the vehicle delay multiplier by difficulty
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

// returns the vehicle delay multiplier by level
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

// returns the vehicle length multiplier by difficulty
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

// returns the vehicle length multiplier by level
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

void changeGameSoundState() {
  savedData.gameSoundState = !savedData.gameSoundState;
}

void changeMenuSoundState() {
  savedData.menuSoundState = !savedData.menuSoundState;
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
