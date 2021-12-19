#pragma once

using Timer = unsigned long;

extern unsigned long updateTime;

bool debounce(bool value, unsigned long& lastTime, unsigned long interval = 500);
bool debounce(unsigned long& lastTime, unsigned long interval = 200);
