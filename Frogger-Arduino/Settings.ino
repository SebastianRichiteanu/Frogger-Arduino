#include "Settings.h"

Difficulty getCurrentDif() { return savedData.difficulty; }

const Timer startingTimeEasy = 100000,
            startingTimeMedium = 75000,
            startingTimeHard = 50000;

const byte startingLivesEasy = 4,
           startingLivesMedium = 3,
           startingLivesHard = 2;

const byte startingJumpsEasy = 3,
           startingJumpsMedium = 2,
           startingJumpsHard = 1;

const byte numberOfWallsEasy = 2,
           numberOfWallsMedium = 3,
           numberOfWallsHard = 4;

const byte minLengthWallsEasy = 2,
           minLengthWallsMedium = 2,
           minLengthWallsHard = 3;

const byte maxLengthWallsEasy = 4,
           maxLengthWallsMedium = 5,
           maxLengthWallsHard = 5;

const float multiplierLenWallsEasy = 0.3,
            multiplierLenWallsMedium = 0.25,
            multiplierLenWallsHard = 0.2;

const byte minNumberOfBonusEasy = 2,
           minNumberOfBonusMedium = 1,
           minNumberOfBonusHard = 0;

const byte maxNumberOfBonusEasy = 4,
           maxNumberOfBonusMedium = 3,
           maxNumberOfBonusHard = 2;

const byte scoreMultiplierEasy = 30,
           scoreMultiplierMedium = 40,
           scoreMultiplierHard = 50;

const float multiplierVehicleDelayEasy = 1,
            multiplierVehicleDelayMedium = 0.9,
            multiplierVehicleDelayHard = 0.8;

const float multiplierVehicleDelayByLvlEasy = 0.01,
           multiplierVehicleDelayByLvlMedium = 0.025,
           multiplierVehicleDelayByLvlHard = 0.05;


const float multiplierVehicleLengthEasy = 1,
            multiplierVehicleLengthMedium = 1.1,
            multiplierVehicleLengthHard = 1.2;

const float multiplierVehicleLengthByLvlEasy = 0.01,
            multiplierVehicleLengthByLVlMedium = 0.025,
            multiplierVehicleLengtgByLvlHard = 0.05;

// returns a char for each difficulty (for lcd output purposes)
const char getCurrentDifAsChar() {
  switch(getCurrentDif()) {
    case Difficulty::Easy:
      return 'E';
    case Difficulty::Medium:
      return 'M';
    case Difficulty::Hard:
      return 'H';
  }
}

// returns a string for each difficulty (for lcd output purposes)
const char* getCurrentDifAsString() {
  switch(getCurrentDif()) {
    case Difficulty::Easy:
      return "Easy";
    case Difficulty::Medium:
      return "Medium";
    case Difficulty::Hard:
      return "Hard";
  }
}

void setCurrentDif(Difficulty diff) { 
  savedData.difficulty = diff;
}

void increaseDifficulty() {
  byte diff = (byte)getCurrentDif();
  diff = (diff + 1) % difficultyNum;
  savedData.difficulty = (Difficulty)diff;
}

void decreaseDifficulty() {
  byte diff = (byte)getCurrentDif();
  diff = (diff + difficultyNum - 1) % difficultyNum;
  savedData.difficulty = (Difficulty)diff;
}

// returns the starting time corresponding to the selected difficulty
const Timer getStartingTimeByDif() {
  switch(getCurrentDif()) {
    case Difficulty::Easy:
      return startingTimeEasy;
    case Difficulty::Medium:
      return startingTimeMedium;
    case Difficulty::Hard:
      return startingTimeHard;
  }
}


// returns the starting number of lives corresponding to the selected difficulty
const byte getStartingLivesByDif() {
  switch(getCurrentDif()) {
    case Difficulty::Easy:
      return startingLivesEasy;
    case Difficulty::Medium:
      return startingLivesMedium;
    case Difficulty::Hard:
      return startingLivesHard;
  }
}



// returns the starting number of jumps corresponding to the selected difficulty
const byte getStartingJumpsByDif() {
  switch(getCurrentDif()) {
    case Difficulty::Easy:
      return startingJumpsEasy;
    case Difficulty::Medium:
      return startingJumpsMedium;
    case Difficulty::Hard:
      return startingJumpsHard;
  }
}

// returns the number of walls corresponding to the selected difficulty
const byte getNumberOfWallsByDif() {
  switch(getCurrentDif()) {
    case Difficulty::Easy:
      return numberOfWallsEasy;
    case Difficulty::Medium:
      return numberOfWallsMedium;
    case Difficulty::Hard:
      return numberOfWallsHard;
  }
}


// returns the length of walls corresponding to the selected difficulty
const byte getLengthOfWallsByDif() {
  switch(getCurrentDif()) {
    case Difficulty::Easy:
      return random(minLengthWallsEasy, maxLengthWallsEasy);
    case Difficulty::Medium:
      return random(minLengthWallsMedium, maxLengthWallsMedium);
    case Difficulty::Hard:
      return random(minLengthWallsHard, maxLengthWallsHard);
  }
}

// returns the walls length multiplier corresponding to the selected difficulty
const float getLengthOfWallsByLvl() {
  byte currentLvl = levelMap.getLevel();
  switch(getCurrentDif()) {
    case Difficulty::Easy:
      return 1 + currentLvl * multiplierLenWallsEasy;
    case Difficulty::Medium:
      return 1 + currentLvl * multiplierLenWallsMedium;
    case Difficulty::Hard:
      return 1 + currentLvl * multiplierLenWallsHard;
  }
}

// returns the starting number of bonus points corresponding to the selected difficulty
const byte getNumberOfBonusByDif() {
  switch(getCurrentDif()) {
    case Difficulty::Easy:
      return random(minNumberOfBonusEasy, maxNumberOfBonusEasy);
    case Difficulty::Medium:
      return random(minNumberOfBonusMedium, maxNumberOfBonusMedium);
    case Difficulty::Hard:
      return random(minNumberOfBonusHard, maxNumberOfBonusHard);
  }
}

// returns the score multiplier by difficulty
const byte getScoreMultiplierByDif() {
  switch(getCurrentDif()) {
    case Difficulty::Easy:
      return scoreMultiplierEasy;
    case Difficulty::Medium:
      return scoreMultiplierMedium;
    case Difficulty::Hard:
      return scoreMultiplierHard;
  }
}

// returns the vehicle delay multiplier by difficulty
const float vehicleDelayByDif() {
  switch(getCurrentDif()) {
    case Difficulty::Easy:
      return multiplierVehicleDelayEasy;
    case Difficulty::Medium:
      return multiplierVehicleDelayMedium;
    case Difficulty::Hard:
      return multiplierVehicleDelayHard;
  }
}

// returns the vehicle delay multiplier by level
const float vehicleDelayByLevel() {
  byte currentLvl = levelMap.getLevel();
  switch(getCurrentDif()) {
    case Difficulty::Easy:
      return 1 - currentLvl * multiplierVehicleDelayByLvlEasy;
    case Difficulty::Medium:
      return 1 - currentLvl * multiplierVehicleDelayByLvlMedium;
    case Difficulty::Hard:
      return 1 - currentLvl * multiplierVehicleDelayByLvlHard;
  }
}

// returns the vehicle length multiplier by difficulty
const float vehicleLenByDif() {
  switch(getCurrentDif()) {
    case Difficulty::Easy:
      return multiplierVehicleLengthEasy;
    case Difficulty::Medium:
      return multiplierVehicleLengthMedium;
    case Difficulty::Hard:
      return multiplierVehicleLengthHard;
  }
}

// returns the vehicle length multiplier by level
const float vehicleLenByLevel() {
  byte currentLvl = levelMap.getLevel();
  switch(getCurrentDif()) {
    case Difficulty::Easy:
      return 1 + currentLvl * multiplierVehicleLengthByLvlEasy;
    case Difficulty::Medium:
      return 1 + currentLvl * multiplierVehicleLengthByLVlMedium;
    case Difficulty::Hard:
      return 1 + currentLvl * multiplierVehicleLengtgByLvlHard;
  }
}

// lcd

byte getCurrentLcdContrast() { return savedData.lcdContrast; }
byte getCurrentLcdBrightness() { return savedData.lcdBrightness; }

void increaseLcdContrast() {
  byte contrast = getCurrentLcdContrast();
  contrast = (contrast + 5) % maxLcdContrast;
  savedData.lcdContrast = contrast;
}

void decreaseLcdContrast() {
  byte contrast = getCurrentLcdContrast();
  contrast = (contrast + maxLcdContrast - 5) % maxLcdContrast;
  savedData.lcdContrast = contrast;
}

void increaseLcdBrightness() {
  byte brightness = getCurrentLcdBrightness();
  brightness = (brightness + 5) % maxLcdBrightness;
  savedData.lcdBrightness = brightness;
}

void decreaseLcdBrightness() {
  byte brightness = getCurrentLcdBrightness();
  brightness = (brightness + maxLcdBrightness - 5) % maxLcdBrightness;
  savedData.lcdBrightness = brightness; 
}

void changeMusicState() { 
  savedData.musicState = !savedData.musicState;
}

void changeGameSoundState() {
  savedData.gameSoundState = !savedData.gameSoundState;
}

void changeMenuSoundState() {
  savedData.menuSoundState = !savedData.menuSoundState;
}

// matrix

byte getCurrentMatrixBright() { return savedData.matrixBrightness; }

void increaseMatrixBright() {
  byte brightness = getCurrentMatrixBright();
  brightness = (brightness + 5) % maxMatrixBrightness;
  savedData.matrixBrightness = brightness;
}

void decreaseMatrixBright() {
  byte brightness = getCurrentMatrixBright();
  brightness = (brightness + maxMatrixBrightness - 5) % maxMatrixBrightness;
  savedData.matrixBrightness = brightness;
}
