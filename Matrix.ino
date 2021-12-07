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

void Matrix::happyFace() {
  byte smile[8] = {0x3C,0x42,0xA5,0x81,0xA5,0x99,0x42,0x3C};
  for (byte row = 0; row < 8; ++row) 
    setRow(row, smile[row]);
}

void Matrix::snowingEffect() {
  fill();
}

void Matrix::randomEffect() {
  for (byte times = 0; times < 10; ++times) {
    for (byte row = 0; row < 8; ++row) 
      for (byte column = 0; column < 8; ++column) 
        set(row, column, (byte)random(0,2));
  }
}
