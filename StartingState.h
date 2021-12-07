#pragma once

#include "State.h"
#include "Timer.h"

class StartingState : public State {
  void generateInitialMap();

  public:
    void onBegin() override;
    void update() override;
    void render() const override;
};
