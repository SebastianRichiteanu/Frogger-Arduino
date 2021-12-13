#include "State.h"
#include "SavedData.h"
#include "Map.h"

const Timer skipTime = 30;
Timer updateTime = 0;

void setup () {
  loadSavedData();
  initHardware();
  getGameState().onBegin();

  // resetSavedData();
}

void loop() {
  Timer startTime = millis();

  do {
    js.read();

    updateTime = millis();

    getGameState().update();
  } while (millis() - startTime < skipTime);

  getGameState().render();
 
}
