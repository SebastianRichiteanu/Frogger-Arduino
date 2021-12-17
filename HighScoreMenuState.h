#pragma once

class HighScoreMenuState : public State {
  byte topScoreIndex;

  void printScore(byte index);
  void printScores();

  public:
    void onBegin() override;
    void update() override;
};
