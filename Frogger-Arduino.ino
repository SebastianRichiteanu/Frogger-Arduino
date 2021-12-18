#include "State.h"
#include "SavedData.h"

// variables used for debounce
const Timer skipTime = 30;
Timer updateTime = 0;

// setup function called on startup which loads data from EEPROM, inits hardware and starts the game with the intro state
void setup () {
  loadSavedData();
  initHardware();
  getGameState().onBegin();
}

// loop function called continuously to check for js input
// and update and render the game
void loop() {
  Timer startTime = millis();
  do {
    js.read();

    updateTime = millis();

    getGameState().update();
  } while (millis() - startTime < skipTime);

  getGameState().render();
}
