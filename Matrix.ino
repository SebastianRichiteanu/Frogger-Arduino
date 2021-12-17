#include "Matrix.h"

const byte addrMatrix = 0;

Matrix matrix;

void Matrix::setRow(byte row, byte rowValue) {
  lc.setRow(addrMatrix, row, rowValue);
}

void Matrix::set(byte row, byte column, byte value) {
  lc.setLed(addrMatrix, row, column, value);
}

void Matrix::clear() { lc.clearDisplay(addrMatrix); }

void Matrix::fill() {
  for (byte row = 0; row < 8; ++row) {
    setRow(row, 0xFF); // full
  }
}

void Matrix::setEffect(byte matr[]) {
  for (byte row = 0; row < 8; ++row) {
    setRow(row, matr[row]);
  }
}

void Matrix::cupEffect() {
  byte cup[8] = {0x42, 0x7E, 0x7E, 0x7E, 0x3C, 0x18, 0x18, 0x3C} ;
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
