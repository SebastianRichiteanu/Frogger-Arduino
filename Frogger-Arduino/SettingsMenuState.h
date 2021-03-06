#pragma once

class SettingsMenuState : public State {
  byte currentIndex, chrIndex;
  bool isEditing;

  void copySaveData();
  void clearSelArrow();
  void printSelArrow();
  void printNameField();
  void printDifficultyLevelField();
  void printLcdContrast();
  void printLcdBrightness();
  void printMatrixBright();
  void printMusicState();
  void printGameSoundState();
  void printMenuSoundState();
  void printResetEEPROM();
  void printField(byte);
  void printFields(byte);
  void changeToPrevChar();
  void changeToNextChar();

  public:
    void onBegin() override;
    void update() override;
};

extern SavedData copySavedData = {};
