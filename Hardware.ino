#include "Hardware.h"

//LCD
const byte RS = 7;
const byte enable = 13;
const byte d4 = A5;
const byte d5 = 4;
const byte d6 = 3;
const byte d7 = 2;
const byte lcdPinContrast = 9;
const byte lcdPinBrightness = 6; // PWM
LiquidCrystal lcd(RS, enable, d4, d5, d6, d7);


const byte dinPin = 12;
const byte clockPin = 11;
const byte loadPin = 10;
const byte noDrivers = 1;
LedControl lc(dinPin, clockPin, loadPin, noDrivers);

Joystick js;

bool lastButtonState = LOW;
bool buttonState = LOW;
const byte buttonPin = A4;
const Timer buttonDebounceDelay = 100;
Timer lastButtonDebounceTime = updateTime;

void initHardware() {
  Serial.begin(9600); // debugging purposes

  lcd.begin(16,2);

  pinMode(lcdPinContrast, OUTPUT);
  pinMode(lcdPinBrightness, OUTPUT);
  analogWrite(lcdPinContrast, savedData.lcdContrast);
  byte mappedLcdBrightness = map(savedData.lcdBrightness, 0, 95, 0, 255);
  analogWrite(lcdPinBrightness, mappedLcdBrightness);
  byte mappedMatrixBright = map(savedData.matrixBrightness, 0, 95, 0, 15);


  lc.shutdown(0, false); // turn off power saving, enables display
  lc.setIntensity(0, mappedMatrixBright); // sets brightness (0~15 possible values)
  lc.clearDisplay(0);// clear screen

  // button
  pinMode(A4, INPUT_PULLUP);
}

void updateHardware() {
  analogWrite(lcdPinContrast, savedData.lcdContrast);
  byte mappedBrightness = map(savedData.lcdBrightness, 0, 95, 0, 255);
  analogWrite(lcdPinBrightness, mappedBrightness);
  byte mappedMatrixBright = map(savedData.matrixBrightness, 0, 95, 0, 15);
  lc.setIntensity(0, mappedMatrixBright);
}

bool buttonPressed() {
  bool retVal = false;
  bool reading = digitalRead(buttonPin);
  if (reading != lastButtonState) {
    lastButtonDebounceTime = updateTime;
  }
  if (updateTime - lastButtonDebounceTime > buttonDebounceDelay) {
    if (reading != buttonState) {
      buttonState = reading;
      if (buttonState == LOW) {
        retVal = true;
      }
    }
  }
  lastButtonState = reading;
  return retVal;
}
