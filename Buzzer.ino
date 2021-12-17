#include "Buzzer.h"

Buzzer buzzer;

void Buzzer::playTone(int frequency, Timer duration) {
  if (savedData.soundState) {
    playing = false;
    tone(buzzerPin, frequency, duration);
    playing = true;
  }
}

void Buzzer::setMelody(const Melody &melody) {
  frequencies = melody.frequencies;
  durations = melody.durations;
  noteCount = melody.noteCount;
  baseDuration = melody.baseDuration;
}

void Buzzer::play() {
  if (noteCount == 0) {
    return;
  }
  playing = true;
  currentNote = 0;
  nextTimerNote = updateTime;
}

void Buzzer::stop() {
  playing = false;
  currentNote = 0;
  nextTimerNote = updateTime;
}

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

void Buzzer::updateOrRestart() {
  update();
  if (!isPlaying()) {
    buzzer.play();
  }
}

bool Buzzer::isPlaying () const { return playing; }

void Buzzer::playCrashed() const {
  playTone(75, 300);
}

void Buzzer::playBonus() const {
  playTone(2512, 200);
}

void Buzzer::playFinishedLevel() const {
  playTone(1568, 200);
}
