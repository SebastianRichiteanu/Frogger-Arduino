#pragma once

class Score {
  unsigned current = 0;

  public:
    void setCurrentScore(unsigned newScore);
    unsigned getCurrentScore() const;

    void reset();

    bool isHighScore() const;
    void updateHighScoreList();

    void addPointsForTimeLeft(byte timeLeft);
    void addPointsForLivesLeft(byte livesLeft);
    void addPointsForCollectedObj(byte collectedObj);
};

extern Score score;
