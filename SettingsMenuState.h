#pragma once

// #include "Settings.h"
#include "State.h"

class SettingsMenuState : public State {
  byte currentIndex;
  byte chrIndex;
  bool isEditing;

  void clearSelArrow();
  void printSelArrow();
  void printNameField();
  void printDifficultyLevelField();
  void printLcdContrast();
  void printLcdBrightness();
  void printMatrixBright();
  void printField(byte);
  void printFields(byte);
  void changeToPrevChar();
  void changeToNextChar();

  public:
    void onBegin() override;
    void update() override;
};
