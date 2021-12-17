#pragma once

#include "Hardware.h"

class State {
  public:
    virtual void onBegin() {}
    virtual void onEnd() {}

    virtual void update() {}
    virtual void render() const {} 
};

enum class GameState {
  Intro,
  StartMenu,
  HighScoreMenu,
  SettingsMenu,
  SaveSettingsMenu,
  AboutMenu,
  Starting,
  Playing,
  GameOver,
  NewLevel,
};

State& getGameState();
bool checkMainState();
bool checkPlayingState();
void setGameState(GameState newState);
