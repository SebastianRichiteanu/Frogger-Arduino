#pragma once

class SaveSettingsMenuState : public State {
  byte selIndex;

  void printMenuLabels() const;
  void printSelectionArrow() const;
  void resetSettings();

  public:
    void onBegin() override;
    void update() override;
    void render() const override;
};
