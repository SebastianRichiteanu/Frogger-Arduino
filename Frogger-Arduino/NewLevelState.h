#pragma once

class NewLevelState : public State {
  Timer lastTime;
  void printInfo() const;

  public:
    void onBegin() override;
    void onEnd() override;
    void update() override;
};
