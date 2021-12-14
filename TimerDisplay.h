#pragma once

#include "Timer.h"

class TimerDisplay {
  Timer lastUpdateTime = 0;
  Timer timeLeft = 0;
  bool paused = false;

  public :
    void pause();
    void unpause();
    bool isFinished() const;
    void setTime(Timer newTime);
    void increaseTime(Timer increaseTime);

    Timer getTimeLeft() const;
    Timer getTimeLeftInSec() const;
    void update();

};

extern TimerDisplay timerDisplay;
