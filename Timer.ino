#include "Timer.h"

// debounce the last time to the interval if the value is true
bool debounce(bool value, Timer& lastTime, Timer interval) {
  if (value && (updateTime > lastTime + interval)) {
    lastTime = updateTime;
    return true;
  }
  return false;
}

// debounce the last time to the interval
bool debounce(Timer& lastTime, Timer interval) {
  if (updateTime > lastTime + interval) {
    lastTime = updateTime;
    return true;
  }
  return false;
}
