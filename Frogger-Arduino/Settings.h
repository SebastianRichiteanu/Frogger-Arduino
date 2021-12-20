#pragma once

const byte playerNameLen = 3;
const byte difficultyNum = 3;

enum class Difficulty : byte { Easy, Medium, Hard} ;

Difficulty getCurrentDif();
const char getCurrentDifAsChar();
const char* getCurrentDifAsString();
void setCurrentDif(Difficulty diff);

void increaseDifficulty();
void decreaseDifficulty();

const Timer getStartingTimeByDif();
const Timer getStartingTimeByDifAsSec();
const byte getStartingLivesByDif();
const byte getStartingJumpsByDif();
const byte getNumberOfWallsByDif();
const byte getLengthOfWallsByDif();
const float getLengthOfWallsByLvl();
const byte getNumberOfBonusByDif();
const byte getScoreMultiplierByDif();
const float vehicleDelayByDif();
const float vehicleDelayByLevel();
const float vehicleLenByDif();
const float vehicleLenByLevel();

// lcd

const byte maxLcdContrast = 100;
const byte maxLcdBrightness = 100;

byte getCurrentLcdContrast();
byte getCurrentLcdBrightness();

void increaseLcdContrast();
void decreaseLcdContrast();

void increaseLcdBrightness();
void decreaseLcdBrightness();

void changeMusicState();
void changeGameSoundState();
void changeMenuSoundState();

// matrix

const byte maxMatrixBrightness = 100;

byte getCurrentMatrixBright();
void increaseMatrixBright();
void decreaseMatrixBright();
