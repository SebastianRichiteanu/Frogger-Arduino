#include "SavedData.h"
#include <EEPROM.h>

// clears the saved data struct and saves the empty struct to the EEPROM
void resetSavedData() {
  savedData = {};
  saveSavedData();
}

// load every byte of saved data from the EEPROM
void loadSavedData() {
  byte* data = (byte*)&savedData;
  for (byte i = 0; i < sizeof(savedData); ++i) {
    data[i] = EEPROM.read(i);
  }
}

// save every byte of saved data to the EEPROM
void saveSavedData() {
  const byte* data = (const byte*)&savedData;
  for (byte i = 0; i < sizeof(savedData); ++i) {
    EEPROM.write(i, data[i]);
  }
}
