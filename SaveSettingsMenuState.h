#pragma once

#include "State.h"

class SaveSettingsMenuState : public State {
  byte selIndex;

  void printMenuLabels() const;
  void printSelectionArrow() const;
  void deleteSelectionArrow() const;
  void resetSettings();

  public:
    void onBegin() override;
    //void onEnd() override;
    void update() override;
    void render() const override;
};
