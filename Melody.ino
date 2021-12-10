#include "Melody.h"
// https://github.com/robsoncouto/arduino-songs/blob/master/asabranca/asabranca.ino

const uint16_t PROGMEM jingleBellsFreq[] = {
  NOTE_E5, NOTE_E5, NOTE_E5,
  NOTE_E5, NOTE_E5, NOTE_E5,
  NOTE_E5, NOTE_G5, NOTE_C5, NOTE_D5,
  NOTE_E5,
  NOTE_F5, NOTE_F5, NOTE_F5, NOTE_F5,
  NOTE_F5, NOTE_E5, NOTE_E5, NOTE_E5, NOTE_E5,
  NOTE_E5, NOTE_D5, NOTE_D5, NOTE_E5,
  NOTE_D5, NOTE_G5,
};

const uint8_t PROGMEM jingleBellsDur[] = {
  8, 8, 4,
  8, 8, 4,
  8, 8, 8, 8,
  2,
  8, 8, 8, 8,
  8, 8, 8, 16, 16,
  8, 8, 8, 8,
  4, 4,
};

const static Timer jingleBellsBaseDuration = 2000;

Melody jingleBellsMelody{jingleBellsFreq, jingleBellsDur, sizeof(jingleBellsDur) / sizeof(jingleBellsDur[0]), jingleBellsBaseDuration};

const uint16_t PROGMEM testFreq[] = {
  NOTE_FS5, NOTE_FS5, NOTE_D5, NOTE_B4, NOTE_B4, NOTE_E5, 
  NOTE_E5, NOTE_E5, NOTE_GS5, NOTE_GS5, NOTE_A5, NOTE_B5, 
  NOTE_A5, NOTE_A5, NOTE_A5, NOTE_E5, NOTE_D5, NOTE_FS5, 
  NOTE_FS5, NOTE_FS5, NOTE_E5, NOTE_E5, NOTE_FS5, NOTE_E5
};

const uint8_t PROGMEM testDur[] = {
  8, 8, 8, 4, 4, 4, 
  4, 5, 8, 8, 8, 8, 
  8, 8, 8, 4, 4, 4, 
  4, 5, 8, 8, 8, 8
};

const static Timer testBaseDuration = 1500;

Melody testMelody{testFreq, testDur, sizeof(testDur) / sizeof(testDur[0]), testBaseDuration};
