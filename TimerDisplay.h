#pragma once

class TimerDisplay {
  Timer lastUpdateTime = 0,
        timeLeft = 0,
        elapsedTime = 0;
  bool paused = false;

  public :
    void pause();
    void unpause();
    bool isFinished() const;
    void setTime(Timer newTime);
    void increaseTime(Timer increaseTime);
    Timer getElapsedTimeInSec() const;
    Timer getTimeLeft() const;
    Timer getTimeLeftInSec() const;
    void update();

};

extern TimerDisplay timerDisplay;
