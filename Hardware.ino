#include "Hardware.h"

//LCD
const byte RS = 7;
const byte enable = 6;
const byte d4 = 5;
const byte d5 = 4;
const byte d6 = 3;
const byte d7 = 2;
const byte lcdPinContrast = 9;
const int lcdContrast = 80;
LiquidCrystal lcd(RS, enable, d4, d5, d6, d7);


const byte dinPin = 12;
const byte clockPin = 11;
const byte loadPin = 10;
const byte noDrivers = 1;
const byte matrixBrightness = 15;
LedControl lc(dinPin, clockPin, loadPin, noDrivers);

Joystick js;

void initHardware() {
  Serial.begin(9600); // debugging purposes

  lcd.begin(16,2);

  // set brightness of led
  pinMode(lcdPinContrast, OUTPUT);
  analogWrite(lcdPinContrast, lcdContrast);

  lc.shutdown(0, false); // turn off power saving, enables display
  lc.setIntensity(0, matrixBrightness); // sets brightness (0~15 possible values)
  lc.clearDisplay(0);// clear screen
}
