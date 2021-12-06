#include "SavedData.h"
#include <EEPROM.h>

void resetSavedData() {
  savedData = {};
  saveSavedData();
}

void loadSavedData() {
  byte* data = (byte*)&savedData;
  for (byte i = 0; i < sizeof(savedData); ++i) {
    data[i] = EEPROM.read(i);
  }
}

void saveSavedData() {
  const byte* data = (const byte*)&savedData;
  for (byte i = 0; i < sizeof(savedData); ++i) {
    EEPROM.write(i, data[i]);
  }
}
