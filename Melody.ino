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

const uint16_t PROGMEM takeOnMeFreq[] = {
  NOTE_FS5, NOTE_FS5, NOTE_D5, NOTE_B4, NOTE_B4, NOTE_E5, 
  NOTE_E5, NOTE_E5, NOTE_GS5, NOTE_GS5, NOTE_A5, NOTE_B5, 
  NOTE_A5, NOTE_A5, NOTE_A5, NOTE_E5, NOTE_D5, NOTE_FS5, 
  NOTE_FS5, NOTE_FS5, NOTE_E5, NOTE_E5, NOTE_FS5, NOTE_E5
};

const uint8_t PROGMEM takeOnMeDur[] = {
  8, 8, 8, 4, 4, 4, 
  4, 5, 8, 8, 8, 8, 
  8, 8, 8, 4, 4, 4, 
  4, 5, 8, 8, 8, 8
};

const static Timer takeOnMeBaseDuration = 1500;

Melody takeOnMeMelody{takeOnMeFreq, takeOnMeDur, sizeof(takeOnMeDur) / sizeof(takeOnMeDur[0]), takeOnMeBaseDuration};

const uint16_t PROGMEM tetrisFreq[] = {
    NOTE_E5,  NOTE_E3, NOTE_B4,  NOTE_C5, NOTE_D5,  NOTE_E5, NOTE_D5,  NOTE_C5,
    NOTE_B4,  NOTE_A4, NOTE_A3,  NOTE_A4, NOTE_C5,  NOTE_E5, NOTE_A3,  NOTE_D5,
    NOTE_C5,  NOTE_B4, NOTE_E4,  NOTE_G4, NOTE_C5,  NOTE_D5, NOTE_E3,  NOTE_E5,
    NOTE_E3,  NOTE_C5, NOTE_A3,  NOTE_A4, NOTE_A3,  NOTE_A4, NOTE_A3,  NOTE_B2,
    NOTE_C3,  NOTE_D3, NOTE_D5,  NOTE_F5, NOTE_A5,  NOTE_C5, NOTE_C5,  NOTE_G5,
    NOTE_F5,  NOTE_E5, NOTE_C3,  REST,    NOTE_C5,  NOTE_E5, NOTE_A4,  NOTE_G4,
    NOTE_D5,  NOTE_C5, NOTE_B4,  NOTE_E4, NOTE_B4,  NOTE_C5, NOTE_D5,  NOTE_G4,
    NOTE_E5,  NOTE_G4, NOTE_C5,  NOTE_E4, NOTE_A4,  NOTE_E3, NOTE_A4,  REST,
    NOTE_E5,  NOTE_E3, NOTE_B4,  NOTE_C5, NOTE_D5,  NOTE_E5, NOTE_D5,  NOTE_C5,
    NOTE_B4,  NOTE_A4, NOTE_A3,  NOTE_A4, NOTE_C5,  NOTE_E5, NOTE_A3,  NOTE_D5,
    NOTE_C5,  NOTE_B4, NOTE_E4,  NOTE_G4, NOTE_C5,  NOTE_D5, NOTE_E3,  NOTE_E5,
    NOTE_E3,  NOTE_C5, NOTE_A3,  NOTE_A4, NOTE_A3,  NOTE_A4, NOTE_A3,  NOTE_B2,
    NOTE_C3,  NOTE_D3, NOTE_D5,  NOTE_F5, NOTE_A5,  NOTE_C5, NOTE_C5,  NOTE_G5,
    NOTE_F5,  NOTE_E5, NOTE_C3,  REST,    NOTE_C5,  NOTE_E5, NOTE_A4,  NOTE_G4,
    NOTE_D5,  NOTE_C5, NOTE_B4,  NOTE_E4, NOTE_B4,  NOTE_C5, NOTE_D5,  NOTE_G4,
    NOTE_E5,  NOTE_G4, NOTE_C5,  NOTE_E4, NOTE_A4,  NOTE_E3, NOTE_A4,  REST,
    NOTE_E4,  NOTE_E3, NOTE_A2,  NOTE_E3, NOTE_C4,  NOTE_E3, NOTE_A2,  NOTE_E3,
    NOTE_D4,  NOTE_E3, NOTE_GS2, NOTE_E3, NOTE_B3,  NOTE_E3, NOTE_GS2, NOTE_E3,
    NOTE_C4,  NOTE_E3, NOTE_A2,  NOTE_E3, NOTE_A3,  NOTE_E3, NOTE_A2,  NOTE_E3,
    NOTE_GS3, NOTE_E3, NOTE_GS2, NOTE_E3, NOTE_B3,  NOTE_E3, NOTE_GS2, NOTE_E3,
    NOTE_E4,  NOTE_E3, NOTE_A2,  NOTE_E3, NOTE_C4,  NOTE_E3, NOTE_A2,  NOTE_E3,
    NOTE_D4,  NOTE_E3, NOTE_GS2, NOTE_E3, NOTE_B3,  NOTE_E3, NOTE_GS2, NOTE_E3,
    NOTE_C4,  NOTE_E3, NOTE_E4,  NOTE_E3, NOTE_A4,  NOTE_E3, NOTE_A2,  NOTE_E3,
    NOTE_GS4, NOTE_E3, NOTE_GS2, NOTE_E3, NOTE_GS2, NOTE_E3, NOTE_GS2, NOTE_E3,
    NOTE_E5,  NOTE_E3, NOTE_B4,  NOTE_C5, NOTE_D5,  NOTE_E5, NOTE_D5,  NOTE_C5,
    NOTE_B4,  NOTE_A4, NOTE_A3,  NOTE_A4, NOTE_C5,  NOTE_E5, NOTE_A3,  NOTE_D5,
    NOTE_C5,  NOTE_B4, NOTE_E4,  NOTE_G4, NOTE_C5,  NOTE_D5, NOTE_E3,  NOTE_E5,
    NOTE_E3,  NOTE_C5, NOTE_A3,  NOTE_A4, NOTE_A3,  NOTE_A4, NOTE_A3,  NOTE_B2,
    NOTE_C3,  NOTE_D3, NOTE_D5,  NOTE_F5, NOTE_A5,  NOTE_C5, NOTE_C5,  NOTE_G5,
    NOTE_F5,  NOTE_E5, NOTE_C3,  REST,    NOTE_C5,  NOTE_E5, NOTE_A4,  NOTE_G4,
    NOTE_D5,  NOTE_C5, NOTE_B4,  NOTE_E4, NOTE_B4,  NOTE_C5, NOTE_D5,  NOTE_G4,
    NOTE_E5,  NOTE_G4, NOTE_C5,  NOTE_E4, NOTE_A4,  NOTE_E3, NOTE_A4,  REST,
    NOTE_E5,  NOTE_E3, NOTE_B4,  NOTE_C5, NOTE_D5,  NOTE_E5, NOTE_D5,  NOTE_C5,
    NOTE_B4,  NOTE_A4, NOTE_A3,  NOTE_A4, NOTE_C5,  NOTE_E5, NOTE_A3,  NOTE_D5,
    NOTE_C5,  NOTE_B4, NOTE_E4,  NOTE_G4, NOTE_C5,  NOTE_D5, NOTE_E3,  NOTE_E5,
    NOTE_E3,  NOTE_C5, NOTE_A3,  NOTE_A4, NOTE_A3,  NOTE_A4, NOTE_A3,  NOTE_B2,
    NOTE_C3,  NOTE_D3, NOTE_D5,  NOTE_F5, NOTE_A5,  NOTE_C5, NOTE_C5,  NOTE_G5,
    NOTE_F5,  NOTE_E5, NOTE_C3,  REST,    NOTE_C5,  NOTE_E5, NOTE_A4,  NOTE_G4,
    NOTE_D5,  NOTE_C5, NOTE_B4,  NOTE_E4, NOTE_B4,  NOTE_C5, NOTE_D5,  NOTE_G4,
    NOTE_E5,  NOTE_G4, NOTE_C5,  NOTE_E4, NOTE_A4,  NOTE_E3, NOTE_A4,  REST,
    NOTE_E4,  NOTE_E3, NOTE_A2,  NOTE_E3, NOTE_C4,  NOTE_E3, NOTE_A2,  NOTE_E3,
    NOTE_D4,  NOTE_E3, NOTE_GS2, NOTE_E3, NOTE_B3,  NOTE_E3, NOTE_GS2, NOTE_E3,
    NOTE_C4,  NOTE_E3, NOTE_A2,  NOTE_E3, NOTE_A3,  NOTE_E3, NOTE_A2,  NOTE_E3,
    NOTE_GS3, NOTE_E3, NOTE_GS2, NOTE_E3, NOTE_B3,  NOTE_E3, NOTE_GS2, NOTE_E3,
    NOTE_E4,  NOTE_E3, NOTE_A2,  NOTE_E3, NOTE_C4,  NOTE_E3, NOTE_A2,  NOTE_E3,
    NOTE_D4,  NOTE_E3, NOTE_GS2, NOTE_E3, NOTE_B3,  NOTE_E3, NOTE_GS2, NOTE_E3,
    NOTE_C4,  NOTE_E3, NOTE_E4,  NOTE_E3, NOTE_A4,  NOTE_E3, NOTE_A2,  NOTE_E3,
    NOTE_GS4, NOTE_E3, NOTE_GS2, NOTE_E3, NOTE_GS2, NOTE_E3, NOTE_GS2, NOTE_E3,
};

const uint8_t PROGMEM tetrisDur[] = {
    8,  8, 8, 8, 8,  16, 16, 8,  8,  8,  8,  8, 8, 8, 8, 8, 8,  8,  8,  8,  8,
    8,  8, 8, 8, 8,  8,  8,  8,  8,  8,  8,  8, 8, 4, 8, 8, 16, 16, 8,  8,  8,
    8,  8, 8, 8, 16, 16, 8,  8,  8,  8,  8,  8, 8, 8, 8, 8, 8,  8,  8,  8,  4,
    4,  8, 8, 8, 8,  8,  16, 16, 8,  8,  8,  8, 8, 8, 8, 8, 8,  8,  8,  8,  8,
    8,  8, 8, 8, 8,  8,  8,  8,  8,  8,  8,  8, 8, 8, 4, 8, 8,  16, 16, 8,  8,
    8,  8, 8, 8, 8,  16, 16, 8,  8,  8,  8,  8, 8, 8, 8, 8, 8,  8,  8,  8,  8,
    4,  4, 8, 8, 8,  8,  8,  8,  8,  8,  8,  8, 8, 8, 8, 8, 8,  8,  8,  8,  8,
    8,  8, 8, 8, 8,  8,  8,  8,  8,  8,  8,  8, 8, 8, 8, 8, 8,  8,  8,  8,  8,
    8,  8, 8, 8, 8,  8,  8,  8,  8,  8,  8,  8, 8, 8, 8, 8, 8,  8,  8,  8,  8,
    8,  8, 8, 8, 8,  8,  8,  8,  16, 16, 8,  8, 8, 8, 8, 8, 8,  8,  8,  8,  8,
    8,  8, 8, 8, 8,  8,  8,  8,  8,  8,  8,  8, 8, 8, 8, 8, 4,  8,  8,  16, 16,
    8,  8, 8, 8, 8,  8,  8,  16, 16, 8,  8,  8, 8, 8, 8, 8, 8,  8,  8,  8,  8,
    8,  8, 4, 4, 8,  8,  8,  8,  8,  16, 16, 8, 8, 8, 8, 8, 8,  8,  8,  8,  8,
    8,  8, 8, 8, 8,  8,  8,  8,  8,  8,  8,  8, 8, 8, 8, 8, 8,  4,  8,  8,  16,
    16, 8, 8, 8, 8,  8,  8,  8,  16, 16, 8,  8, 8, 8, 8, 8, 8,  8,  8,  8,  8,
    8,  8, 8, 4, 4,  8,  8,  8,  8,  8,  8,  8, 8, 8, 8, 8, 8,  8,  8,  8,  8,
    8,  8, 8, 8, 8,  8,  8,  8,  8,  8,  8,  8, 8, 8, 8, 8, 8,  8,  8,  8,  8,
    8,  8, 8, 8, 8,  8,  8,  8,  8,  8,  8,  8, 8, 8, 8, 8, 8,  8,  8,  8,  8,
    8,  8, 8, 8, 8,  8,
};

static const int tetrisNoteCount = sizeof(tetrisDur) / sizeof(tetrisDur[0]);
const static Timer tetrisBaseDuration = 1750;

Melody tetrisMelody{tetrisFreq, tetrisDur, tetrisNoteCount, tetrisBaseDuration};
