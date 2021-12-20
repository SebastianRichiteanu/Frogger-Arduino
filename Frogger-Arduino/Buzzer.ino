#include "Buzzer.h"

// buzzer instance
Buzzer buzzer;

// plays a tone for a certain period of time
// only works if soundState is true, it can be enabled/disabled in the settings
void Buzzer::playTone(int frequency, Timer duration) {
  if (savedData.gameSoundState) {
    playing = false;
    tone(buzzerPin, frequency, duration);
    playing = true;
  }
}

// set the melody to a new one by chaning the frequencies, durations, etc.
void Buzzer::setMelody(const Melody &melody) {
  frequencies = melody.frequencies;
  durations = melody.durations;
  noteCount = melody.noteCount;
  baseDuration = melody.baseDuration;
}

// plays a song while there are notes to play
void Buzzer::play() {
  if (noteCount == 0) {
    return;
  }
  playing = true;
  currentNote = 0;
  nextTimerNote = updateTime;
}

// stops the song
void Buzzer::stop() {
  playing = false;
  currentNote = 0;
  nextTimerNote = updateTime;
}

// the update function check if the musicState is on
// if so it reads from the PROGMEM and updates the buzzer tone
void Buzzer::update() {
  if (!playing || !savedData.musicState) {
    return;
  }
  const uint16_t currentNoteFreq = pgm_read_word_near(frequencies + currentNote);
  const Timer currentNoteDur = baseDuration / pgm_read_byte_near(durations + currentNote);

  if (updateTime > nextTimerNote) {
    if (currentNoteFreq == 0) {
      noTone(buzzerPin);
    } else {
      tone(buzzerPin, currentNoteFreq, currentNoteDur);
    }

    nextTimerNote = updateTime + currentNoteDur;
    ++currentNote;
  }

  if (currentNote == noteCount) {
    playing = false;
    noTone(buzzerPin);
  }
}

// if the melody was finished we start all over again
void Buzzer::updateOrRestart() {
  update();
  if (!isPlaying()) {
    buzzer.play();
  }
}

bool Buzzer::isPlaying () const { return playing; }

// play the menu scrolling sound
void Buzzer::playMenuTone() {
  if (savedData.menuSoundState) {
    playing = false;
    tone(buzzerPin, 4699, 50);
    playing = true;
  }
}

// play the player crashed by a vehicle sound
void Buzzer::playCrashed() const {
  playTone(75, 300);
}

// play the player collected a bonus sound
void Buzzer::playBonus() const {
  playTone(2512, 200);
}

// play the player finished a level sound
void Buzzer::playFinishedLevel() const {
  playTone(1568, 200);
}
