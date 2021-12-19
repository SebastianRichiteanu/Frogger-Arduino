#pragma once

#include "Settings.h"

const byte maxHighScores = 5;

struct Highscore {
  unsigned score;
  char name[playerNameLen];
};

struct SavedData {
  char playerName[playerNameLen + 1];
  byte lcdBrightness;
  byte lcdContrast;
  byte matrixBrightness;
  bool musicState;
  bool soundState;
  Difficulty difficulty;
  Highscore highscores[maxHighScores];
}savedData;

void resetSavedData();
void loadSavedData();
void saveSavedData();
