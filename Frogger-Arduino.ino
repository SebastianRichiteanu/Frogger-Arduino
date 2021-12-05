#include "State.h"

#include "Highscore.h"

const Timer skipTime = 30;

Timer updateTime = 0;

void setup () {
  initHardware();
  getGameState().onBegin();

  //resetHighscores();
  loadHighscores();
  //saveHighscores();
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
