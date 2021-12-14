#pragma once

class PlayingState : public State {
  bool paused, playerMoved, playerDied;
  Difficulty savedDifficulty;
  Timer dieTime;

  bool isGameOver() const;

  public:
    void onBegin() override;
    void onEnd() override;
    void update() override;
    void render() const override;
};
