#include "TimerDisplay.h"

#include "Hardware.h"
#include "Settings.h"

TimerDisplay timerDisplay;

void TimerDisplay::pause() {
  paused = true;
  lastUpdateTime = updateTime;
}

void TimerDisplay::unpause() {
  paused = false;
  lastUpdateTime = updateTime;
}

bool TimerDisplay::isFinished() const { return timeLeft == 0; }

Timer TimerDisplay::getTimeLeft() const { return timeLeft; }

Timer TimerDisplay::getTimeLeftInSec() const { return timeLeft / 1000; }

void TimerDisplay::setTime(Timer newTime) { timeLeft = newTime; }

void TimerDisplay::update() {
  if (!paused) {
    Timer timeDif = updateTime - lastUpdateTime;
    if (timeLeft > timeDif) {
      timeLeft -= timeDif;
    } else {
      timeLeft = 0;
    }
  }
  lastUpdateTime = updateTime;
}
