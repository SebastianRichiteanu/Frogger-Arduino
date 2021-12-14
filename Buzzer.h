#pragma once

#include "Melody.h"

class Buzzer {
  private:
    const static int buzzerPin = 5;
    
    Timer baseDuration;
  
    bool playing = 0;
    int currentNote = 0;
    Timer nextTimerNote = 0;
   
    const uint16_t* frequencies;
    const uint8_t* durations;
    int noteCount = 0;

  public:

    void playTone(int frequency, Timer duration);
    void setMelody(const Melody& melody);

    void play();
    void stop();
    void update();
    void updateOrRestart();

    bool isPlaying() const;

    void playCrashed() const;
    void playBonus() const;
};
