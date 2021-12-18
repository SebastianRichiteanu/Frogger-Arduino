// vars for each state possible
IntroState introState;
StartMenuState startMenuState;
AboutMenuState aboutMenuState;
HighScoreMenuState highScoreMenuState;
SettingsMenuState settingsMenuState;
StartingState startingState;
PlayingState playingState;
GameOverState gameOverState;
SaveSettingsMenuState saveSettingsMenuState;
NewLevelState newLevelState;

// generic state var for current state
State* currentState = &introState;

State& getGameState() { return *currentState; }

bool checkMainState() { return currentState == &startMenuState; }

bool checkPlayingState() { return currentState == &playingState; }

// renders and calls on end for the old state
// change the state to the new one
// and calls the on begin for the new state
void setGameState(GameState newState) {
  currentState -> render();
  currentState -> onEnd();

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
    case GameState::NewLevel:
      currentState = &newLevelState;
      break;
    default:
      currentState = &startMenuState;
      break;
  }

  currentState -> onBegin();
}
