#include "Highscore.h"
#include <EEPROM.h>

void resetHighscores() {
  for (byte i = 0; i < maxHighScores; ++i) {
    highscores[i].score = 0;
    strcpy(highscores[i].name, "zby");
  }
  saveHighscores();
}

void loadHighscores() {
  byte* data = (byte*)&highscores;
  for (byte i = 0; i < sizeof(highscores); ++i) {
    data[i] = EEPROM.read(i);
  }
}

void saveHighscores() {
  const byte* data = (const byte*)&highscores;
  for (byte i = 0; i < sizeof(highscores); ++i) {
    EEPROM.write(i, data[i]);
  }
}
