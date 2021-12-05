#include "Timer.h"

bool debounce(bool value, unsigned long& lastTime, unsigned long interval) {
  if (value && (updateTime > lastTime + interval)) {
    lastTime = updateTime;
    return true;
  }
  return false;
}

bool debounce(unsigned long& lastTime, unsigned long interval) {
  if (updateTime > lastTime + interval) {
    lastTime = updateTime;
    return true;
  }
  return false;
}
