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

void Matrix::snowingEffect() {
  fill();
}
