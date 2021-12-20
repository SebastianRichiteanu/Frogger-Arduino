#pragma once

class StartMenuState : public State {
  byte selIndex;

  void printChar(byte chr) const;
  void printMenuLabels() const;
  void printSelectionArrow() const;

  public:
    void onBegin() override;
    void onEnd() override;
    void update() override;
};
