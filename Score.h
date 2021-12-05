#pragma once

class Score {
  unsigned current = 0;

  public:
    void setCurrentScore(unsigned newScore);
    unsigned getCurrentScore() const;

    void reset();

    bool isHighScore() const;
    void updateHighScoreList();
};

extern Score score;
