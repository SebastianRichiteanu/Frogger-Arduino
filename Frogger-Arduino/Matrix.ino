#include "Matrix.h"

// address of the matrix
const byte addrMatrix = 0;

// the matrix instance
Matrix matrix;

// set one position of the matrix to a given value
void Matrix::set(byte row, byte column, byte value) {
  lc.setLed(addrMatrix, row, column, value);
}

// set one row of the matrix to a given value
void Matrix::setRow(byte row, byte rowValue) {
  lc.setRow(addrMatrix, row, rowValue);
}

// clear the whole matrix
void Matrix::clear() { lc.clearDisplay(addrMatrix); }

// fills the whole matrix
void Matrix::fill() {
  for (byte row = 0; row < 8; ++row) {
    setRow(row, 0xFF);
  }
}

// set the matrix to an effect by chaning each row to a given value 
void Matrix::setEffect(byte matr[]) {
  for (byte row = 0; row < 8; ++row) {
    setRow(row, matr[row]);
  }
}

void Matrix::frogEffect() {
  byte frog[8] = {0x7E, 0x7E, 0x60, 0x60, 0x7C, 0x7C, 0x60, 0x60};
  setEffect(frog);
}

void Matrix::cupEffect() {
  byte cup[8] = {0x42, 0x7E, 0x7E, 0x7E, 0x3C, 0x18, 0x18, 0x3C};
  setEffect(cup);
}

void Matrix::hammerEffect() {
  byte hammer[8] = {0x10, 0x38, 0x70, 0xF0, 0x48, 0x04, 0x02, 0x1}; // alhiris help
  setEffect(hammer);
}

void Matrix::heartEffect() {
  byte heart[8] = {0x66, 0xFF, 0xFF, 0xFF, 0xFF, 0x7E, 0x3C, 0x18};
  setEffect(heart);
}

void Matrix::happyFace() {
  byte smile[8] = {0x3C, 0x42, 0xA5, 0x81, 0xA5, 0x99, 0x42, 0x3C};
  setEffect(smile);
}

void Matrix::sadFace() {
  byte sad[8] = {0x3C, 0x42, 0xA5, 0x81, 0x99, 0xA5, 0x42, 0x3C};
  setEffect(sad);
}
