#pragma once
#include "Pitches.h"

struct Melody {
  const uint16_t* frequencies;
  const uint8_t* durations;
  const int noteCount;
  const Timer baseDuration;
};

extern Melody jingleBellsMelody;
extern Melody testMelody;
