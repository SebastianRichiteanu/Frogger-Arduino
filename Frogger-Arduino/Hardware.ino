#include "Hardware.h"

// LCD pins
const byte RS = 7;
const byte enable = 13;
const byte d4 = A5;
const byte d5 = 4;
const byte d6 = 3;
const byte d7 = 2;
const byte lcdPinContrast = 9;
const byte lcdPinBrightness = 6; // PWM
LiquidCrystal lcd(RS, enable, d4, d5, d6, d7);

// matrix pins
const byte dinPin = 12;
const byte clockPin = 11;
const byte loadPin = 10;
const byte noDrivers = 1;
LedControl lc(dinPin, clockPin, loadPin, noDrivers);

// JS instance
Joystick js;

// button pin
const byte buttonPin = A4;

// button variables + a constant delay
const Timer buttonDebounceDelay = 100;
bool lastButtonState = LOW;
bool buttonState = LOW;
Timer lastButtonDebounceTime = updateTime;

// a heart char for lcd
// byte code: 0
static byte heartChar[] = {
  0b00000,
  0b01010,
  0b11111,
  0b11111,
  0b01110,
  0b00100,
  0b00000,
  0b00000};

// an arrow down char for lcd menu
// byte code 1
static byte arrowDownChar[] = {
  B00100,
  B00100,
  B00100,
  B00100,
  B10101,
  B01110,
  B00100,
  B00000};

// byte code 2
static byte arrowUpChar[] = {
  B00100,
  B01110,
  B10101,
  B00100,
  B00100,
  B00100,
  B00100,
  B00000};

// byte code 3
static byte arrowLeftChar[] = {
  B00010,
  B00100,
  B01000,
  B11111,
  B01000,
  B00100,
  B00010,
  B00000};

// byte code 4
static byte arrowRightChar[] = {
  B01000,
  B00100,
  B00010,
  B11111,
  B00010,
  B00100,
  B01000,
  B00000};

// byte code 5
static byte arrowDownLeftChar[] = {
  B00000,
  B10001,
  B10010,
  B10100,
  B11000,
  B11111,
  B00000,
  B00000};

// byte code 6
static byte arrowDownRightChar[] = {
  B00000,
  B10001,
  B01001,
  B00101,
  B00011,
  B11111,
  B00000,
  B00000};

// byte code 7
static byte arrowUpLeftChar[] = {
  B00000,
  B11111,
  B11000,
  B10100,
  B10010,
  B10001,
  B00000,
  B00000};

// byte code 8
static byte arrowUpRightChar[] = {
  B00000,
  B11111,
  B00011,
  B00101,
  B01001,
  B10001,
  B00000,
  B00000};

// create heart and arrow chars for lcd
void initMenuChars() {
  lcd.createChar(0, arrowDownChar);
  lcd.createChar(1, arrowUpChar);
  lcd.createChar(2, arrowLeftChar);
  lcd.createChar(3, arrowRightChar);
  lcd.createChar(4, arrowDownLeftChar);
  lcd.createChar(5, arrowDownRightChar);
  lcd.createChar(6, arrowUpLeftChar);
  lcd.createChar(7, arrowUpRightChar);
}

void initHeart() {
  lcd.createChar(0, heartChar);
}

// init hardware will pin mode all the necessary pins
// set the brightness to a mapped value
// and set the seed to the value of pin 0, which is not plugged in
// to get a real random effect
void initHardware() {
  Serial.begin(9600); // debugging purposes

  lcd.begin(16,2);

  pinMode(lcdPinContrast, OUTPUT);
  pinMode(lcdPinBrightness, OUTPUT);
  // button
  pinMode(A4, INPUT_PULLUP);
  
  analogWrite(lcdPinContrast, savedData.lcdContrast);
  byte mappedLcdBrightness = map(savedData.lcdBrightness, 0, 95, 100, 255);
  analogWrite(lcdPinBrightness, mappedLcdBrightness);
  byte mappedMatrixBright = map(savedData.matrixBrightness, 0, 95, 5, 15);

  lc.shutdown(0, false); // turn off power saving, enables display
  lc.setIntensity(0, mappedMatrixBright); // sets brightness (0~15 possible values)
  lc.clearDisplay(0);// clear screen

  // random seed on pin 0 because it s not connected and will generate noise
  randomSeed(analogRead(0));

  
}

// updates the contrast and brightness with the mapped values
void updateHardware() {
  analogWrite(lcdPinContrast, savedData.lcdContrast);
  byte mappedBrightness = map(savedData.lcdBrightness, 0, 95, 100, 255);
  analogWrite(lcdPinBrightness, mappedBrightness);
  byte mappedMatrixBright = map(savedData.matrixBrightness, 0, 95, 5, 15);
  lc.setIntensity(0, mappedMatrixBright);
}

// debounce for the button pressed so it won't fail
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
