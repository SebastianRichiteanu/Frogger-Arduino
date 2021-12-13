#include "State.h"

#include "IntroState.h"
#include "StartMenuState.h"
#include "AboutMenuState.h"
#include "HighScoreMenuState.h"
#include "SettingsMenuState.h"
#include "StartingState.h"
#include "PlayingState.h"
#include "GameOverState.h"
#include "SaveSettingsMenuState.h"

IntroState introState;
StartMenuState startMenuState;
AboutMenuState aboutMenuState;
HighScoreMenuState highScoreMenuState;
SettingsMenuState settingsMenuState;
StartingState startingState;
PlayingState playingState;
GameOverState gameOverState;
SaveSettingsMenuState saveSettingsMenuState;

State* currentState = &introState;

State& getGameState() { return *currentState; }

bool checkMainState() { return currentState == &startMenuState; }

bool checkPlayingState() { return currentState == &playingState; }

void setGameState(GameState newState) {
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
    case GameState::SettingsMenu:
      currentState = &settingsMenuState;
      break;
    case GameState::Starting:
      currentState = &startingState;
      break;
    case GameState::Playing:
      currentState = &playingState;
      break;
    case GameState::GameOver:
      currentState = &gameOverState;
      break;
    case GameState::SaveSettingsMenu:
      currentState = &saveSettingsMenuState;
      break;
    default:
      currentState = &startMenuState;
      break;
  }

  // render new
  currentState -> onBegin();
}
