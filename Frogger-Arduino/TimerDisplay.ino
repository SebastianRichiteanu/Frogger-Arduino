#include "TimerDisplay.h"

// timer display instance
TimerDisplay timerDisplay;

// pause the timer and update the time
void TimerDisplay::pause() {
  paused = true;
  lastUpdateTime = updateTime;
}

// unpause the timer and update the time
void TimerDisplay::unpause() {
  paused = false;
  lastUpdateTime = updateTime;
}

// check if ther is no time left
bool TimerDisplay::isFinished() const { return timeLeft == 0; }

// set the time to a new one
void TimerDisplay::setTime(Timer newTime) { 
  timeLeft = newTime;
  elapsedTime = newTime;
}

// increase the time by increaseTime (in milliseconds)
void TimerDisplay::increaseTime(Timer increaseTime) { 
  timeLeft += increaseTime;
  elapsedTime += increaseTime;
}

Timer TimerDisplay::getElapsedTimeInSec() const { return elapsedTime / 1000; }

Timer TimerDisplay::getTimeLeft() const { return timeLeft; }

Timer TimerDisplay::getTimeLeftInSec() const { return timeLeft / 1000; }

// if the game is not paused
// update the timer
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
