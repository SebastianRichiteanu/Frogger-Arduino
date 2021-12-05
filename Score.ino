#include "Score.h"
#include "Highscore.h"
#include "Utility.h"

Score score;

void Score::setCurrentScore(unsigned newScore) { current = newScore; }
unsigned Score::getCurrentScore() const { return current; }
void Score::reset() { current = 0; }

bool Score::isHighScore() const {
  const Highscore& lastPlayer = highscores[maxHighScores - 1];
  return current >= lastPlayer.score;
}

void Score::updateHighScoreList() {
  Highscore& lastPlayer = highscores[maxHighScores - 1];


  char playerName[4] = "zby";
  strncpy(lastPlayer.name, playerName, playerNameLen);
  lastPlayer.score = current;

  for (int i = maxHighScores - 2; i >= 0; --i) {
    if (highscores[i].score < highscores[i + 1].score) {
      swap(highscores[i], highscores[i + 1]);
    }
  }
  saveHighscores();
}
