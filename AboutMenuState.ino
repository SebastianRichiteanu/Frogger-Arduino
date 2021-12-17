#include "AboutMenuState.h"

#include "Matrix.h"
#include "Buzzer.h"

const byte infoNum = 12;
const int scrollDelay = 400;
const char* const info[] = { "Frogger",
                             "Created by Richiteanu Sebastian",
                             "Project for @UnibucRobotics",
                             "GitHub: tinyurl.com/2umzw7wf",
                             "Press JS to go to menu",
                             "How to play:",
                             "Move/jump with the JS",
                             "Pause with the button",
                             "Don't get hit by cars",
                             "Collect bonus points",
                             "Go up to finish levels",
                             "Pay attention to the time"};
                                  
void AboutMenuState::addScrollDelayAtStart() {
  lastScrollTime = updateTime + 2 * scrollDelay;
}

void AboutMenuState::scrollToLine(byte index) {
  topLineIndex = index;
  currentScroll = 0;
  maxScroll = 0;
  scrollingLeft = true;
  addScrollDelayAtStart();
  printCurrentLines();
}

byte AboutMenuState::printInfoLine(byte index, byte startingAt) const {
  const char* infoLine = info[index];
  lcd.print(infoLine + startingAt);
  return strlen(infoLine);
}

void AboutMenuState::printCurrentLines() {
  lcd.clear();
  lcd.print('>');
  lcd.setCursor(1, 0);
  byte lineLen = printInfoLine(topLineIndex, currentScroll);
  maxScroll = lineLen;
  if (topLineIndex + 1 < infoNum) {
    lcd.setCursor(1, 1);
    printInfoLine(topLineIndex + 1);
  }
}

void AboutMenuState::onBegin() {
  scrollToLine(0);
  matrix.heartEffect();
  buzzer.setMelody(takeOnMeMelody);
  buzzer.play();
}

void AboutMenuState::onEnd() {
  matrix.clear();
}

void AboutMenuState::update() {
  if (maxScroll > 0 && debounce(lastScrollTime, scrollDelay)) {
    if (scrollingLeft) {
      ++currentScroll;
      if (currentScroll == maxScroll) {
        scrollingLeft = false;
      }
    } else {
        --currentScroll;
        if (currentScroll == 0) {
          scrollingLeft = true;
          lastScrollTime = updateTime + 2 * scrollDelay;
        }
      }
      printCurrentLines();
    }

  if (js.isDownDebounce()) {
    scrollToLine((topLineIndex + infoNum - 1) % infoNum);
  }
  if (js.isUpDebounce()) {
    scrollToLine((topLineIndex + 1) % infoNum);
  }
  if (js.isPressedDebounce()) {
    setGameState(GameState::StartMenu);
  }

  // melody
  buzzer.updateOrRestart();
}
