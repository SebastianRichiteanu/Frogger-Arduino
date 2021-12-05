#pragma once

// #include "Settings.h"

const byte maxHighScores = 5;
const byte playerNameLen = 4;

struct Highscore {
  unsigned score;
  char name[playerNameLen];
}highscores[maxHighScores];

void resetHighscores();
void loadHighscores();
void saveHighscores();
