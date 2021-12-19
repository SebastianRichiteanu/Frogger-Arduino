#pragma once

class IntroState : public State {
  Timer startTime;

  public:
    void onBegin() override;
    void update() override;
};
