#include "Settings.h"

#include "SavedData.h"
#include "Timer.h"

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
  //savedData.lcdContrast = contrast;
  savedData.lcdContrast = 90;
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
