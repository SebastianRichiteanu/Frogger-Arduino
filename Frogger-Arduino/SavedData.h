#pragma once

#include "Settings.h"

const byte maxHighScores = 5;

struct Highscore {
  unsigned score;
  char name[playerNameLen];
};

struct SavedData {
  char playerName[playerNameLen + 1];
  byte lcdBrightness, lcdContrast, matrixBrightness;
  bool musicState, gameSoundState, menuSoundState;
  Difficulty difficulty;
  Highscore highscores[maxHighScores];
}savedData;

void resetSavedData();
void loadSavedData();
void saveSavedData();
