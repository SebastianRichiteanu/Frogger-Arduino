#pragma once

#include "Score.h"

class GameOverState : public State {
  Timer lastTime;
  bool printingScore, printingHighscore, printingCongrats;

  void printCongrats();
  void printScore();
  void printHighscore();
  void printReturnToMenu();

  public:
    void onBegin() override;
    void onEnd() override;
    void update() override;
};
