#pragma once

#include "SavedData.h"

const byte playerNameLen = 3;

enum class Difficulty : byte { Easy, Medium, Hard} ;
const byte difficultyNum = 3;

Difficulty getCurrentDif();
const char* getCurrentDifAsString();
void setCurrentDif(Difficulty diff);

void increaseDif();
void decreaseDif();

// lcd

const byte maxLcdContrast = 100;
const byte maxLcdBrightness = 100;

byte getCurrentLcdContrast();
byte getCurrentLcdBrightness();

void increaseLcdContrast();
void decreaseLcdContrast();

void increaseLcdBrightness();
void decreaseLcdBrightness();

// matrix

const byte maxMatrixBrightness = 100;

byte getCurrentMatrixBright();
void increaseMatrixBright();
void decreaseMatrixBright();
