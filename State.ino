#include "State.h"

#include "IntroState.h"
#include "StartMenuState.h"
#include "AboutMenuState.h"

IntroState introState;
StartMenuState startMenuState;
AboutMenuState aboutMenuState;
HighScoreMenuState highScoreMenuState;

State* currentState = &introState;

State& getGameState() { return *currentState; }

void setGameState(GameState newState) {
  // print again and clean
  currentState -> render();
  currentState -> onEnd();

  // change
  switch (newState) {
    case GameState::Intro:
      currentState = &introState;
      break;
    case GameState::AboutMenu:
      currentState = &aboutMenuState;
      break;
    case GameState::HighScoreMenu:
      currentState = &highScoreMenuState;
      break;
    default:
      currentState = &startMenuState;
  }

  // render new
  currentState -> onBegin();
}
