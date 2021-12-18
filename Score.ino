#include "Score.h"
#include "Utility.h"

// the score instance
Score score;

void Score::setCurrentScore(unsigned newScore) { current = newScore; }

unsigned Score::getCurrentScore() const { return current; }

void Score::reset() { current = 0; }

// get the score of the last player in the top 
// and check if the new score is better than it
bool Score::isHighScore() const {
  const Highscore& lastPlayer = savedData.highscores[maxHighScores - 1];
  return current >= lastPlayer.score;
}

// switch the last player stats in the top with the new ones
// and reorder the highscores list
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

// add points to the current score for each level
void Score::addPointsForLevel(byte level) {
  current += level * getScoreMultiplierByDif();
}

// add points to the current score for each life left
void Score::addPointsForLivesLeft(byte livesLeft) {
  current += livesLeft * getScoreMultiplierByDif();
}

// add points to the current score for the time left
void Score::addPointsForTimeLeft(byte timeLeft) {
  current += timeLeft * getScoreMultiplierByDif() / 10;
}
