#pragma once

class StartMenuState : public State {
  byte selIndex;

  void printMenuLabels() const;
  void printSelectionArrow() const;
  void deleteSelectionArrow() const;

  public:
    void onBegin() override;
    void onEnd() override;
    void update() override;
};
