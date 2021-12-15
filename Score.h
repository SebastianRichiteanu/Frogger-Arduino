#pragma once

class Score {
  unsigned current = 0;

  public:
    void setCurrentScore(unsigned newScore);
    unsigned getCurrentScore() const;

    void reset();

    bool isHighScore() const;
    void updateHighScoreList();

    void addPointsForLevel(byte level);
    void addPointsForTimeLeft(byte timeLeft);
    void addPointsForLivesLeft(byte livesLeft);
};

extern Score score;
