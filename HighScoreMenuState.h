#pragma once

#include "SavedData.h"
#include "State.h"

class HighScoreMenuState : public State {
  byte topScoreIndex;

  void printScore(byte index);

  void printScores();

  public:
    void onBegin() override;
    void update() override;
    // void onEnd() override;
};
