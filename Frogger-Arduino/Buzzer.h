#pragma once

#include "Melody.h"

class Buzzer {
  private:
    const static int buzzerPin = 5;
    
    bool playing = 0;
    int currentNote = 0, noteCount = 0;
    Timer baseDuration, nextTimerNote = 0;
   
    const uint16_t* frequencies;
    const uint8_t* durations;

  public:

    void playTone(int frequency, Timer duration);
    void setMelody(const Melody& melody);

    void play();
    void stop();
    void update();
    void updateOrRestart();

    bool isPlaying() const;

    void playMenuTone();
    void playCrashed() const;
    void playBonus() const;
    void playFinishedLevel() const;
};
