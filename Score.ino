#include "Score.h"
#include "Utility.h"

Score score;

void Score::setCurrentScore(unsigned newScore) { current = newScore; }

unsigned Score::getCurrentScore() const { return current; }

void Score::reset() { current = 0; }

bool Score::isHighScore() const {
  const Highscore& lastPlayer = savedData.highscores[maxHighScores - 1];
  return current >= lastPlayer.score;
}

void Score::updateHighScoreList() {
  Highscore& lastPlayer = savedData.highscores[maxHighScores - 1];


  strncpy(lastPlayer.name, savedData.playerName, playerNameLen);
  strncpy(lastPlayer.name + playerNameLen, "\0", 1);
  lastPlayer.score = current;

  for (int i = maxHighScores - 2; i >= 0; --i) {
    if (savedData.highscores[i].score < savedData.highscores[i + 1].score) {
      swap(savedData.highscores[i], savedData.highscores[i + 1]);
    }
  }
  saveSavedData();
}

void Score::addPointsForLevel(byte level) {
  current += level * getScoreMultiplierByDif();
}

void Score::addPointsForLivesLeft(byte livesLeft) {
  current += livesLeft * getScoreMultiplierByDif();
}

void Score::addPointsForTimeLeft(byte timeLeft) {
  current += timeLeft * getScoreMultiplierByDif() / 10;
}
