#pragma once

#include "State.h"

class StartMenuState : public State {
  byte selIndex;

  void printMenuLabels() const;
  void printSelectionArrow() const;

  public:
    void onBegin() override;
    void update() override;
    void render() const override;
};
