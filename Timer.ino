#include "Timer.h"

bool debounce(bool value, Timer& lastTime, Timer interval) {
  if (value && (updateTime > lastTime + interval)) {
    lastTime = updateTime;
    return true;
  }
  return false;
}

bool debounce(Timer& lastTime, Timer interval) {
  if (updateTime > lastTime + interval) {
    lastTime = updateTime;
    return true;
  }
  return false;
}
